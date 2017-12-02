#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
using namespace std;
int i,j,k,l,dp[100005][3];
int y[100005];
string a;
int main()
{
	freopen("reverse.in","r",stdin);
	freopen("reverse.out","w",stdout);
	cin>>a;
	l=a.size();
	for(i=0;i<=l-1;i++)
		y[i+1]=a[i]-'0';
	dp[1][1]=(y[1]==0);
	dp[1][0]=(y[1]==1);
	for(i=2;i<=l;i++)
	{
		dp[i][1]=min(dp[i-1][1],dp[i-1][0])+(y[i]==0);
		dp[i][0]=dp[i-1][0]+(y[i]==1);
	}
	cout<<min(dp[l][1],dp[l][0]);
	return 0;
}