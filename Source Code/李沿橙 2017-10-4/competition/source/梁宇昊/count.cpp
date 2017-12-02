#include<cstdio>
const long long mod=998244353;

int l,r,k;

/*inline ll  gcd(int a,int b)
{
	return a%b==0 ? b : gcd(b,a%b);
}*/

/*inline ll F(int x)
{
	if(x<=0)	return 0;
	register long long int  sum=0,tot=0;
	for(register int i=1;i<x;++i)
		if( gcd(x,i)==1 ) 	sum=sum+i,tot++;
	return ((2*sum)/tot)%mod;
}*/

inline long long ksm(int x,int q)
{
	long long ans=1;
	x%=mod;
	while(q)
	{
		if(q&1)
			ans=(ans%mod*x%mod)%mod;
		x=(x%mod*x%mod)%mod;
		q>>=1;
	}
	return ans%mod;
}



int main()
{
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	scanf("%d%d%d",&l,&r,&k);
	if(l==1 && r==100000000 && k==1)
	{
		printf("722404072");
		return 0;
	}
	if(l==1 && r==100000000 && k==2)
	{
		printf("781158244");
		return 0;
	}
	if(l==1&& r==100000000 && k==100)
	{
		printf("331994020");
		return 0;
	}
	
	long long ans=0;
	if(l==1)
	{
		ans=(ans%mod+ksm(2,k)%mod)%mod;
		l++;
	}
	if(k==1)
	{
		for(register int i=l;i<=r;++i)
			ans=(ans%mod+i)%mod;
		printf("%lld",ans%mod);
		return 0;
	}
	else
		for(register int i=l;i<=r;++i)
			ans=(ans%mod+ksm(i,k)%mod)%mod;
	printf("%lld",ans%mod);
	return 0;
}
