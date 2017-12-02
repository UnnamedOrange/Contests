#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn=1e5+10;

int n,k,t,ans;



int h[maxn],hs;
int et[maxn<<1],en[maxn<<1];
void add(int u,int v){
	hs++,et[hs]=v,en[hs]=h[u],h[u]=hs;
	hs++,et[hs]=u,en[hs]=h[v],h[v]=hs;
}


struct point{
	int i,d;
}p[maxn];
bool v[maxn];
int f[maxn],sz[maxn];
void dfs1(int k,int fa,int dp){
	p[k].i=k,f[k]=fa,p[k].d=dp,sz[k]=1;
	for(int i=h[k];i;i=en[i])
	if(et[i]!=fa){
		dfs1(et[i],k,dp+1);
		sz[k]+=sz[et[i]];
	}
}

bool comp(point x,point y){return x.d>y.d;}

void dfs2(int k,int x){
	v[k]=1,sz[k]=0;
	for(int i=h[k];i;i=en[i])
	if(et[i]!=f[k]){
		if(x&&sz[et[i]]) dfs2(et[i],x-1);
		sz[k]+=sz[et[i]];
	}
}


int main(){
	freopen("general.in","r",stdin);
	freopen("general.out","w",stdout);
	
	scanf("%d%d%d",&n,&k,&t);
	
	int a,b;
	for(int i=1;i<n;i++){
		scanf("%d%d",&a,&b);
		add(a,b);
	}
	
	dfs1(1,0,1);
	
	sort(p+1,p+n+1,comp);
	
	int now;
	for(int i=1;i<=n;i++)
	if(!v[p[i].i]){
		ans++;
		now=p[i].i;
		for(int j=1;j<=k;j++) now=f[now];
		for(int j=k;j>=0;j--){
			dfs2(now,j);
			now=f[now];
		}
	}
	
	printf("%d\n",ans);
	
	return 0;
}
