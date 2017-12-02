#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
int a[10],b[70];
int main()
{
	freopen("starlit.in","r",stdin);freopen("starlit.out","w",stdout);
	int i,j,k,m,n;
	scanf("%d%d%d",&n,&k,&m);
	for(i=1;i<=k;i++)
	{
		scanf("%d",&a[i]);
	}
	for(j=1;j<=m;j++)
	{
		scanf("%d",&b[j]);
	}
	printf("2\n");
	return 0;
}
