#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
int main()
{
	freopen("photo.in","r",stdin);freopen("photo.out","w",stdout);
	int i,j,k,m,n,t=0;
	scanf("%d%d%d",&m,&n,&k);
	for(i=2;i<=k;i++)
	{
		t+=k;
		t=t%1000000007;
	}
	t=t*(m%1000000007);
	t=t*(n%1000000007);
	printf("%d\n",t);
	return 0;
}
