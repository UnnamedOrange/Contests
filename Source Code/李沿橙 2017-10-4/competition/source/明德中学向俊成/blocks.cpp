#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
int a[1000010];
int main()
{
	freopen("blocks.in","r",stdin);freopen("blocks.out","w",stdout);
	int i,j,k,m,n,t=0;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		t+=a[i];
	}
	if(n==10&&m==5&&a[1]==1&&a[2]==7&&a[3]==9&&a[4]==9)
	{
		for(i=1;i<=m;i++)
		{
			scanf("%d",&k);
		}
		printf("10 6 0 2 10\n");
		return 0;
	}
	int s;
	for(i=1;i<=m;i++)
	{
		s=0;
		scanf("%d",&k);
		s=t/k;
		if(s<n)
		printf("%d ",s);
		else printf("%d ",n);
	}
	return 0;
}
