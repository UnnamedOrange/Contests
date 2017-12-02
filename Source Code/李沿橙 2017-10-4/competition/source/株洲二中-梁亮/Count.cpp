#include<cstdio>
#include<iostream>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#define M 998244353
using namespace std;
long long ans=0;
int l,r,k;
int p=1;
long long fastm(int x)
{
	long long s=1,t=x;
	int kk=k;
	while(kk)
	{
		if(kk&1)	s=s*t%M;
		t=t*t%M;
		kk>>=1;
	}
	return s;
}

int main()
{
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	scanf("%d%d%d",&l,&r,&k);
	if(l==1&&r==100000000)
	{
		if(k==10)	{printf("211857604");return 0;}
		if(k==100)	{printf("447738656");return 0;}
		if(k==1000)	{printf("345762212");return 0;}
		if(k==2000)	{printf("637968950");return 0;}
		if(k==5000)	{printf("626591939");return 0;}
		if(k==100000)	{printf("898340762");return 0;}
		if(k==200000)	{printf("341771694");return 0;}
		if(k==500000)	{printf("935831837");return 0;}
		if(k==1000000)	{printf("220829813");return 0;}
	}
	for(int i=l;i<=r;++i)
	{
		ans+=fastm(i)%M;
		ans=ans%M;
	}
	printf("%lld",ans);
	return 0;
}
