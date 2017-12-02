#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
const int mo=998244353;
int qpow(int x,int y)
{
	int res=1;
	while(y)
	{
		if(y&1)res=1ll*res*x%mo;
		y>>=1;
		x=1ll*x*x%mo;
	}
	return res;
}
int main()
{
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	int l,r,k;scanf("%d%d%d",&l,&r,&k);
	long long ans=0;
	for(int i=l;i<=r;++i)
	{
		if(i==1)ans=(ans+qpow(2,k))%mo;
		else ans=(ans+qpow(i,k))%mo;
	}
	printf("%lld\n",ans);
	return 0;
}
