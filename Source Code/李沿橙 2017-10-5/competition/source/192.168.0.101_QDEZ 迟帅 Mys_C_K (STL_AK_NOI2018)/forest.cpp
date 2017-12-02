#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#define N 100010
#define M N<<1
#define LMAX N<<2
#define MAXLOG 18
#define lint long long
#define inv(x) fast_pow(x,mod-2)
#define mod 1000000007
#define Link(x,y) list[x].nxt=y
#define Cut(x,y) list[x].nxt=list[y].nxt
#define debug(x) cerr<<#x<<"="<<x
#define sp <<" "
#define ln <<endl
#define max(x,y) (x>y)?x:y
using namespace std;
struct edges{
	int to,pre;
}e[M];int h[N],etop,lst[N];
inline int add_edge(int u,int v)
{
	e[++etop].to=v;
	e[etop].pre=h[u];
	return h[u]=etop;
}
struct link{
	int id,nxt;
}list[LMAX];int head[N],dep[N];
int fa[N],dist[N],up[N][MAXLOG];
int link_cnt,val[N],u[N],v[N],d[N];
int ans[N],maxd[N],id[N],LOG;
int logdep[N];
inline int findf(int x)
{
	int fx=x,y;
	while(fx^fa[fx]) fx=fa[fx];
	while(x^fx) y=fa[x],fa[x]=fx,x=y;
	return fx;
}
inline int dfs(int x,int fa)
{
	up[x][0]=fa,dep[x]=dep[fa]+1,
	dist[x]=dist[fa]+val[x];
	for(int i=1;i<=logdep[dep[x]];i++)
		up[x][i]=up[up[x][i-1]][i-1];
	for(int i=h[x];i;i=e[i].pre)
		if(e[i].to^fa)
			dfs(e[i].to,x);
	return 0;
}
inline int getLCA(int u,int v)
{
	if(dep[u]<dep[v]) swap(u,v);
	int d1=logdep[dep[u]],d2=logdep[dep[v]];
	for(int i=d1;i>=0;i--)
		if(dep[up[u][i]]>=dep[v])
			u=up[u][i];
	if(u==v) return v;
	for(int i=d2;i>=0;i--)
		if(up[u][i]^up[v][i])
			u=up[u][i],v=up[v][i];
	return up[u][0];
}
inline int getDist(int x,int y)
{
	int c=getLCA(x,y);
	return dist[x]-dist[c]+dist[y]-dist[up[c][0]];
}
inline int solve_list(int fx,int x,int v)
{
	int p=head[fx],last=p;
	while(list[p].nxt)
	{
		p=list[p].nxt;
		int id=list[p].id,&lt=lst[id];
		lt=max(lt,getDist(id,x)+v);
//		debug(id)sp,debug(lst[id])ln;
	}
	p=head[fx];
	while(list[p].nxt)
	{
		last=p,p=list[p].nxt;
		if(!d[list[p].id]) /*debug(list[p].id)ln,*/Cut(last,p),p=last;
	}
	return list[last].nxt?list[last].nxt:last;
}
inline int new_link(int id)
{
	int p=++link_cnt;
	list[p].id=id,
	list[p].nxt=0;
	return p;
}
inline int fast_pow(int b,int k)
{
	int ans=1;
	while(k)
	{
		(k&1)?(ans=(lint)ans*b%mod):0;
		b=(lint)b*b%mod;k>>=1;
	}
	return ans;
}
int main()
{
	freopen("forest.in","r",stdin);
	freopen("forest.out","w",stdout);
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&val[i]);
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&u[i],&v[i]);d[u[i]]++,d[v[i]]++;
		add_edge(u[i],v[i]),add_edge(v[i],u[i]);
	}
	for(int i=1;i<n;i++) scanf("%d",&id[i]);
	int MAXDEP=n;
	for(int i=1;i<=MAXDEP;i++)
	{
		logdep[i]=logdep[i-1];
		if((1<<logdep[i])<i) logdep[i]++;
	}
	int rt=1;dfs(rt,0);LOG=0;
	logdep[0]=1;
	for(int i=1;i<=n;i++)
		ans[i]=1,fa[i]=i,
		maxd[i]=lst[i]=val[i];
	for(int i=1;i<=n;i++)
	{
		head[i]=new_link(i);
//		debug(i)sp,debug(head[i])ln;
		if(!d[i]) continue;
		int t=new_link(i);
		Link(head[i],t);
	}
	for(int i=1;i<=n;i++)
		ans[n]=(lint)ans[n]*maxd[i]%mod;
	for(int i=n-1;i;i--)
	{
//		debug(i)sp;
		int x=u[id[i]],y=v[id[i]];d[x]--,d[y]--;
//		debug(x)sp,debug(y)sp;
		int fx=findf(x),fy=findf(y);
//		debug(fx)sp,debug(fy)sp;
		ans[i]=(lint)ans[i+1]*inv(maxd[fx])%mod*inv(maxd[fy])%mod;
#define d D
		int d=max(maxd[fx],maxd[fy]);
		d=max(d,lst[x]+lst[y]);
		maxd[fa[fy]=fx]=d;
		ans[i]=(lint)ans[i]*d%mod;
//		debug(d)sp;
#undef d
		int lx=lst[x],ly=lst[y];
//		debug(lx)sp,debug(ly)ln;
		int pos=solve_list(fx,x,ly);
		solve_list(fy,y,lx);
		Link(pos,list[head[fy]].nxt);
		
	}
	for(int i=1;i<=n;i++)
		printf("%d\n",ans[i]);
	return 0;
}
