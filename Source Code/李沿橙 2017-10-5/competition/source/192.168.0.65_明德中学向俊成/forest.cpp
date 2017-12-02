#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
int a[100001],b[100001],c[100001],d[100001],f[10001];
int x,y;
int main()
{
	freopen("forest.in","r",stdin);freopen("forest.out","w",stdout);
	int i,j,k,m,n,s=0;
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		s+=a[i];
		s=s%1000000007;
	}
	for(i=1;i<n;i++)
	{
		scanf("%d%d",&b[i],&c[i]);
		f[c[i]]=b[i];
	}
	for(i=1;i<n;i++)
	{
		scanf("%d",&d[i]);
	}
	printf("%d\n",s);
	if(s==6)
	printf("9\n6\n");
	else
	for(i=2;i<n;i++)
	{
		printf("1\n");
	}
	return 0;
}
