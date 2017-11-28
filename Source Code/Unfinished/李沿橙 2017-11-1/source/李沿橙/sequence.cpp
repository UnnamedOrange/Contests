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
typedef int INT;
using std::cin;
using std::cout;
using std::endl;
INT readIn()
{
	INT a = 0;
	bool minus = false;
	char ch = getchar();
	while (!(ch == '-' || (ch >= '0' && ch <= '9'))) ch = getchar();
	if (ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		a = a * 10 + (ch - '0');
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}
void printOut(INT x)
{
	static char buffer[20];
	INT length = 0;
	bool minus = x < 0;
	if (minus) x = -x;
	do
	{
		buffer[length++] = x % 10 + '0';
		x /= 10;
	} while (x);
	if (minus) buffer[length++] = '-';
	do
	{
		putchar(buffer[--length]);
	} while (length);
	putchar('\n');
}

const INT maxn = 30;
INT n;
INT a[maxn];

#define RunInstance(x) delete new x
void reverse(INT x[], INT r)
{
	INT to = (1 + r) >> 1;
	for (int i = 1; i <= to; i++)
		std::swap(x[i], x[r - i + 1]);
}
INT check(INT x[])
{
	for (int i = n; i >= 1; i--)
		if (x[i] != i)
			return i;
	return 0;
}

#define RunInstance(x) delete new x
struct work
{
	bool found;
	INT maxd;

	void search(INT nei, INT depth = 0, INT pre = 0)
	{
		INT c = check(a);
		if (depth == maxd)
		{
			if (!c)
				found = true;
			return;
		}
		if (depth + nei > maxd) return;
		for (int i = 1; i <= c; i++)
		{
			if (i == pre) continue;
			reverse(a, i);
			search(nei + (i < n && std::abs(a[i] - a[i + 1]) > 1) - (i < n && std::abs(a[1] - a[i + 1]) > 1), depth + 1, i);
			if (found) return;
			reverse(a, i);
		}
	}

	work() : found()
	{
		INT nei = 0;
		for (int i = 1; i < n; i++) nei += std::abs(a[i] - a[i + 1]) > 1;
		for (maxd = nei; ; maxd++)
		{
			search(nei);
			if (found)
			{
				printOut(maxd);
				break;
			}
		}
	}
};

void run()
{
	INT T = readIn();
	while (T--)
	{
		n = readIn();
		for (int i = 1; i <= n; i++)
			a[i] = readIn();

		RunInstance(work);
	}
}

int main()
{
#ifndef JUDGE
	freopen("sequence.in", "r", stdin);
	freopen("sequence.out", "w", stdout);
#endif
	run();
	return 0;
}
