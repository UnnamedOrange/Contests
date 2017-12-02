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

const ll maxn = 230;
ll m;
ll pre[maxn];
ll Index[maxn];

ll turt(ll num)
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

ll count_(ll num)
{
	ll from = turt(num);
	ll ans = 0;
	for(ll i = from; i >= 1; i--)
	{
		ll size = i * i * i;
		//if(num / size) printf("%lld*%lld ",num/size, size);
		ans += num / size;
		num %= size;
	}
	//puts("");
	return ans;
}

void run()
{
	cin >> m;
	ll ans1 = 0;
	ll ans2 = 0;
	for(int i = 1; i <= m; i++)
	{
		if(count_(i) >= ans1)
		{
			ans1=count_(i);
			ans2 = i;
		}
	}
	cout<<ans1<<" "<<ans2<<endl;
	
	
}

int main()
{
	run();
	return 0;
}
