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
typedef int INT_PUT;
INT_PUT readIn()
{
	INT_PUT a = 0;
	int positive = true;
	char ch = getchar();
	while (!(ch == '-' || std::isdigit(ch))) ch = getchar();
	if (ch == '-')
	{
		positive = false;
		ch = getchar();
	}
	while (std::isdigit(ch))
	{
		a = a * 10 - (ch - '0');
		ch = getchar();
	}
	if (positive) a = -a;
	return a;
}
void printOut(INT_PUT x)
{
	char buffer[20];
	int length = 0;
	if (x < 0) putchar('-');
	else x = -x;
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
	putchar('\n');
}

const long double Div = 1e140;
const long double threshold = Div * Div;
const int maxn = int(2e5) + 5;
int n, m;
int a[maxn];

#define RunInstance(x) delete new x
struct brute
{
	brute()
	{
		while (m--)
		{
			int ins = readIn();
			int l = readIn();
			int r = readIn();
			if (ins == 1)
			{
				int t = readIn();
				if (t) std::sort(a + l, a + r + 1);
				else std::sort(a + l, a + r + 1, std::greater<int>());
			}
			else if (ins == 2)
			{
				long double t = 1;
				for (int i = l; i <= r; i++)
				{
					t *= a[i];
					if (t > threshold) t /= Div;
				}
				printOut(t / std::pow(10, std::floor(std::log10(t))));
			}
		}
	}
};
struct cheat
{
	class SegTree
	{
		static inline int code(int l, int r)
		{
			return (l + r) | (l != r);
		}
		long double mul[maxn * 2];

#define PARAM int l, int r

		int g_L, g_R;
		long double query_(PARAM)
		{
			if (g_L <= l && r <= g_R)
			{
				return mul[code(l, r)];
			}
			int mid = (l + r) >> 1;
			long double ret = 1;
			if (g_L <= mid) ret *= query_(l, mid);
			if (g_R > mid) ret *= query_(mid + 1, r);
			if (ret >= threshold) ret /= Div;
			return ret;
		}

	public:
		void build(PARAM)
		{
			if (l == r)
			{
				mul[code(l, r)] = a[l];
				return;
			}
			int mid = (l + r) >> 1;
			build(l, mid);
			build(mid + 1, r);
			long double& ans = mul[code(l, r)];
			ans = mul[code(l, mid)] * mul[code(mid + 1, r)];
			if (ans >= threshold) ans /= Div;
		}
		long double query(int l, int r)
		{
			g_L = l;
			g_R = r;
			return query_(1, n);
		}
	} st;
	cheat()
	{
		st.build(1, n);
		while (m--)
		{
			int ins = readIn();
			int l = readIn();
			int r = readIn();
			if (ins == 1) readIn();
			else if (ins == 2)
			{
				long double t = st.query(l, r);
				printOut(t / std::pow(10, std::floor(std::log10(t))));
			}
		}
	}
};

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= n; i++)
		a[i] = readIn();
	if (n <= 1000 && m <= 1000)
		RunInstance(brute);
	else
		RunInstance(cheat);
}

int main()
{
#ifndef LOCAL
	freopen("zkb.in", "r", stdin);
	freopen("zkb.out", "w", stdout);
#endif
	run();
	return 0;
}