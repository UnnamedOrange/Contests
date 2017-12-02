#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#define INF 2147483647
int T;
int a[25],b[25],smax[25];
int s[25],h[25];
int lastb[25];
int choosed[25];
using namespace std;
int main()
{
	freopen("cashier.in","r",stdin);
	freopen("cashier.out","w",stdout);
	scanf("%d",&T);
	for(int I=1;I<=T;I++)
	{
		int fff=0;
		for(int i=0;i<=23;i++)
		{
			scanf("%d",&a[i]);
		}
		for(int i=0;i<=23;i++)
		{
			scanf("%d",&b[i]);
			lastb[i]=b[i];
		}
		int tot=0;
		for(int i=8;i<=23;i++)
		{
			tot-=choosed[i-8];
			if(tot<a[i])
			{
				for(int j=i;j>=i-7;j--)
				{
					if(lastb[j]!=0)
					{
						if(lastb[j]>=a[i]-tot)
						{
							choosed[j]+=a[i]-tot;
							lastb[j]-=a[i]-tot;
							tot=a[i];
							break;
						}
						else
						{
							choosed[j]+=lastb[j];
							tot+=lastb[j];
							lastb[j]=0;
						}
					}
				}
			}
			if(tot<a[i])
			{
				printf("-1\n");
				fff=1;
				break;
			}
		}
		if(fff==0)
		{
			int ans=0;
			for(int i=0;i<=23;i++)
			{
				ans+=choosed[i];
			}
			printf("%d\n",ans);
		}
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
