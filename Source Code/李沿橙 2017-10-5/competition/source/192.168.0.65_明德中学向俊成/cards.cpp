#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
int a[301];
int main()
{
	freopen("cards.in","r",stdin);freopen("cards.out","w",stdout);
	int i,j,k,m,n;
	double s=0;
	scanf("%d",&n);
	m=n;
	for(i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		if(a[i]==1)
		m--;
	}
	n=m/2;
	if(m%2==0)
	printf("0.500000000");
	else 
	{
		s=(double)(n+1)/m;
		printf(".9llf",s);
	}
	printf(" 1.000000000\n");
	return 0;
}
