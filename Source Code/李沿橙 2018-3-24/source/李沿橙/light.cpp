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
typedef LL INT_PUT;
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
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
	putchar('\n');
}

const int maxn = int(5e4) + 5;
int n, g, r;
LL sum;
int d[maxn];
int q;
int querys[maxn];

#define RunInstance(x) delete new x
struct brute
{
	brute()
	{
		for (int i = 1; i <= q; i++)
		{
			LL start = querys[i];
			for (int j = 1; j <= n + 1; j++)
			{
				LL t;
				if ((t = start % sum) < g)
					start += d[j];
				else
					start += sum - t + d[j];
			}
			printOut(start);
		}
	}
};
struct cheat1
{
	LL f[maxn][205];
	cheat1() : f()
	{
		for (int i = n + 1; i; i--)
		{
			for (int j = 0; j < g; j++)
				f[i][j] = f[i + 1][(j + d[i]) % sum] + d[i];
			for (int j = g; j < sum; j++)
				f[i][j] = f[i + 1][d[i] % sum] + d[i] + sum - j;
		}
		for (int i = 1; i <= q; i++)
			printOut(f[1][querys[i] % sum] + querys[i]);
	}
};

void run()
{
	n = readIn();
	g = readIn();
	r = readIn();
	sum = g + r;
	for (register int i = 1, to = n + 1; i <= to; i++)
		d[i] = readIn();
	q = readIn();
	for (register int i = 1; i <= q; i++)
		querys[i] = readIn();

	if (n <= 1000 && q <= 1000)
		RunInstance(brute);
	else if (g <= 100 && r <= 100)
		RunInstance(cheat1);
	else
		RunInstance(brute);
}

int main()
{
#ifndef LOCAL
	freopen("light.in", "r", stdin);
	freopen("light.out", "w", stdout);
#endif
	run();
	return 0;
}