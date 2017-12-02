#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
using namespace std;
int n,m;
int dp[205][6][10005][3];
int mp[205][6],sum[205];
int vis[205][6][2],ans;
int Max(int x,int y){return x>y?x:y;}
void work1(int x)
{
	for(int i=2;i<=5;++i)
	{
		if(vis[x][i][0])continue;
		for(int j=0;j<=sum[x];++j)
		if(j+mp[x][i]>=0)
		{
			int len=j+mp[x][i],sco=mp[x][i]<0?-mp[x][i]:0;
			int mx=dp[x][i-1][j][0];
			if(dp[x][i-1][j][1]!=-1)mx=Max(mx,dp[x][i-1][j][1]);
			if(mx==-1)continue;
			dp[x][i][len][1]=Max(dp[x][i][len][1],mx+sco);
			ans=Max(ans,mx+sco);
		}
	}
	for(int i=4;i>=1;--i)
	{
		if(vis[x][i][1])continue;
		for(int j=0;j<=sum[x];++j)
		if(j+mp[x][i]>=0)
		{
			int len=j+mp[x][i],sco=mp[x][i]<0?-mp[x][i]:0;
			int mx=dp[x][i+1][j][0];
			if(dp[x][i+1][j][2]!=-1)mx=Max(mx,dp[x][i+1][j][2]);
			if(mx==-1)continue;
			dp[x][i][len][2]=Max(dp[x][i][len][2],mx+sco);
			ans=Max(ans,mx+sco);
		}
	}
}
void work2(int x)
{
	for(int i=1;i<=5;++i)
	{
		for(int j=0;j<=sum[x];++j)
		if(j+mp[x+1][i]>=0)
		{
			int len=j+mp[x+1][i],sco=mp[x+1][i]<0?-mp[x+1][i]:0;
			int mx=Max(dp[x][i][j][0],dp[x][i][j][1]);
			mx=Max(mx,dp[x][i][j][2]);
			if(mx==-1)continue;
			dp[x+1][i][len][0]=mx+sco;
			ans=Max(ans,mx+sco);
		}
	}
}
int main()
{
	freopen("snakevsblock.in","r",stdin);
	freopen("snakevsblock.out","w",stdout);
	memset(dp,-1,sizeof(dp));
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		sum[i]+=sum[i-1]+4;
		for(int j=1;j<=5;++j)
		{
			scanf("%d",&mp[i][j]);
			if(mp[i][j]>0)sum[i]+=mp[i][j];
		}
		vis[i][1][0]=1;vis[i][5][1]=1;
	}
	scanf("%d",&m);
	int t1,t2;
	for(int i=1;i<=m;++i)
	{
		scanf("%d%d",&t1,&t2);
		vis[t1][t2][1]=vis[t1][t2+1][0]=1;
	}
	dp[1][3][4][0]=0;
	for(int i=1;i<=n;++i)
	{
		work1(i);
		if(i!=n)
		work2(i);
	}
	printf("%d\n",ans);
	return 0;
}
