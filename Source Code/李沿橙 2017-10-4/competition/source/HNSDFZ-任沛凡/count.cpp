#include<cstdio>
#define ll long long
#define mod 998244353
using namespace std;
int qpow(int x,int y)
{
	int tmp=1;
	while(y)
	{
		if(y&1)
		tmp=(ll)tmp*x%mod;
		x=(ll)x*x%mod;
		y>>=1;
	}
	return tmp;
}
int inc(int x,int y)
{
	if(x+y>=mod)
	return x+y-mod;
	return x+y;
}
int main()
{
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	int l,r,k,ans=0;
	scanf("%d%d%d",&l,&r,&k);
	for(int i=l;i<=r;i++)
	ans=inc(ans,qpow(i,k));
	if(l==1)
	ans=inc(ans,1);
	printf("%d\n",ans);
	return 0;
}
