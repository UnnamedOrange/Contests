#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
long long x[200010], y[200010];
int main() 
{
	freopen("geometry.in", "r", stdin);freopen("geometry.out", "w", stdout);
	int n,m,i,l,r;
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	{
		scanf("%lld",&x[i]);
	}
	for(i=1;i<=n;i++)
	{
		scanf("%lld",&y[i]);
	}
	sort(x+1,x+n+1);
	sort(y+1,y+n+1);
	scanf("%d",&m);
	for(i=1;i<=m;i++) 
	{
		long long xx,yy;
		scanf("%lld%lld",&xx,&yy);
		l=1;
		r=n;
		while(l<r) 
		{
			int mid=(l+r+1)/2;
			if (x[mid]*yy+y[mid]*xx>=x[mid]*y[mid])l=mid;
			else r = mid - 1;
		}
		if (x[l]*yy+y[l]*xx>=x[l]*y[l])printf("%d\n",l);
		else printf("%d\n", 0);
	}
	return 0;
}
