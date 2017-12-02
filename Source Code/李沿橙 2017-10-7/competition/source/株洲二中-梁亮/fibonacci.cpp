#include<cstdio>
#include<iostream>
//10^12   fibonacci<60
using namespace std;
int m;
long long a,b,fibon[66];
long long fa,fb;
bool founda=false,foundb=false;

long long findf(long long x)
{
	long long fx;
	bool foundx=false;
	for(int i=1;i<60;++i)
	{
		if(foundx==false&&fibon[i]>=x)
		{
				fx=x-fibon[i-1];
				foundx=true;
		}
	}
	return fx;
}

long long search(long long x,long long y)
{
	while(x>1&&y>1)
	{
		if(x>y)	x=findf(x);
		if(x<y)	y=findf(y);
		if(x==y)	return x;
	}
	return 1;
}

int main()
{
	freopen("fibonacci.in","r",stdin);
	freopen("fibonacci.out","w",stdout);
	
	scanf("%d",&m);
	fibon[0]=fibon[1]=1;
	for(int i=2;i<60;++i)
		fibon[i]=fibon[i-1]+fibon[i-2];
	while(m)
	{
		scanf("%d%d",&a,&b);
		--m;
		printf("%d\n",search(a,b));
	}
	return 0;
}


