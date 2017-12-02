#include<iostream>
#include<cstdio>
#include<cstring>

#define N 2001
#define mod 1000000007
#define ll long long

using namespace std;
ll n,m,ans,cnt,tot,k;

ll ksm(ll a,ll b)
{
	ll res=1;
	while(b)
	{
		if(b&1) res=res*a%mod;
		b>>=1;a=a*a%mod;
	}return res;
}

int main()
{
	freopen("photo.in","r",stdin);
	freopen("photo.out","w",stdout);
	cin>>n>>m>>k;
	cout<<ksm(2,k+1)%mod;
}
