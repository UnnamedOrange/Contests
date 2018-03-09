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
LL a[maxn], b[maxn], c[maxn];

#define RunInstance(x) delete new x
struct work
{
	struct BIT
	{
		int bound;
		int bit[maxn];
		BIT() : bit() {}
		static inline int lowbit(int x)
		{
			return x & -x;
		}
		void add(int pos, int val)
		{
			while (pos < bound)
			{
				bit[pos] += val;
				pos += lowbit(pos);
			}
		}
		int query(int pos)
		{
			int ret = 0;
			while (pos)
			{
				ret += bit[pos];
				pos ^= lowbit(pos);
			}
			return ret;
		}
		int query(int l, int r)
		{
			if (l == r + 1) return 0;
			if (!l) return query(r);
			return query(r) - query(l - 1);
		}
		void clear(int bound)
		{
			memset(bit, 0, sizeof(int) * (bound + 1));
			this->bound = bound;
		}
	} bit;
	LL disc1[maxn];
	LL disc2[maxn];
	void discretize()
	{
		std::sort(disc1 + 1, disc1 + 1 + disc1[0]);
		disc1[0] = std::unique(disc1 + 1, disc1 + 1 + disc1[0]) - (disc1 + 1);
		std::sort(disc2 + 1, disc2 + 1 + disc2[0]);
		disc2[0] = std::unique(disc2 + 1, disc2 + 1 + disc2[0]) - (disc2 + 1);
	}
	LL calc1(int j)
	{
		return a[j - 1] + b[j + r - 1] - b[j - 1] - a[j + r - 1];
	}
	LL calc2(int j)
	{
		return b[j - 1] - c[j - 1] + b[j + r - 1] - a[j + r - 1];
	}
	int code1(LL val)
	{
		return std::upper_bound(disc1 + 1, disc1 + 1 + disc1[0], val) - 1 - disc1;
	}
	int code2(LL val)
	{
		return std::upper_bound(disc2 + 1, disc2 + 1 + disc2[0], val) - 1 - disc2;
	}
	LL v1[maxn];
	LL v2[maxn];
	int dis1[maxn];
	int dis2[maxn];
	LL sub1[maxn];
	LL sub2[maxn];
	LL check(LL s)
	{
		LL ret = 0;
		bit.clear(disc1[0] + 10);
		for (int i = n - r - r + 1; i >= 1; i--)
		{
			bit.add(dis1[i + r], 1);
			ret += bit.query(code1(s - sub1[i]));
		}
		bit.clear(disc2[0] + 10);
		for (int i = 2, to = std::min(r, n - r + 1); i <= to; i++)
			bit.add(dis2[i], 1);
		for (int i = 1; i < n - r + 1; i++)
		{
			ret += bit.query(code2(s - sub2[i]));
			if (i + r <= n - r + 1) bit.add(dis2[i + r], 1);
			bit.add(dis2[i + 1], -1);
		}
		return ret;
	}
	work()
	{
		for (int i = 2; i <= n; i++)
		{
			a[i] += a[i - 1];
			b[i] += b[i - 1];
			c[i] += c[i - 1];
		}
		disc1[0] = disc2[0] = 0;
		for (int i = r + 1, to = n - r + 1; i <= to; i++)
			disc1[++disc1[0]] = v1[i] = calc1(i);
		for (int i = 2, to = n - r + 1; i <= to; i++)
			disc2[++disc2[0]] = v2[i] = calc2(i);
		discretize();

		for (int i = r + 1, to = n - r + 1; i <= to; i++)
			dis1[i] = code1(v1[i]);
		for (int i = 2, to = n - r + 1; i <= to; i++)
			dis2[i] = code2(v2[i]);
		for (int i = n - r - r + 1; i >= 1; i--)
			sub1[i] = a[n] + (a[i - 1] + b[i + r - 1] - b[i - 1] - a[i + r - 1]);
		for (int i = 1; i < n - r + 1; i++)
			sub2[i] = a[n] + (a[i - 1] - b[i - 1] + c[i + r - 1] - b[i + r - 1]);

		LL left = a[n], right = c[n];
		while (right - left > 0)
		{
			LL mid = left + ((right - left) >> 1);
			if (check(mid) < k)
				left = mid + 1;
			else
				right = mid;
		}
		printOut(right);
	}
};

void run()
{
	n = readIn();
	r = readIn();
	k = readIn();
	for (int i = 1; i <= n; i++) a[i] = readIn();
	for (int i = 1; i <= n; i++) b[i] = readIn();
	for (int i = 1; i <= n; i++) c[i] = readIn();

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