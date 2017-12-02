#include <iostream>
#include <cstdio>
#define mod 998244353;
using namespace std;
int pow(int a,int b)
{	
	int res=1;
	int base=a;
	while(b>0)
	{
		if(b%2)
		res*=base;
		base*=base;
		b/=2;
	}
	return res;
/*	int z=a;
	b--;	
	while(b--)
		a*=z;
		return a;*/
}
int gcd(int m,int n)
{
	return n==0?m : gcd(n,m%n);
}
int sum(int x)
{
	int ret;
	float  ans1=0
	;
	int s=0;
	for(int i=1;i<=x;i++)
	{
		if(gcd(i,x)==1) 
		{
			s++;
			ans1+=i;
		}
	}
	ret=(ans1/s)*2;
	return  ret;
}
int main()
{
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	int bl;
	int t;
	int ans=0;
	int l,r,k;
	cin>>l>>r>>k;
	for(int i=l;i<=r;i++)
	{
		t=sum(i);
		bl=pow(t,k);
		bl=bl%mod;
		ans+=bl;
	}
	cout<<ans;
	fclose(stdin);
	fclose(stdout);
	return 0;
}
