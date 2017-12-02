#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<climits>
#define P(x) x
#define Q(x) (x+n)
#define build_edge(u,v,x) add_edge(u,v,x),add_edge(v,u,0)
#define INF (INT_MAX/10-10)
#define M 3600010
#define N 200010
using namespace std;
struct edges{
	int to,pre,resf;
}e[M];int h[N],etop,lev[N];
queue<int> q;bool vis[N];
inline int add_edge(int u,int v,int c)
{
	etop++;
	e[etop].to=v;
	e[etop].resf=c;
	e[etop].pre=h[u];
	return h[u]=etop;
}
inline bool bfs(int s,int t)
{
	while(!q.empty()) q.pop();
	memset(vis,false,sizeof(vis));
	memset(lev,0,sizeof(lev));
	q.push(s);vis[s]=true;lev[s]=1;
	while(!q.empty())
	{
		int x=q.front();q.pop();
		for(int i=h[x];i;i=e[i].pre)
			if(!vis[e[i].to]&&e[i].resf)
				lev[e[i].to]=lev[x]+1,
				vis[e[i].to]=true,
				q.push(e[i].to);
	}
	return vis[t];
}
int cur[N];
int dfs(int s,int t,int a)
{
	if(s==t||!a) return a;
	int flow=0,f;
	for(int &i=cur[s];i;i=e[i].pre)
		if(lev[e[i].to]==lev[s]+1&&(f=dfs(e[i].to,t,min(e[i].resf,a))>0))
		{
			flow+=f,a-=f,e[i].resf-=f;
			e[((i-1)^1)+1].resf+=f;
			if(!a) break;
		}
	return flow;
}
int main()
{
	int n,m;scanf("%d%d",&n,&m);
	int s=Q(n)+1,t=s+1;
	for(int i=1;i<=n;i++)
		build_edge(P(i),Q(i),1);
	for(int i=1;i<=m;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		build_edge(Q(u),P(v),INF);
		build_edge(Q(v),P(u),INF);
	}
	int k;scanf("%d",&k);
	while(k--)
	{
		int u,v;scanf("%d%d",&u,&v);
		build_edge(s,P(u),INF);
		build_edge(Q(v),t,INF);
	}
	int flow=0;
	while(bfs(s,t))
	{
		for(int i=1;i<=t;i++)
			cur[i]=h[i];
		flow+=dfs(s,t,INF);
	}
	printf("%d\n",flow);
	return 0;
}
