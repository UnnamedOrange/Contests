#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#define MAXN 65
int m;
long long f[MAXN];
using namespace std;

long long get_fa(long long x)
{
	for(int i=1;i<=60;i++)
	{
		if(x>f[i] && x<=f[i+1])
		{
			return x-f[i];
		}
	}
}

int main()
{
	freopen("fibonacci.in","r",stdin);
	freopen("fibonacci.out","w",stdout);
	f[0]=1;
	f[1]=1;
	for(int i=2;i<=61;i++)
	{
		f[i]=f[i-1]+f[i-2];
	}
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		long long a,b;
		scanf("%lld%lld",&a,&b);
		while(a!=b)
		{
			if(a>b) a=get_fa(a);
			else b=get_fa(b);
		}
		printf("%lld\n",a);
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
