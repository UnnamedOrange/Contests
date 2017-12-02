#include<bits/stdc++.h>
using namespace std;
#define maxn 2000005
int a[maxn],dp[maxn],n,m,ans;
int main()
{
	freopen("wave.in","r",stdin);
	freopen("wave.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
		for(int j=i-1;j>=1;j--)
			for(int k=i-1;k>=j+1;k--)
				if(abs(a[i]-a[k])>=m&&abs(a[k]-a[j])>=m)
				{
					if(a[k]>=a[i]&&a[k]>=a[j])dp[i]=max(dp[i],dp[j]+2);
					ans=max(ans,dp[i]);
				}
	cout<<ans+1;
	return 0;
}
