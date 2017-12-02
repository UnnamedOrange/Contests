#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
int dp[100005][2];
char s[100005];
int main()
{
	freopen("reverse.in","r",stdin);
	freopen("reverse.out","w",stdout);
	scanf("%s",s);
	int n=strlen(s);
	if(s[0]=='1')dp[0][1]=0,dp[0][0]=1;
	else dp[0][1]=1,dp[0][0]=0;
	for(int i=1;i<n;++i)
	{
		if(s[i]=='1')
		{
			dp[i][0]=dp[i-1][0]+1;
			dp[i][1]=min(dp[i-1][1],dp[i-1][0]);
		}
		if(s[i]=='0')
		{
			dp[i][0]=dp[i-1][0];
			dp[i][1]=min(dp[i-1][0],dp[i-1][1])+1;
		}
	}
	printf("%d\n",min(dp[n-1][0],dp[n-1][1]));
	return 0;
}
