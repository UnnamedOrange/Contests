#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
#define mod 7
typedef long long ll;

ll n,ans=0;
ll f[1005];

ll exgcd(ll a,ll b,ll &x,ll &y)
{
	if (b==0)
	{
		x=1,y=0;
		return a;
	}
	ll res=exgcd(b,a%b,y,x);
	y-=(a/b)*x;
	return res;
}
ll inv(ll a)
{
	ll x,y,d=exgcd(a,mod,x,y);
	if (x<0) x+=mod;
	return x%mod;
}
void work()
{
	for (ll i=2;i<=2*n;i++) f[i]=f[i-1]*i;
	ans=f[2*n]/f[n]/f[n];
	ans-=f[2*n]/f[n+1]/f[n-1];
	printf("%lld\n",ans%7);
}

int main()
{
	freopen("stack.in","r",stdin);
	freopen("stack.out","w",stdout);
	
	scanf("%lld",&n);
	f[0]=f[1]=1;
	if (n<=15) {work();return 0;}
	for (ll i=2;i<=2*n;i++) f[i]=f[i-1]*i%mod;
	ans=f[2*n]*inv(f[n]*f[n]%mod)%mod;
	ans-=f[2*n]*inv(f[n+1]*f[n-1]%mod)%mod;
	ans+=mod;ans%=mod;
	printf("%lld\n",ans%7);
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}
