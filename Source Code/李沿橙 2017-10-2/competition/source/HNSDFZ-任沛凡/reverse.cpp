#include<cstdio>
#include<cstring>
#define maxn 100010
#define min(x,y) (x)<(y)?(x):(y)
using namespace std;
char s[maxn];
int n,dp[maxn][2];
int main()
{
	freopen("reverse.in","r",stdin);
	freopen("reverse.out","w",stdout);
	scanf("%s",s+1);
	n=strlen(s+1);
	for(int i=1;i<=n;i++)
	{
		if(s[i]=='0')
		{
			dp[i][1]=min(dp[i-1][0]+1,dp[i-1][1]+1);
			dp[i][0]=dp[i-1][0];
		}
		else 
		{
			dp[i][1]=min(dp[i-1][0],dp[i-1][1]);
			dp[i][0]=dp[i-1][0]+1;
		}
	}
	printf("%d\n",min(dp[n][1],dp[n][0]));
	return 0;
}
			
	
