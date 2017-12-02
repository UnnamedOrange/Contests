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
#include <bitset>
using std::cin;
using std::cout;
using std::endl;
typedef long long INT;
inline INT readIn()
{
	INT a = 0;
	bool minus = false;
	char ch = getchar();
	while(!(ch == '-' || ch >= '0' && ch <= '9')) ch = getchar();
	if(ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9')
	{
		a *= 10;
		a += ch;
		a -= '0';
		ch = getchar();
	}
	if(minus) a = -a;
	return a;
}

const INT INF = ~(INT(1) << (sizeof(INT) * 8 - 1));
const INT maxn = INT(2e6) + 5;
INT n;
INT num[maxn];

#define RunInstance(x) delete new x

struct work
{
	INT change[maxn]; //当循环到i时有多少个数由负数变成非负 
	
	INT getChangePoint(INT pos, INT val)
	{
		if(val < pos) return pos - val;
		else return n - (val - pos);
	}

	work() : change()
	{
		INT sum = 0;
		INT nonNegative = 0;
		for(int i = 1; i <= n; i++) change[getChangePoint(i, num[i])]++;
		for(int i = 1; i <= n; i++)
		{
			if(num[i] >= i)
			{
				sum += num[i] - i;
				nonNegative++;
			}
			else
			{
				sum += i - num[i];
			}
		}
		INT ans = sum;
		for(int i = 1; i < n; i++)
		{
			//把1移动到n 
			nonNegative--;
			sum -= std::abs(num[i] - 1);
			sum += std::abs(num[i] - n);
			
			//把其它的向前移动
			sum += nonNegative - (n - 1 - nonNegative);
			ans = std::min(ans, sum);
			
			//更新nonNegative 
			nonNegative += change[i];
		}
		cout << ans << endl;
	}
};
struct cheat2
{
		class BIT
		{
#define fit(x) ((x) + 2000001)
#define lowbit(x) ((x) & -(x))
				static const INT range = 4000001;
				INT bit[range + 5];

			public:
				static const INT maxVal = 2000000;
				BIT() : bit() {}
				void add(INT x, INT toAdd)
				{
					x = fit(x);
					while(x <= range)
					{
						bit[x] += toAdd;
						x += lowbit(x);
					}
				}
				INT query(INT x)
				{
					INT ans = 0;
					x = fit(x);
					while(x > 0)
					{
						ans += bit[x];
						x -= lowbit(x);
					}
					return ans;
				}
				INT query(INT l, INT r)
				{
					return query(r) - query(l - 1);
				}
		} bit1, size1, bit2, size2;

		cheat2()
		{
			INT ans = 0;
			for(int i = 1; i <= n; i++)
			{
				num[i] -= i;
				ans += std::abs(num[i]);

				bit1.add(num[i], num[i]);
				size1.add(num[i], 1);
			}

#ifdef JUDGE
			cout << ans << endl;
#endif

			for(int i = 1; i < n; i++)
			{
				bit1.add(num[i], -num[i]);
				size1.add(num[i], -1);
				bit2.add(num[i], num[i]);
				size2.add(num[i], 1);

				INT sum = 0;
				sum += -(bit1.query(-i) + size1.query(-i) * i);
				sum += bit1.query(-i + 1, BIT::maxVal) + size1.query(-i + 1, BIT::maxVal) * i;
				INT j = n - i;
				sum += -(bit2.query(j) - size2.query(j) * j);
				sum += bit2.query(j + 1, BIT::maxVal) - size2.query(j + 1, BIT::maxVal) * j;

#ifdef JUDGE
				cout << sum << endl;
#endif

				ans = std::min(ans, sum);
			}
			cout << ans << endl;
		}
};
struct cheat1
{
	cheat1()
	{
		INT ans = INF;
		for(int i = 1; i <= n; i++)
		{
			INT sum = 0;
			for(int j = i, k = 1; k <= n; k++)
			{
				sum += std::abs(num[j] - k);

				j++;
				if(j > n) j = 1;
			}

#ifdef JUDGE
			cout << sum << endl;
#endif

			ans = std::min(ans, sum);
		}
		cout << ans << endl;
	}
};
void run()
{
	n = readIn();
	for(int i = 1; i <= n; i++)
	{
		num[i] = readIn();
	}
	if(n <= 1000) RunInstance(cheat1);
	else if(n <= 100000) RunInstance(cheat2);
	else RunInstance(work);
}

int main()
{
#ifndef JUDGE
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
#endif
	run();
	return 0;
}
