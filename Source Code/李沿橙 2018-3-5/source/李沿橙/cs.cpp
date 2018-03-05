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
typedef int INT_PUT;
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

const int maxn = int(1e5) + 5;
int n, p;
int a[maxn];

#define RunInstance(x) delete new x
struct brute
{
	static const int maxN = 15;
	int per[maxN];
	int minDelta;
	int ans[maxN];

	brute() : minDelta(n + 1)
	{
		for (int i = 1; i <= n; i++)
			per[i] = i;
		do
		{
			int score = 0;
			for (int i = 2; i <= n; i++)
			{
				if (score * n < a[per[i]] * (i - 1))
					score++;
			}
			int t;
			if ((t = std::abs(p - score)) < minDelta)
			{
				minDelta = t;
				memcpy(ans, per, sizeof(ans));
			}
		} while (std::next_permutation(per + 1, per + 1 + n));
		for (int i = 1; i <= n; i++)
		{
			printOut(ans[i]);
			putchar(' ');
		}
	}
};
struct cheat
{
	int idx[maxn];

	static bool comp(const int& x, const int& y)
	{
		return a[x] > a[y];
	}

	cheat()
	{
		for (int i = 1; i <= n; i++)
			idx[i] = i;
		std::sort(idx + 1, idx + 1 + n, comp);
		for (int i = 1; i <= n; i++)
		{
			printOut(idx[i]);
			putchar(' ');
		}
	}
};
struct work
{
	int idx[maxn];

	static bool comp(const int& x, const int& y)
	{
		return a[x] > a[y];
	}

	bool check(int s)
	{
		int score = 0;
		for(int i = 1; i <= s; i++)
		{
			if (score * n < a[idx[i]] * (i - 1))
				score++;
		}
		for(int i = n; i > s; i--)
		{
			if (score * n < a[idx[i]] * (i - 1))
				score++;
		}
		return score;
	}

	work()
	{
		for (int i = 1; i <= n; i++)
			idx[i] = i;
		std::sort(idx + 1, idx + 1 + n, comp);

		int l = 0, r = n;
		while(r - l > 0)
		{
			int mid = (l + r) >> 1;
			if(check(mid) >= p)
				l = mid + 1;
			else
				r = mid;
		}

		if(std::abs(check(l + 1) - p) < std::abs(check(l) - p))
			l++;

		for(int i = 1; i <= l; i++)
		{
			printOut(idx[i]);
			putchar(' ');
		}
		for(int i = n; i > l; i--)
		{
			printOut(idx[i]);
			putchar(' ');
		}
	}
};

void run()
{
	n = readIn();
	p = readIn();
	for (int i = 1; i <= n; i++)
		a[i] = readIn();

	if (n <= 10)
		RunInstance(brute);
	else if (!p)
		RunInstance(cheat);
	else
		RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("cs.in", "r", stdin);
	freopen("cs.out", "w", stdout);
#endif
	run();
	return 0;
}
