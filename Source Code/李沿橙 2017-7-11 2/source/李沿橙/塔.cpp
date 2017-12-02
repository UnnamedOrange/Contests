#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <deque>
#include <map>
#include <set>
using std::cin;
using std::cout;
using std::endl;
inline int readIn()
{
	int a;
	scanf("%d", &a);
	return a;
}
typedef unsigned long long ll;
ll m;

ll tqrt(ll num)
{
	ll l = 1, r = 1e5+1;
	while(r - l > 1)
	{
		ll mid = l + (r - l) / 2;
		if(mid * mid * mid < num)
		{
			l = mid;
		}
		else
		{
			r = mid;
		}
	}
	if((l + 1) * (l + 1) * (l + 1) <= num) l++;
	return l;
}

int f(ll m, ll& x)
{
	ll a = turt(m);
	if(a == 1)
	{
		x += m;
		return m;
	}
	ll y=0,z=0;
	int ans1 = f(m - a*a*a,y) + 1;
	int ans2 = f(a*a*a-1-(a-1)*(a-1)*(a-1),z) + 1;
	if(ans1 >= ans2)
	{
		x = a*a*a + y;
		return ans1;
	}
	else
	{
		x = (a-1) * (a-1) * (a-1) + z;
		return ans2;
	}
}

void run()
{
	cin >> m;
	ll x = 0;
	printf("%d ", f(m, x));
	cout<<x<<endl;
}

int main()
{
	run();
	return 0;
}
