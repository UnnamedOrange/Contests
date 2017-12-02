#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#define MOD 998244353
int l,r,k;
long long ans=0;
using namespace std;

long long q_power(long long a,int x)
{
	long long tmpans=1;
	while(x>0)
	{
		if(x&1) tmpans=(tmpans*a)%MOD;
		a=(a*a)%MOD;
		x/=2;
	}
	return tmpans;
}

int main()
{
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	scanf("%d%d%d",&l,&r,&k);
	for(long long i=l;i<=r;i++)
	{
		if(i==1) ans+=q_power(2,k);
		else ans+=q_power(i,k);
		ans%=MOD;
	}
	printf("%lld\n",ans);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
