#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<stack>
#define N 100005
using namespace std;
struct edge
{
	int to,nx;
}d[N*2];
int head[N],cnt;
void add(int u,int v)
{
	cnt++;
	d[cnt].to=v;
	d[cnt].nx=head[u];
	head[u]=cnt;
}
int n,typ,k;
int dp[N][3],siz[N];
void dfs(int x,int f)
{
	dp[x][2]=1;dp[x][1]=-1;
	int mn=1000000000,po=0;
	bool fl=0,f2=0;
	for(int i=head[x];i;i=d[i].nx)
	{
		if(d[i].to==f)continue;
		dfs(d[i].to,x);
		int v=d[i].to;
		if(dp[v][1]==-1)f=1;
		if(!fl)dp[x][0]+=dp[v][1];//0
		
		if(dp[v][1]==-1)dp[x][1]+=dp[v][2],f2=1;
		else
		{
			if(dp[v][2]<=dp[v][1])dp[x][1]+=dp[v][2],f2=1;
			else
			{
				dp[x][1]+=dp[v][1];
				if(dp[v][2]<mn)mn=dp[v][2],po=v;
			}
		}
		
		if(dp[v][1]==-1&&dp[v][0]==-1)dp[x][2]+=dp[v][2];
		else if(dp[v][1]==-1)dp[x][2]+=min(dp[v][0],dp[v][2]);
		else if(dp[v][0]==-1)dp[x][2]+=min(dp[v][1],dp[v][2]);
		else dp[x][2]+=min(min(dp[v][0],dp[v][1]),dp[v][2]);
	}
	if(fl)dp[x][0]=-1;
	if(!f2)
		dp[x][1]=dp[x][1]-dp[po][1]+mn;
}
int main()
{
freopen("general.in","r",stdin);
freopen("general.out","w",stdout);
	scanf("%d%d%d",&n,&k,&typ);
	int t1,t2;
	for(int i=1;i<n;++i)
	{
		scanf("%d%d",&t1,&t2);		
		add(t1,t2);add(t2,t1);
	}
	if(k==0){printf("%d\n",n);return 0;}
	if(k==1){dfs(1,0);printf("%d\n",min(dp[1][1],dp[1][2]));return 0;}
	return 0;
}
