#include<bits/stdc++.h>
#define mo 1000000007
using namespace std;
long long getmi(long long a,long long x)
{
	if (a<0) return 0;
	a%=mo;x%=(mo-1);
	long long ans=1;
	while (x)
	{
		if (x&1) ans=ans*a%mo;
		a=a*a%mo;
		x>>=1;
	}if (ans>=mo) assert(0);
	return ans;
}
int main()
{
	int t;scanf("%d",&t);
	while (t--)
	{
		long long n,m;scanf("%lld%lld",&n,&m);
		if (n==1) printf("%lld\n",m%mo);
		else if (n==2) printf("%lld\n",m%mo*((m-1+mo)%mo)%mo);
		else printf("%lld\n",(m%mo)*((m-1+mo)%mo)%mo*getmi(m-2,n-2)%mo);
	}
}
	
