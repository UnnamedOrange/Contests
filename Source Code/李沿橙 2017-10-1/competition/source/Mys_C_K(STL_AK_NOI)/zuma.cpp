#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<climits>
#define f(x,y) dp[i][k][x][y]
#define g(x,y) dp[k+1][j][x][y]
#define INF (INT_MAX/2-10)
#define N 210
#define debug(x) cerr<<#x<<"="<<x
#define sp <<" "
#define ln <<endl
#define min(x,y) ((x<(y))?x:(y))
using namespace std;
int dp[N][N][2][3];
char s[N];		
int main()
{
	freopen("zuma.in","r",stdin);
	freopen("zuma.out","w",stdout);
	scanf("%s",s+1);int n=strlen(s+1);	
	for(int i=1;i<=n;i++)
	{
		int w=s[i]^'0',g=w^1;
		dp[i][i][0][0]=dp[i][i][1][0]=2;
		dp[i][i][w][1]=0,dp[i][i][w][2]=1;
		dp[i][i][g][1]=3,dp[i][i][g][2]=4;
	}
	for(int len=1;len<n;len++)
		for(int i=1,j;(j=i+len)<=n;i++)
		{
			dp[i][j][0][0]=dp[i][j][0][1]=dp[i][j][0][2]=INF;
			dp[i][j][1][0]=dp[i][j][1][1]=dp[i][j][1][2]=INF;
			for(int k=i;k<j;k++)
			{
				int &x=dp[i][j][0][0],w;				
				x=min(x,f(0,0)+g(0,0));
				x=min(x,f(0,2)+g(0,2));
				x=min(x,f(0,1)+g(0,2));
				x=min(x,f(0,2)+g(0,1));
				x=min(x,f(0,1)+g(0,1)+1);
				x=min(x,f(0,2)+g(0,0)+1);
				x=min(x,f(0,0)+g(0,2)+1);
				x=min(x,f(0,1)+g(0,0)+2);
				x=min(x,f(0,0)+g(0,1)+2);
				
				x=min(x,f(1,0)+g(1,0));
				x=min(x,f(1,2)+g(1,2));
				x=min(x,f(1,1)+g(1,2));
				x=min(x,f(1,2)+g(1,1));
				x=min(x,f(1,1)+g(1,1)+1);
				x=min(x,f(1,2)+g(1,0)+1);
				x=min(x,f(1,0)+g(1,2)+1);
				x=min(x,f(1,1)+g(1,0)+2);
				x=min(x,f(1,0)+g(1,1)+2);
				dp[i][j][1][0]=x;
				
				int &y1=dp[i][j][0][1];
				y1=min(y1,f(0,1)+g(0,0));
				y1=min(y1,f(0,0)+g(0,1));
				y1=min(y1,f(0,0)+g(0,0)+1);
				
				int &y2=dp[i][j][1][1];
				y2=min(y2,f(1,1)+g(1,0));
				y2=min(y2,f(1,0)+g(1,1));
				y2=min(y2,f(1,0)+g(1,0)+1);
				
				int &z1=dp[i][j][0][2];
				z1=min(z1,f(0,0)+g(0,0)+2);
				z1=min(z1,f(0,0)+g(0,1)+1);
				z1=min(z1,f(0,1)+g(0,0)+1);
				z1=min(z1,f(0,1)+g(0,1));
				z1=min(z1,f(0,2)+g(0,0));
				z1=min(z1,f(0,0)+g(0,2));
				
				int &z2=dp[i][j][1][2];
				z2=min(z2,f(1,0)+g(1,0)+2);
				z2=min(z2,f(1,0)+g(1,1)+1);
				z2=min(z2,f(1,1)+g(1,0)+1);
				z2=min(z2,f(1,1)+g(1,1));
				z2=min(z2,f(1,2)+g(1,0));
				z2=min(z2,f(1,0)+g(1,2));
			}
//			if(len<=5)
//			debug(i)sp,debug(j)ln,
//			debug(dp[i][j][0][0])ln,
//			debug(dp[i][j][0][1])sp,debug(dp[i][j][1][1])ln,
//			debug(dp[i][j][0][2])sp,debug(dp[i][j][1][2])ln;
		}
	printf("%d\n",dp[1][n][0][0]);return 0;
}
