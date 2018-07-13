#include <bits/stdc++.h>
#define ll long long
#define ysf (19260817)
#define inf (1LL<<60)
#define N (20005)

int ch[N][2],depa[N<<1],depb[N<<1],a[N<<1],b[N<<1],c[N<<1],n;
ll sum[N][41][41],ans,ret,mid,l,r;

using namespace std;

struct data{
    
    ll val; int num;
    
    inline data operator + (const data a) const{
	return (data){val+a.val,num+a.num};
    }
    
    inline void min(data a,int tot){
	a.val+=mid*tot,a.num+=tot;
	if (val>a.val || (val==a.val && num<a.num)) val=a.val,num=a.num;
    }
    
}res;

struct hash{
    
    struct edge{ int nt,to; data res; }g[2000000];
    
    int head[ysf],st[ysf],num,top;
    
    inline void clear(){
	while (top) head[st[--top]]=0; num=0;
    }
    
    inline void insert(int from,int to,data res){
	g[++num]=(edge){head[from],to,res},head[from]=num;
    }
    
    inline void add(int x,int y,int z,data v){
	int wy=(x<<6|y)<<6|z;
	if (!head[wy%ysf]) st[top++]=wy%ysf;
	insert(wy%ysf,wy,v);
    }
    
    inline data query(int x,int y,int z){
	int wy=(x<<6|y)<<6|z;
	for (int i=head[wy%ysf];i;i=g[i].nt)
	    if (g[i].to==wy) return g[i].res;
	return (data){-1,-1};
    }
    
}hsh;

inline int gi(){
    int x=0,q=1; char ch=getchar();
    while (ch<'0' || ch>'9') q=ch=='-'?-1:1,ch=getchar();
    while (ch>='0' && ch<='9') x=x*10+ch-'0',ch=getchar();
    return q*x;
}

inline void dfs(int x,int A,int B){
    depa[x]=A,depb[x]=B; if (x>=n) return;
    dfs(ch[x][0],A+1,B),dfs(ch[x][1],A,B+1);
    for (int i=0;i<=40;++i)
	for (int j=0,v;j<=40;++j){
	    if ((v=ch[x][0])<n) sum[x][i][j]+=sum[v][i][j];
	    else if (A+1>=i && B>=j) sum[x][i][j]+=1LL*c[v]*(a[v]+A+1-i)*(b[v]+B-j);
	    if ((v=ch[x][1])<n) sum[x][i][j]+=sum[v][i][j];
	    else if (A>=i && B+1>=j) sum[x][i][j]+=1LL*c[v]*(a[v]+A-i)*(b[v]+B+1-j);
	}
}

inline data dp(int x,int A,int B){
    if (x>=n){
	if (A && B) return (data){1LL*c[x]*(a[x]+depa[x]-A+1)*(b[x]+depb[x]-B+1),0};
	if (A && !B) return (data){1LL*c[x]*(a[x]+depa[x]-A+1)*b[x],0};
	if (!A && B) return (data){1LL*c[x]*a[x]*(b[x]+depb[x]-B+1),0};
	return (data){1LL*c[x]*a[x]*b[x],0};
    }
    if (A && B) return (data){sum[x][A-1][B-1],0};
    data res=hsh.query(x,A,B);
    if (res.num!=-1) return res; res=(data){inf,0};
    if (!A && !B){
	res.min(dp(ch[x][0],0,0)+dp(ch[x][1],0,0),2);
	res.min(dp(ch[x][0],depa[x]+1,0)+dp(ch[x][1],0,0),1);
	res.min(dp(ch[x][0],0,0)+dp(ch[x][1],0,depb[x]+1),1);
	res.min(dp(ch[x][0],depa[x]+1,0)+dp(ch[x][1],0,depb[x]+1),0);
    }
    if (A && !B){
	res.min(dp(ch[x][0],A,0)+dp(ch[x][1],A,0),1);
	res.min(dp(ch[x][0],A,0)+dp(ch[x][1],A,depb[x]+1),0);
    }
    if (!A && B){
	res.min(dp(ch[x][0],0,B)+dp(ch[x][1],0,B),1);
	res.min(dp(ch[x][0],depa[x]+1,B)+dp(ch[x][1],0,B),0);
    }
    hsh.add(x,A,B,res); return res;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("y.in","r",stdin);
    freopen("y.out","w",stdout);
#endif
    n=gi();
    for (int i=1;i<n;++i){
	ch[i][0]=gi(),ch[i][1]=gi();
	if (ch[i][0]<0) ch[i][0]=n-1-ch[i][0];
	if (ch[i][1]<0) ch[i][1]=n-1-ch[i][1];
    }
    for (int i=n;i<n<<1;++i)
	a[i]=gi(),b[i]=gi(),c[i]=gi(),r+=1LL*c[i]*a[i]*b[i];
    dfs(1,0,0);
    while (l<=r){
	mid=(l+r)>>1,hsh.clear(),res=dp(1,0,0);
	if (res.num==n-1){ ans=res.val,ret=mid; break; }
	res.num>=n-1?(ans=res.val,ret=mid,l=mid+1):r=mid-1;
    }
    cout<<ans-ret*(n-1); return 0;
}
