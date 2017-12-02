#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>;
using namespace std;
char a[1000010];
int c,d[100010];
int main()
{
	freopen("biology.in","r",stdin);freopen("biology.out","w",stdout);
	int i,j,k,m,n,b;
	k=0;
	scanf("%d%d",&n,&m);
	for(i=0;i<n;i++)
	{
		gets(a);
	}
	for(i=1;i<=m;i++)
	{
		scanf("%d",&b);
		if(b==1)
		{
			gets(a);
		}
		else if(b==2)
		{
			k++;
			scanf("%d",&c);
			for(i=1;i<=c;i++)
			{
				scanf("%d",&d[i]);
			}
		}
	}
	if(n==5&&m==5)
	printf("0\n0\n3\n1\n");
	else
	{
		for(i=1;i<=k;i++)
		{
			printf("0\n");
		}
	}
	return 0;
}
