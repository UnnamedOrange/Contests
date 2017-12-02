#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<string>
#include<cmath>
#include<ctime>
#include<queue>
#include<map>
#include<vector>
#define rint register int
#define debug(x) cerr<<#x<<"="<<x<<endl
#define fgx cerr<<"-------------"<<endl
typedef long long ll;
using namespace std;
ll fib[1000];
map<ll,int> mp;
inline ll read()
{	ll x; char c=getchar();
	for(;c>'9'||c<'0';c=getchar());
	for(;c<='9'&&c>='0';c=getchar()) x=x*10+(c-'0');
	return x;
}
int main()
{   freopen("fibonacci.in","r",stdin);
	freopen("fibonacci.out","w",stdout);
	fib[1]=fib[2]=1;
	for(rint i=3;i<=60;++i) fib[i]=fib[i-1]+fib[i-2];
	int m;scanf("%d",&m); ll x,y;
	for(rint i=1;i<=m;++i)
	{	x=read();y=read(); mp.clear();
		int k1=lower_bound(fib+1,fib+61,x)-fib,k2=lower_bound(fib+1,fib+61,y)-fib;
		while(x!=1)
		{	mp[x]=1;
			x=x-fib[k1-1];
			while(fib[k1-1]>=x) k1--;
		}
		while(y!=1)
		{	if(mp[y]) {printf("%lld\n",y);goto ext;}
			y=y-fib[k2-1];
			while(fib[k2-1]>=y) k2--;
		}
		printf("1\n"); ext:;
	}
 	return 0;
}



