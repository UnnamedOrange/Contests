#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
int n;
int sum[1<<12];
int main()
{
	freopen("number.in","r",stdin);
	freopen("number.out","w",stdout);
	scanf("%d",&n);
	ll ans=0;sum[1]=1;
	for(int i=1;i<=n;++i)
	{
		int x=0,y=i;
		for(int len=1;y;y/=10,++len)
		x|=(1<<(y%10));
		ans=ans+sum[x];
		sum[x]++;
	}
	printf("%lld\n",ans);
	return 0;
}
