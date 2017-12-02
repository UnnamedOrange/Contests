#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<iostream>
using namespace std;
const int MAXN=450;
int a[MAXN][MAXN],b[MAXN][MAXN],c[MAXN][MAXN],d[MAXN];
int main()
{
	int k,m,n,ans,p;
	freopen("rally.in","r",stdin);
	freopen("rally.out","w",stdout);
	
	scanf("%d%d%d",&n,&m,&k);
	
	if (n==2 && m==2)
	{
		ans=0;
		scanf("%d%d%d%d",&a[1][1],&a[1][2],&a[2][1],&a[2][2]);
		if ((a[1][1]%k)==0) ans++;
		if ((a[1][2]%k)==0) ans++;
		if ((a[2][1]%k)==0) ans++;
		if ((a[2][2]%k)==0) ans++;
		if (((a[1][1]+a[1][2])%k)==0) ans++;
		if (((a[2][1]+a[2][2])%k)==0) ans++;
		if (((a[1][1]+a[2][1])%k)==0) ans++;
		if (((a[1][2]+a[2][2])%k)==0) ans++;
		if (((a[1][1]+a[1][2]+a[2][1]+a[2][2])%k)==0) ans++;
		printf("%d",ans); 
		return 0;
	}
	
	
	
	ans=0;
	memset(b,0,sizeof(b));
	memset(c,0,sizeof(c));
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=m;j++)
		{
			scanf("%d",&a[i][j]);
			a[i][j]%=k;
			if (a[i][j]==0) ans++;
			b[i][j]=(b[i][j-1]+a[i][j])%k;
			if (b[i][j]==0 && j!=1) ans++;
		}
		for (int j=3;j<=m;j++)
			for (int l=1;l<=j-2;l++)
			{
				p=(b[i][j]-b[i][l]+k)%k;
				if (p==0) ans++;
			}
		
	
	}
	for (int j=1;j<=m;j++)
	{
		for (int i=1;i<=n;i++)
		{
			c[i][j]=(c[i-1][j]+b[i][j])%k;
			if (i!=1 && c[i][j]==0)ans++;
		}
		for (int i=3;i<=n;i++)
			for (int l=1;l<=i-2;l++)
			{
				p=(c[i][j]-c[l][j]+k)%k;
				if (p==0) ans++;
			}
	}
	for (int i1=3;i1<=m;i1++)
		for(int j1=2;j1<=n;j1++)
			for (int i2=1;i2<i1-1;i2++)
				for (int j2=0;j2<j1-1;j2++)
				{
					p=(c[i1][j1]-c[i1][j2]+c[i2][j2]-c[i1][j1]+k)%k;
					if (p==0) ans++;
				}
	printf("%d",ans);
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}
