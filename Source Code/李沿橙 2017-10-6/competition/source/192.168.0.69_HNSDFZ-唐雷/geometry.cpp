#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define N 100005
using namespace std;
typedef long long ll;
ll n,m,ans;
ll a[N],b[N];
bool check(ll x,ll y,ll pos)
{
	return 1ll*a[pos]*b[pos]<=1ll*a[pos]*y+1ll*b[pos]*x;
}
void work(ll x,ll y)
{
	if(!check(x,y,1)){ans=0;return;}
	ll l=1,r=n;
	while(l<=r)
	{
		ll mid=(l+r)>>1;
		if(check(x,y,mid)){ans=mid;l=mid+1;}
		else {r=mid-1;}
	}
}
int main()
{
	freopen("geometry.in","r",stdin);
	freopen("geometry.out","w",stdout);
	scanf("%lld",&n);
	for(ll i=1;i<=n;++i)scanf("%lld",&a[i]);sort(a+1,a+1+n);
	for(ll i=1;i<=n;++i)scanf("%lld",&b[i]);sort(b+1,b+1+n);
	ll l1,l2;
	scanf("%lld",&m);
	for(ll i=1;i<=m;++i)
	{
		scanf("%lld%lld",&l1,&l2);
		ans=0;
		work(l1,l2);
		printf("%lld\n",ans);
	}
	return 0;
}
