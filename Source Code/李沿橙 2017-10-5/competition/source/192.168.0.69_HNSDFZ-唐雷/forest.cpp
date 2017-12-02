#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define N 100005
#define mo 1000000007
using namespace std;
struct edge
{
	int to,nx;
}d[N*2];
int head[N],tim,cnt;
bool ct[N*2];
void add(int u,int v)
{
	cnt++;
	d[cnt].to=v;
	d[cnt].nx=head[u];
	head[u]=cnt;
}
int n,res,ans;
int vis[N],dp[N];
int a[N];
void dfs(int x,int f)
{
	vis[x]=tim;
	dp[x]=a[x];res=max(a[x],res);
	for(int i=head[x];i;i=d[i].nx)
	{
		if(d[i].to==f||ct[i])continue;
		dfs(d[i].to,x);
		res=max(dp[x]+dp[d[i].to],res);
		dp[x]=max(dp[d[i].to]+a[x],dp[x]);
	}
}
int main()
{
freopen("forest.in","r",stdin);
freopen("forest.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;++i)scanf("%d",&a[i]);
	int t1,t2;
	for(int i=1;i<n;++i)
	{
		scanf("%d%d",&t1,&t2);
		add(t1,t2);add(t2,t1);
	}
	dfs(1,0);printf("%d\n",res);
	for(int i=1;i<n;++i)
	{
		ans=1;
		tim++;
		scanf("%d",&t1);
		ct[(t1-1)*2+1]=ct[t1*2]=1;
		for(int j=1;j<=n;++j)
		{
			res=0;
			if(vis[j]!=tim)
			{
			dfs(j,0);
			ans=1ll*ans*res%mo;
			}
		}
		printf("%d\n",ans<0?ans+mo:ans);
	}
	
	return 0;
}
