#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#define MAXN 2000005
int n,k,ans=0;
int a[MAXN];
int tmp[MAXN];
using namespace std;
int main()
{
	freopen("wave.in","r",stdin);
	freopen("wave.out","w",stdout);
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++) tmp[j]=0;
		int len=1;
		tmp[1]=a[i];
		for(int j=i+1;j<=n;j++)
		{
			if(len%2==1)
			{
				if(a[j]<tmp[len])
				{
					tmp[len]=a[j];
					continue;
				}
				if(a[j]-tmp[len]>=k)
				{
					len++;
					tmp[len]=a[j];
					continue;
				}
				else continue;
			}
			else
			{
				if(a[j]>tmp[len])
				{
					tmp[len]=a[j];
					continue;
				}
				if(tmp[len]-a[j]>=k)
				{
					len++;
					tmp[len]=a[j];
					continue;
				}
				else continue;
			}
		}
		if(ans<len) ans=len;
	}
	printf("%d\n",ans);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
