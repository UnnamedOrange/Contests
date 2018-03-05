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
	while (!(ch == '-' || isdigit(ch))) ch = getchar();
	if (ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while (isdigit(ch))
	{
		a = a * 10 + (ch - '0');
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}
void printOut(INT_PUT x)
{
	char buffer[20];
	int length = 0;
	if (x < 0)
	{
		putchar('-');
		x = -x;
	}
	do
	{
		buffer[length++] = x % 10 + '0';
		x /= 10;
	} while (x);
	do
	{
		putchar(buffer[--length]);
	} while (length);
}

const int maxn = 200005;
int n, q;
LL m;
int a[maxn];
int b[maxn];

#define RunInstance(x) delete new x
struct brute
{
	int pos[maxn];

	brute()
	{
		for (int i = 1; i <= n; i++)
			pos[a[i]] = i;

		for (int i = 1, j = 0; i <= m; i++, j = (j + 1 == q ? 0 : j + 1))
		{
			int v = b[j];
			int p = pos[v];
			std::swap(pos[a[1]], pos[v]);
			std::swap(a[1], a[p]);
		}

		for (int i = 1; i <= n; i++)
		{
			printOut(a[i]);
			putchar(' ');
		}
	}
};
struct work
{
	int pos[maxn];

	struct Permutation
	{
		std::vector<int> c;
		Permutation() : c(n + 1)
		{
			for (int i = 1; i <= n; i++)
				c[i] = i;
		}
		Permutation(bool) : c(n + 1) {}
		void operator*= (const std::pair<int, int>& p)
		{
			std::swap(c[p.first], c[p.second]);
		}
		Permutation operator* (const Permutation& p) const
		{
			Permutation ret(true);
			for (int i = 1; i <= n; i++)
				ret.c[i] = p.c[c[i]];
			return ret;
		}
		void GetResult()
		{
			Permutation temp(*this);
			for (int i = 1; i <= n; i++)
				c[temp.c[i]] = i;
		}
		Permutation operator^ (LL y) const
		{
			Permutation ret;
			Permutation x = *this;
			while (y)
			{
				if (y & 1) ret = ret * x;
				x = x * x;
				y >>= 1;
			}
			return ret;
		}
	} per;

	int ansPos[maxn];
	int ans[maxn];

	work()
	{
		for (int i = 1; i <= n; i++)
			pos[a[i]] = i;
		m--;

		for (int i = 1; i < q; i++)
			per *= std::make_pair(b[i - 1], b[i]);
		per *= std::make_pair(b[q - 1], b[0]);
		per.GetResult(); // note
		per = per ^ (m / q);
		per.GetResult(); // note
		m %= q;
		for (int i = 1; i <= m; i++)
			per *= std::make_pair(b[i - 1], b[i]);
		per.GetResult();

		std::swap(pos[a[1]], pos[b[0]]);
		for (int i = 1; i <= n; i++)
			ansPos[per.c[i]] = pos[i];
		for (int i = 1; i <= n; i++)
			ans[ansPos[i]] = i;
		for (int i = 1; i <= n; i++)
		{
			printOut(ans[i]);
			putchar(' ');
		}
	}
};

void run()
{
	n = readIn();
	q = readIn();
	m = readIn();
	for (int i = 1; i <= n; i++)
		a[i] = readIn();
	for (int i = 0; i < q; i++)
		b[i] = readIn();

	if (m <= int(1e6))
		RunInstance(brute);
	else
		RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("sim.in", "r", stdin);
	freopen("sim.out", "w", stdout);
#endif
	run();
	return 0;
}