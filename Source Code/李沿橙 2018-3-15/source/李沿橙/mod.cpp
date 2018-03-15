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
	bool positive = true;
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
	do buffer[length++] = -(x % 10) + '0';
	while (x /= 10);
	do putchar(buffer[--length]);
	while (length);
	putchar('\n');
}

LL n, m;

#define RunInstance(x) delete new x
struct brute
{
	brute()
	{
		LL ans = 0;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				ans += (i % j >= m);
		printOut(ans);
	}
};
struct cheat
{
	cheat()
	{
		LL ans = 0;
		if (m == 0)
		{
			printOut((LL)n * n);
			return;
		}
		for (int j = m + 1; j <= n; j++)
			ans += (LL)((n + 1) / j) * (j - m) + std::max(0ll, (n + 1) % j - m);
		printOut(ans);
	}
};
struct work
{
	work()
	{
		if (m == 0)
		{
			printOut((LL)n * n);
			return;
		}
		else if (m >= n)
		{
			printOut(0);
			return;
		}
		LL ans = 0;
		LL to = n + 1;
		for (LL j = m + 1, t; j <= n; j = t + 1)
		{
			t = std::min((LL)n, to / (to / j));
			ans += (LL)(to / j) * (j - m + t - m) * (t - j + 1) / 2;
		}
		for (LL j = m + 1, t; j <= n; j = t + 1)
		{
			t = std::min((LL)n, to / (to / j));
			LL cnt = (to - m) / (to / j);
			cnt = std::min(cnt, t);
			if (cnt >= j)
			{
				ans += (LL)(to - m) * (cnt - j + 1) - (LL)(to / j) * (j + cnt) * (cnt - j + 1) / 2;
			}
		}
		printOut(ans);
	}
};

void run()
{
	int T = readIn();
	while (T--)
	{
		n = readIn();
		m = readIn();
		if (n <= 100)
			RunInstance(brute);
		else if (n <= 100000)
			RunInstance(cheat);
		else
			RunInstance(work);
	}
}

int main()
{
#ifndef LOCAL
	freopen("mod.in", "r", stdin);
	freopen("mod.out", "w", stdout);
#endif
	run();
	return 0;
}