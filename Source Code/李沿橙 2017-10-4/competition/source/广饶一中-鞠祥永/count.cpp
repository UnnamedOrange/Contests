#include<iostream>
#include<cstdio>
#include<cstring>

#define N 100000007
#define mod 998244353
#define ll long long

using namespace std;
ll L,R,k,ans;

inline ll read()
{
	ll x=0,f=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}

ll kfc(ll a,ll b)
{
	ll res=0;
	a%=mod,b%=mod;
	while(b)
	{
		if(b&1) b--,res=(res+a)%mod;
		a<<=1,a%=mod,b>>=1;
	}return res;
} 

ll ksm(ll a,ll b)
{
	ll res=1;
	while(b)
	{
		if(b&1) res=kfc(res,a)%mod;
		b>>=1;a=kfc(a,a)%mod;
	}return res;
}

int main()
{
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	L=read();R=read();k=read();
	for(int i=L;i<=R;i++)
	{
		ans+=ksm(i,k)%mod;
		ans%mod;
	}
	printf("%lld\n",ans%mod);
	fclose(stdin);fclose(stdout);
	return 0;
}
