#include<iostream>
#include<cstdio>
#include<cstring>

#define N 100007

using namespace std;
int n,m,ans,cnt;
int a[N],sum[N];char s[N];

int main()
{
	freopen("reverse.in","r",stdin);
	freopen("reverse.out","w",stdout);
	scanf("%s",s);n=strlen(s);ans=N+N;
	if(n==1) 
	{
		printf("0\n");
		return 0;
	}
	for(int i=0;i<n;i++) a[i+1]=s[i]=='0'?0:1;
	for(int i=1;i<=n;i++) sum[i]=sum[i-1]+a[i];
	for(int i=0;i<=n;i++)
	{
		ans=min(ans,sum[i]+n-i-(sum[n]-sum[i]));
	}
	printf("%d\n",ans);
	return 0;
}
