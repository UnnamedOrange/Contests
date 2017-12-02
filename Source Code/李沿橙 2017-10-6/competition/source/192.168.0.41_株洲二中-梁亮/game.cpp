#include<cstdio>
#include<iostream>
#define M 1000000007
using namespace std;
int n,m;
long long a[50004]; 

void one()
{
	int l,r;
	long long c;
	scanf("%d%d%lld",&l,&r,&c);
	for(int i=l;i<=r;++i)
		a[i]+=c,a[i]=a[i]%M;
	return ;
}

void two()
{
	int l,r;
	scanf("%d%d",&l,&r);
	for(int i=l;i<=r;++i)
		a[i]=-a[i];
	return ;
}

void three()
{
	int l,r,k;
	long long sum=0;
	scanf("%d%d%d",&l,&r,&k);
	if(k==1)
		for(int i=l;i<=r;++i)
			sum+=a[i],sum=sum%M;
	
	
	
	else if(k==2)
		for(int i=l;i<=r;++i)
			for(int j=i+1;j<=r;++j)
				sum+=(a[i]*a[j])%M,sum=sum%M;
	
	
	
	else if(k==r-l+1)
	{
		sum=1;
		for(int i=l;i<=r;++i)
			sum*=a[i],sum=sum%M;
	}
	
	
	if(sum<0)	sum+=M;
	printf("%lld\n",sum);
	return ;
}

int main()
{
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i]);
	while(m)
	{
		--m;
		int order;scanf("%d",&order);
		if(order==1)	{one();continue;};
		if(order==2)	{two();continue;};
		if(order==3)	{three();continue;};
		
		
	}
	return 0;
}
