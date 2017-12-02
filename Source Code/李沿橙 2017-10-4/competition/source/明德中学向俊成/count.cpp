#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
int main()
{
	freopen("count.in","r",stdin);freopen("count.out","w",stdout);
	int i,j,k,m,n;
	scanf("%d%d%d",&m,&n,&k);
	long long t,s=0;
	if(m==1)m=2;
	for(i=m;i<=n;i++)
	{
		t=1;
		for(j=1;j<=k;j++)
		{
			t=t*i;
			t=t%998244353;
		}
		s+=t;
		s=s%998244353;
	}
	printf("%lld\n",s);
	return 0;
}
