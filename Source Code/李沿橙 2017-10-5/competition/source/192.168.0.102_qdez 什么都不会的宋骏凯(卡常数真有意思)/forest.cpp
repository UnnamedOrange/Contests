#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<ctime>
#include<map>
#include<queue>
#include<string>
#include<vector>
#define rint register int
#define debug(x) cerr<<#x<<"="<<x<<endl
#define fgx cerr<<"-------------"<<endl
typedef long long ll;
using namespace std;
const int mod=1e9+7;
int head[200001],tot,fa[200001],f[200001],a[200001],g[200001],ff[200001];
struct Edge
{	int u,v,next;
}edge[300001];
bool no[300001];
void addedge(int x,int y)
{	edge[++tot].u=x;
	edge[tot].v=y;
	edge[tot].next=head[x];
	head[x]=tot;
}
void dfs1(int x,int la)
{	f[x]=a[x];g[x]=0;
	for(rint i=head[x];i;i=edge[i].next)
	{	int to=edge[i].v;
		if(to!=la)
		{	dfs1(to,x);
			if(f[to]+a[x]>f[x]) f[x]=f[to]+a[x];
			else if(f[to]+a[x]>g[x]) g[x]=f[to]+a[x];
			fa[to]=x;
		}
	}
}
int dfs2(int x,int la,int kk)
{	int ans=f[x]+g[x]-a[x]; if(!g[x]) ans=f[x];
	for(rint i=head[x];i;i=edge[i].next)
	if(!no[i])
	{	int to=edge[i].v;
		if(to!=la)
		{	ans=max(ans,dfs2(to,x,kk));
			ff[to]=kk;
		}
	}
	return ans;
}
int main()
{	freopen("forest.in","r",stdin);
	freopen("forest.out","w",stdout);
	int n,k,la=0,x,y; scanf("%d",&n);
	for(rint i=1;i<=n;i++) scanf("%d",&a[i]);
	for(rint i=1;i<n;i++) scanf("%d%d",&x,&y),addedge(x,y),addedge(y,x);
	dfs1(1,0);
	for(rint i=1;i<=n;i++) ff[i]=1;
	la=dfs2(1,0,1); printf("%d\n",la);
	for(rint i=1;i<n;i++)
	{	scanf("%d",&k); 
		int x=edge[k+k].u,y=edge[k+k].v;
		if(fa[y]==x) swap(x,y); 
		la/=dfs2(ff[y],0,ff[y]);
		no[k+k-1]=no[k+k]=true;int xx=x; 
		while(1)
		{	x=fa[x]; g[x]=0;f[x]=a[x];
			for(rint j=head[x];j;j=edge[j].next)
			if(!no[j])
			{	int to=edge[j].v;
				if(to!=fa[x])
				{	if(f[to]+a[x]>f[x]) f[x]=f[to]+a[x];
					else if(f[to]+a[x]>g[x]) g[x]=f[to]+a[x];
				}
			}
			if(x==ff[y]) break;
		}
		la=((ll)la*dfs2(ff[y],0,ff[y]))%mod*(ll)dfs2(xx,0,xx)%mod;
		printf("%d\n",la);
	}
	return 0;
}

