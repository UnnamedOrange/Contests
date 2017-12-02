#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>

#define N 1000007

using namespace std;
int dp[N],a[N],cnt[N];
int n,k,ans;

int main()
{
	freopen("wave.in","r",stdin);
	freopen("wave.out","w",stdout);
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++) dp[i]=cnt[i]=1;
	for(int i=2;i<=n;i++)
	{
		for(int j=1;j<=i;j++)
	    {
	    	if(abs(a[j]-a[i])>=k) 
	    	{
	    		if(cnt[j]%2==0 && a[i]<a[j])
				{
					 if(dp[i]<dp[j]+1) dp[i]=dp[j]+1,cnt[i]=cnt[j]+1;
				}
	    		else if(cnt[j]%2!=0 && a[i]>=a[j]) 
				{
					 if(dp[i]<dp[j]+1) dp[i]=dp[j]+1,cnt[i]=cnt[j]+1;
			    }
	    		else dp[i]=max(dp[i],dp[j]);
			}
		}
	}  
	printf("%d\n",dp[n]);
	fclose(stdin);fclose(stdout);
	return 0;
}
