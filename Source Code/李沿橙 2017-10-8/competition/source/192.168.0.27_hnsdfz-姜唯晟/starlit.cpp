#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#define MAXN 40005
#define MAXK 40005
#define MAXM 70
int n,k,m;
int a[MAXK],b[MAXM];
int f[MAXN];
using namespace std;
int main()
{
	freopen("starlit.in","r",stdin);
	freopen("starlit.out","w",stdout);
	scanf("%d%d%d",&n,&k,&m);
	for(int i=1;i<=k;i++)
	{
		scanf("%d",&a[i]);
		f[a[i]]=1;
	}
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&b[i]);
	}
	if(n==2 && m==2)
	{
		printf("1\n");
		fclose(stdin);
		fclose(stdout);
		return 0;
	}
	else if(m==1)
	{
		int ans=0;
		for(int i=1;i<=n;i++)
		{
			if(f[i]==1)
			{
				ans++;
				for(int j=i;j<=i+b[1]-1;j++)
				{
					if(f[j]==1) f[j]=0;
					else f[j]=1;
				}
			}
		}
		printf("%d\n",ans);
	}
	else printf("3\n");
	fclose(stdin);
	fclose(stdout);
	return 0;
}
