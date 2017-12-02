#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
char a[100055];
int sum[100055],sum2[100055];
int main()
{
	freopen("reverse.in","r",stdin);
	freopen("reverse.out","w",stdout);
	int i,n,ans;
	scanf("%s",a+1);
	n=strlen(a+1);
	for(i=1;i<=n;i++)
	{
		sum[i]=sum[i-1];
		if(a[i]=='1')
			sum[i]++;
	}
	for(i=n;i>=1;i--)
	{
		sum2[i]=sum2[i+1];
		if(a[i]=='0')
			sum2[i]++;
	}
	ans=100007;
	for(i=0;i<=n;i++)
		ans=min(ans,sum[i]+sum2[i+1]);
	printf("%d",ans);
	return 0;
}
