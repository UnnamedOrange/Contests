#include<bits/stdc++.h>
using namespace std;
#define mod 1000000007

int read(){
	int x=0,f=1;char ch=getchar();
	for (;!isdigit(ch);ch=getchar()) if (ch=='-') f=-f;
	for (;isdigit(ch);ch=getchar()) x=x*10+ch-'0';
	return x*f;
}

namespace Subtask1{
struct matrix{
	long long f[2][2];
};

matrix operator *(matrix a,matrix b){
	matrix c;
	memset(c.f,0,sizeof(c.f));
	for (int i=0;i<2;i++)
		for (int j=0;j<2;j++)
			for (int k=0;k<2;k++)
				c.f[i][k]=(c.f[i][k]+a.f[i][j]*b.f[j][k])%mod;
	return c;
}

long long solve(long long n){
	matrix f={2,3,1,0},g={12,0,0,0};
	for (long long i=1;i<=n-2;i*=2,f=f*f)
		if (i&(n-2)) g=f*g;
	return g.f[0][0];
}

void main(){
	long long n=read();
	if (n>1e5) return;
	printf("%lld\n",solve(n));
}
}

namespace Subtask2{
long long power(long long x,long long y){
	long long t=1;
	for (long long i=1;i<=y;i*=2,x=x*x%mod)
		if (i&y) t=t*x%mod;
	return t;
}

void main(){
	long long n=read(),ans=0;
	if (n>1e5) return;
	vector<pair<int,int>> q;
	for (long long i=1;i*i<=n;i++)
		if (n%i==0){
			q.push_back(make_pair(i,n/i));
			if (n/i!=i)
			q.push_back(make_pair(n/i,i));
		}
	sort(q.begin(),q.end());
	for (int i=(int)q.size()-1;i>=0;i--)
		for (int j=i+1;j<(int)q.size();j++)
			if (q[j].first%q[i].first==0)
			q[i].second-=q[j].second;
	for (int i=1;i<(int)q.size();i++)
		ans=(ans+Subtask1::solve(q[i].first)*q[i].second)%mod;
	ans=ans*power(n,mod-2)%mod;
	printf("%lld\n",ans);
}
}

namespace Subtask3{
int n,q,a[111116],l[111116*4],r[111116*4];

struct rec{
	long long sum,lmx,rmx,mx;
}f[111116*4];

rec operator +(rec a,rec b){
	return (rec){a.sum+b.sum,max(a.lmx,a.sum+b.lmx),max(b.rmx,b.sum+a.rmx),max(max(a.mx,b.mx),a.rmx+b.lmx)};
}

void build(int t,int x,int y){
	l[t]=x;r[t]=y;
	if (x==y) f[t]=(rec){a[x],a[x],a[x],a[x]};
	else {
		build(2*t,x,(x+y)/2);
		build(2*t+1,(x+y)/2+1,y);
		f[t]=f[2*t]+f[2*t+1];
	}
}

rec query(int t,int x,int y){
	if (x<=l[t]&&y>=r[t]) return f[t];
	if (y<=r[2*t]) return query(2*t,x,y);
	if (x>=l[2*t+1]) return query(2*t+1,x,y);
	return query(2*t,x,y)+query(2*t+1,x,y);
}

void main(){
	n=read();q=read();
	if (n>1000||q>1000) return;
	for (int i=1;i<=n;i++) a[i]=read();
	build(1,1,n);
	for (int i=1;i<=q;i++){
		int x=read(),y=read();
		printf("%lld\n",query(1,x,y).mx);
	}
}
}

namespace Subtask4{
int n,m,k,q,a[11116],l[11116*32],r[11116*32],f[11116*32],tmp[116][11116];

void insert(int x,int y,int z,int k){
	f[y]=f[x]+1;
	if (k==-1) return;
	if ((z&(1<<k))==0) r[y]=r[x],insert(l[x],l[y]=++m,z,k-1);
	else l[y]=l[x],insert(r[x],r[y]=++m,z,k-1);
}

int query(int x,int y,int z,int k){
	if (k==-1) return z;
	if (f[r[x]]==f[r[y]]) return query(l[x],l[y],z,k-1);
	if (f[l[x]]==f[l[y]]) return query(r[x],r[y],z^(1<<k),k-1);
	if (z>(z^(1<<k))) return query(l[x],l[y],z,k-1);
	else return query(r[x],r[y],z^(1<<k),k-1);
}

void main(){
	n=m=read()+1;q=read();k=sqrt(n);
	if (n>1000||q>1000) return;
	for (int i=2;i<=n;i++) a[i]=a[i-1]^read();
	for (int i=1;i<=n;i++) insert(i-1,i,a[i],30);
	for (int i=1;i<=n/k;i++)
		for (int j=i*k;j<=n;j++)
			tmp[i][j]=max(tmp[i][j-1],query(i*k-1,j,a[j],30));
	for (int i=1;i<=q;i++){
		int x=read(),y=read()+1,ans=0;
		if (x/k==y/k){
			for (int j=x;j<=y;j++)
				ans=max(ans,query(x-1,y,a[j],30));
		}
		else {
			ans=tmp[x/k+1][y];
			for (int j=x;j/k==x/k;j++)
				ans=max(ans,query(x-1,y,a[j],30));
		}
		printf("%d\n",ans);
	}
}
}

namespace Subtask5{
int n;
vector<pair<int,int>> v[1116];
vector<long long> q;

void travel(int x,int pre,long long d){
	q.push_back(d);
	for (int i=0;i<(int)v[x].size();i++)
		if (v[x][i].first!=pre)
		travel(v[x][i].first,x,d+v[x][i].second);
}

void main(){
	n=read();
	if (n>100) return;
	for (int i=1;i<n;i++){
		int x=read(),y=read(),z=read();
		v[x].push_back(make_pair(y,z));
		v[y].push_back(make_pair(x,z));
	}
	for (int i=1;i<=n;i++)
		travel(i,0,0);
	sort(q.begin(),q.end());
	printf("%lld\n",q[n*n-1]);
}
}

namespace Subtask6{
int n;
vector<pair<int,int>> v[1116];
vector<long long> q;

void travel(int x,int pre,long long d){
	q.push_back(d);
	for (int i=0;i<(int)v[x].size();i++)
		if (v[x][i].first!=pre)
		travel(v[x][i].first,x,d+v[x][i].second);
}

void main(){
	n=read();
	if (n>100) return;
	for (int i=1;i<n;i++){
		int x=read(),y=read(),z=read();
		v[x].push_back(make_pair(y,z));
		v[y].push_back(make_pair(x,z));
	}
	for (int i=1;i<=n;i++)
		travel(i,i,0);
	sort(q.begin(),q.end());
	printf("%lld\n",q[n+n*(n-1)/2-1]);
}
}

namespace Subtask7{
int n,m,h[1116];
long long d[1116];
vector<pair<int,long long>> v[1116];
queue<int> q;

void main(){
	n=read();m=read();
	if (n>100||m>200) return;
	for (int i=1;i<=m;i++){
		int x=read(),y=read(),z=read();
		v[x].push_back(make_pair(y,z));
		v[y].push_back(make_pair(x,z));
	}
	q.push(1);h[1]=1;
	fill(d+2,d+n+1,1ll<<60);
	while (!q.empty()){
		int x=q.front();
		for (int i=0;i<(int)v[x].size();i++){
			if (d[x]+v[x][i].second<d[v[x][i].first]){
				d[v[x][i].first]=d[x]+v[x][i].second;
				if (!h[v[x][i].first])
				q.push(v[x][i].first),h[v[x][i].first]=1; 
			}
		}
		h[x]=false;q.pop();
	}
	printf("%lld\n",d[n]); 
}
}

namespace Subtask8{
int n,m,d[1116],h[1116],ans;
vector<pair<int,int>> v[1116];
vector<int> q;

void travel(int x,int pre){
	h[x]=1;
	for (int i=0;i<(int)v[x].size();i++)
		if (!h[v[x][i].first])
		d[v[x][i].first]=d[x]^v[x][i].second,travel(v[x][i].first,x);
		else if (v[x][i].first!=pre)
			q.push_back(d[x]^d[v[x][i].first]^v[x][i].second);
}

void main(){
	n=read();m=read();
	if (n>100||m>200) return;
	for (int i=1;i<=m;i++){
		int x=read(),y=read(),z=read();
		v[x].push_back(make_pair(y,z));
		v[y].push_back(make_pair(x,z));
	}
	travel(1,0);
	ans=d[n];
	for (int i=0;i<(int)q.size();i++){
		for (int j=i+1;j<(int)q.size();j++)
			if (q[i]<q[j]) swap(q[i],q[j]);
		if (!q[i]) break;
		if ((ans^q[i])<ans) ans^=q[i];
		for (int j=i+1;j<(int)q.size();j++)
			if ((q[j]^q[i])<q[j]) q[j]^=q[i];
	}
	printf("%d\n",ans);
}
}

namespace Subtask9{
int n,f[1116],g[1116],ans;
char s[1116];

void main(){
	scanf(" %s",s+1);n=strlen(s+1);
	if (n>100) return;
	for (int i=1;i<n;i++)
		for (int j=i,k=i+1;j>=1&&k<=n&&s[j]==s[k];j--,k++)
			f[k]=max(f[k],k-j+1),g[j]=max(g[j],k-j+1);
	for (int i=1;i<n;i++)
		ans=max(ans,f[i]+g[i+1]);
	printf("%d\n",ans);
}
}

namespace Subtask10{
int n,r[1116],ans;
char s[1116];

void main(){
	scanf(" %s",s+1);n=strlen(s+1);
	if (n>100) return;
	for (int i=1;i<n;i++)
		for (int j=i,k=i+1;j>=1&&k<=n&&s[j]==s[k];j--,k++)
			r[i]=i-j+1;
	for (int i=1;i<=n;i++)
		for (int j=i+1,k=0;j<=n;j++){
			if (s[j]==s[j-i]) k++;else k=0;
			if (k>=i&&r[j]>=2*i) ans=4*i;
		}
	printf("%d\n",ans);
}
}

int main(){
	freopen("crack_force.in","r",stdin);
	freopen("crack_force.ans","w",stdout);
	int Case=read();
	if (Case==1) Subtask1::main();
	if (Case==2) Subtask2::main();
	if (Case==3) Subtask3::main();
	if (Case==4) Subtask4::main();
	if (Case==5) Subtask5::main();
	if (Case==6) Subtask6::main();
	if (Case==7) Subtask7::main();
	if (Case==8) Subtask8::main();
	if (Case==9) Subtask9::main();
	if (Case==10) Subtask10::main();
}

