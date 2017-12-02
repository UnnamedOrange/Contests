#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#define MAXL 100005
int len=0,ans=2147483647;
int a[MAXL];
int sum1[MAXL],sum2[MAXL];
using namespace std;
int main()
{
	freopen("reverse.in","r",stdin);
	freopen("reverse.out","w",stdout);
	char x;
	while(1)
	{
		scanf("%c",&x);
		if(x=='0' || x=='1')
		{
			len++;
			a[len]=x-'0';
		}
		else break;
	}
	for(int i=1;i<=len;i++)
	{
		sum1[i]=sum1[i-1]+a[i];
	}
	for(int i=len;i>=1;i--)
	{
		if(a[i]==0)
		{
			sum2[i]=sum2[i+1]+1;
		}
		else sum2[i]=sum2[i+1];
	}
	for(int i=0;i<=len;i++)
	{
		int tot=sum1[i]+sum2[i+1];
		if(tot<ans) ans=tot;
	}
	printf("%d\n",ans);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
