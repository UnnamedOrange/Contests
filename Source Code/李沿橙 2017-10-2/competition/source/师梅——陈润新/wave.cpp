#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
#define MAXN 2000005
int n,k;
int a[MAXN+1];
int dp[MAXN+1];//dp[i]表示前i个中最长的 
int main()
{
	freopen("wave.in","r",stdin);
    freopen("wave.out","w",stdout);
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	//初始化 
	//dp[0] = 0;
	dp[1] = 1;
	//dp[2] = 2;
	for(int i=2;i<=n;i++)
		for(int j=1;j<=i-1;j++){
			if(((dp[j]+1) % 2 == 0) && (a[i] - a[j] >= k))//dp[j]+1为判断此时如果i位合法那么是否是偶数位 
				dp[i] = max(dp[i],dp[j]+1);//后面的判断包含了>相邻的两项 
			else{
				if(((dp[j]+1) % 2 == 1) && (a[j] - a[i] >= k))//后面的含有大于相邻的 
					dp[i] = max(dp[i],dp[j]+1);
			}
		}
	printf("%d",dp[n]);
        return 0;
}

