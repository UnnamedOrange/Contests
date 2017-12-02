#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
int a[410][410];
int main()
{
	freopen("rally.in","r",stdin);freopen("rally.out","w",stdout);
	int i,j,k,m,n,i1,j1,s=0,t=0,i2,j2;
	scanf("%d%d%d",&n,&m,&k);
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=m;j++)
		{
			scanf("%d",&a[i][j]);
			a[i][j]=a[i][j]%k;
			if(a[i][j]==0)
			t++;
		}
	}
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=m;j++)
		{
			for(i1=1;i1<i;i1++)
			{
				for(j1=1;j1<j;j1++)
				{
					s=0;
					for(i2=i1;i2<=i;i2++)
					{
						for(j2=j1;j2<=j;j2++)
						{
							s=s+a[i2][j2];
							s=s%k;
						}
					}
					if(s%k==0)
					t++;
				}
			}
		}
	}
	printf("%d\n",t); 
	return 0;
}
