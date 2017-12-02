#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<string>
#include<cmath>
#include<ctime>
#include<queue>
#include<map>
#include<vector>
#define rint register int
#define debug(x) cerr<<#x<<"="<<x<<endl
#define fgx cerr<<"-------------"<<endl
#define add(x,y) addedge(x,y),addedge(y,x)
typedef long long ll;
using namespace std;
int f[100010][21],g[100010][21],tot,head[100010],k,sum[100010][21];
struct Edge
{	int u,v,next;
}edge[200010];
void addedge(int x,int y)
{	edge[++tot].u=x;
	edge[tot].v=y;
	edge[tot].next=head[x];
	head[x]=tot;
}
void dfs(int x,int la)
{	int p=0;
	for(rint i=head[x];i;i=edge[i].next)
	{	int to=edge[i].v;
		if(to!=la) dfs(to,x);
	}
	for(rint i=head[x];i;i=edge[i].next)
	{	int to=edge[i].v;
		if(to!=la)
		{	p++; int minn=1000000000,mn=1000000000;
			for(rint j=0;j<=k;j++) minn=min(minn,f[to][j]);
			for(rint j=0;j<=k;j++) mn=min(mn,g[to][j]),sum[p][j]=sum[p-1][j]+min(mn,minn);
		}
	}
	int tt=p;p=0;
	if(!tt)
	{	f[x][k]=g[x][0]=1;g[x][1]=0;
		for(rint i=k-1;i>=1;i--) f[x][i]=f[x][i+1];
		return;
	}
	for(rint j=1;j<=k;j++) g[x][j]=sum[tt][j-1];
	g[x][0]=f[x][k]=min(f[x][k],sum[tt][k]+1); 
	for(rint i=head[x];i;i=edge[i].next)
	{	int to=edge[i].v; p++;
		if(to!=la)
		for(rint j=1;j<=k;j++)
		f[x][j-1]=min(f[x][j-1],f[to][j]+sum[p-1][j-1]+sum[tt][j-1]-sum[p][j-1]);
	}
	for(rint i=k-1;i>=1;i--)
	f[x][i]=min(f[x][i],f[x][i+1]);
}
int main()
{   freopen("general.in","r",stdin);
	freopen("general.out","w",stdout);
	int n,t,x,y; scanf("%d%d%d",&n,&k,&t);
	for(rint i=1;i<=n;i++)
	for(rint j=0;j<=k;j++) f[i][j]=g[i][j]=1000000000;
	for(rint i=1;i<n;i++) scanf("%d%d",&x,&y),add(x,y);
	dfs(1,0);
	int minn=1000000000;
	for(rint i=0;i<=k;i++) minn=min(minn,f[1][i]);
	printf("%d\n",minn);
 	return 0;
}



