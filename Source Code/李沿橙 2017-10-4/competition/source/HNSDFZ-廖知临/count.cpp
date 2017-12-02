#include<bits/stdc++.h>
#define Mod 998244353
using namespace std;
long long sum,l,r,k;
long long pow1(long long a,long long b)//ÊÖ¶¯pow 
{
	long long c=1;
	while(b)
	{
		if(b&1)	c=c*a%Mod;
		a=a*a%Mod;
		b>>=1;
	}
	return c;
}
int main()
{
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	cin>>l>>r>>k;
	for(long long i=l;i<=r;i++)
	{
		if(i!=1)	sum+=pow1(i,k);	
		else	sum+=pow1(2,k);
		if(sum>=Mod)	sum=sum%Mod;
	}	
	cout<<sum;
	return 0;
}
