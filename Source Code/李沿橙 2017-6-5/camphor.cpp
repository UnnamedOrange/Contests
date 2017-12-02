#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <map>
#include <set>
using std::cin;
using std::cout;
using std::endl;

const int maxn=100005;
int n;
int num[maxn];

namespace Regular
{
	int gcd(int a,int b)
	{
		if(b==0) return a;
		return gcd(b,a%b);
	}
	bool isCoprime(int a,int b)
	{
		return gcd(a,b)==1;
	}

	void run()
	{
		int ans=1;
		std::vector<int> f(n+1,1);
		for(int i=2; i<=n; i++)
		{
			for(int j=1; j<i; j++)
			{
				if(!isCoprime(num[i],num[j]))
				{
					f[i]=std::max(f[i],f[j]+1);
				}
			}
			ans=std::max(ans,f[i]);
		}
		printf("%d",ans);
	}
	void input()
	{
		scanf("%d",&n);
		for(int i=1; i<=n; i++)
		{
			scanf("%d",&num[i]);
		}
	}
}

int main()
{
#ifndef DEBUG
	freopen("camphor.in","r",stdin);
	freopen("camphor.out","w",stdout);
#endif
	Regular::input();
	Regular::run();
	return 0;
}
