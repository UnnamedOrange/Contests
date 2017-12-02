#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
int a[100010],b[100010],c[100010];
int x,y;
int main()
{
	freopen("ping.in","r",stdin);freopen("ping.out","w",stdout);
	int i,j,k,m,n,s=0;
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++)
	{
		scanf("%d%d",&x,&y);
	}
	scanf("%d",&k);
	for(i=1;i<=k;i++)
	{
		scanf("%d%d",&x,&y);
		c[x]++;
		c[y]++;
	}
	for(i=1;i<=n;i++)
	{
		if(c[i]>=2)
		{
			s++;
		}
	}
	printf("%d\n",s);
	for(i=1;i<=n;i++)
	{
		if(c[i]>=2)
		{
			printf("%d ",c[i]);
		}
	}
	return 0;
}
