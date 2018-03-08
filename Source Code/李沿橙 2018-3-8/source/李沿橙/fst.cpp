#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cassert>
#include <cctype>
#include <climits>
#include <ctime>
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
#include <list>
#include <functional>
typedef long long LL;
typedef unsigned long long ULL;
using std::cin;
using std::cout;
using std::endl;
typedef long long INT_PUT;
INT_PUT readIn()
{
	INT_PUT a = 0;
	bool minus = false;
	char ch = getchar();
	while (!(ch == '-' || std::isdigit(ch))) ch = getchar();
	if (ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while (std::isdigit(ch))
	{
		a = a * 10 + (ch - '0');
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}
void printOut(INT_PUT x)
{
	char buffer[40];
	int length = 0;
	if (x < 0)
	{
		putchar('-');
		x = -x;
	}
	do
	{
		buffer[length++] = x % 10 + '0';
	} while (x /= 10);
	do
	{
		putchar(buffer[--length]);
	} while (length);
}

const int maxn = 30005;
int n, r, k;
LL a[3][maxn];

#define RunInstance(x) delete new x
struct brute
{
	static const int maxN = 505;
	LL sum[maxN * maxN];

	brute() : sum()
	{
		int to = n - r + 1;
		for (int x = 1; x <= to; x++)
		{
			for (int y = x + 1; y <= to; y++)
			{
				LL& ans = sum[++sum[0]];
				ans = 0;
				for (int i = 1; i <= n; i++)
				{
					int cnt = 0;
					if (x <= i && i <= x + r - 1) cnt++;
					if (y <= i && i <= y + r - 1) cnt++;
					ans += a[cnt][i];
				}
			}
		}
		std::nth_element(sum + 1, sum + k, sum + 1 + sum[0]);
		printOut(sum[k]);
	}
};
struct work
{
	int bound;
	
	struct BIT
	{
		int bit[maxn * 2];
		static inline int lowbit(int x)
		{
			return x & -x;
		}
		void add(int pos, int val)
		{
			while (pos <= bound)
			{
				bit[pos] += val;
				pos += lowbit(pos);
			}
		}
		int query(int pos)
		{
			int ret = 0;
			while (ret)
			{
				ret += bit[pos];
				pos ^= lowbit(pos);
			}
			return ret;
		}
		int query(int l, int r)
		{
			return query(r) - query(l - 1);
		}
	} bit;
	

	static bool check(LL s)
	{
		LL sum1 = 0;
		for (int i = 1; i <= r; i++)
		{
			
		}
	}
	work()
	{
		for (int i = 2; i <= n; i++)
		{
			a[0][i] += a[0][i - 1];
			a[1][i] += a[1][i - 1];
			a[2][i] += a[2][i - 1];
		}

		LL l = 0, r = 0;
		for (int i = 1; i <= n; i++) l += a[0][i];
		for (int i = 1; i <= n; i++) r += a[2][i];
		r++;

		while (r - l > 1)
		{
			LL mid = l + ((r - l) >> 1);
			if (check(mid) <= k)
				l = mid;
			else
				r = mid;
		}
		printOut(l);
	}
};

void run()
{
	n = readIn();
	r = readIn();
	k = readIn();
	for (int i = 1; i <= n; i++) a[0][i] = readIn();
	for (int i = 1; i <= n; i++) a[1][i] = readIn();
	for (int i = 1; i <= n; i++) a[2][i] = readIn();

	if (n <= 500)
		RunInstance(brute);
	else
		RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("fst.in", "r", stdin);
	freopen("fst.out", "w", stdout);
#endif
	run();
	return 0;
}