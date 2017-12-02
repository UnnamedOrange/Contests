#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#define MAXN 405
int n,m,k;
long long ans=0;
int samea=0;
int a[MAXN][MAXN];
int sum[MAXN][MAXN];
using namespace std;

int Ask(int x1,int y1,int x2,int y2)
{
	return sum[x1-1][y1-1]+sum[x2][y2]-sum[x1-1][y2]-sum[x2][y1-1];
}

void work()
{
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if((i*j*samea)%k==0) ans+=(n-i+1)*(m-j+1);
		}
	}
	printf("%lld\n",ans);
}

int main()
{
	freopen("rally.in","r",stdin);
	freopen("rally.out","w",stdout);
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++)
	{
		int sumline=0;
		for(int j=1;j<=m;j++)
		{
			scanf("%d",&a[i][j]);
			sumline+=a[i][j];
			sum[i][j]=sum[i-1][j]+sumline;
			if(i==1 && j==1) samea=a[i][j];
			if(a[i][j]!=samea) samea=-1;
		}
	}
	if(n>80 && m>80 && samea!=-1)
	{
		work();
		fclose(stdin);
		fclose(stdout);
		return 0;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			for(int i2=i;i2<=n;i2++)
			{
				for(int j2=j;j2<=m;j2++)
				{
					if(Ask(i,j,i2,j2)%k==0) ans++;
				}
			}
		}
	}
	printf("%lld\n",ans);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
