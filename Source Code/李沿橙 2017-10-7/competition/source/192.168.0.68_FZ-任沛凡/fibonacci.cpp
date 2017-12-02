#include<cstdio>
#include<iostream>
#include<algorithm>
#define ll long long
int m,p;
ll a[100];
using namespace std;
int main()
{
	freopen("fibonacci.in","r",stdin);
	freopen("fibonacci.out","w",stdout);
	ll x,y;
	a[0]=a[1]=1;
	for(int i=2;i<=60;i++)
	a[i]=a[i-2]+a[i-1];
	scanf("%d",&m);
	while(m--)
	{
		scanf("%lld%lld",&x,&y);
		while(x!=y)
		{
			if(x<y)
			swap(x,y);
			p=lower_bound(a+1,a+61,x)-a;
			x-=a[p-1];
		}
		printf("%lld\n",x);
	}
	return 0;
}
