#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
int a;
int main()
{
	freopen("count.in","r",stdin);
	freopen("count.out","w"),stdout);
	int m,n,k,k1;
	long long l,b,num=0;
	scanf("%d%d%d",&m,&n,&k);
	for(int i=m;i<=n;i++)
	{
		memset(a,0,sizeof(a));
		l=((((i+1)%998244353)*i)%998244353)/2-i-1;
	   for(int j=2;j<=sqrt(i);j++)
	   {
	   	b=1;
	    while(i%j==0)
	    {
		b=(b*j)%998244353;
		l-=b;
		}
	   }
	   l=(l*2)%998244353;
	   k1=k;
	   a=l;
	  while(k1!=0)
	  {
	
	  } 
	}
	return 0;
}
