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
}

const int mod = int(1e9) + 7;
const int maxn = 2005;
int n;
int a[maxn];
int pos[maxn];

#define RunInstance(x) delete new x
struct brute
{
	int c[2][305];
	brute()
	{
		LL ans = 0;
		int U = 1 << pos[0];
		for (register int S = 0; S < U; S++)
		{
			for (register int i = 0; i < pos[0]; i++)
				a[pos[i + 1]] = bool(S & (1 << i));

			for (register int i = 1; i <= n; i++)
			{
				c[a[i]][i] = 1;
				c[a[i] ^ 1][i] = 0;
			}
			c[0][0] = c[1][0] = c[0][n + 1] = c[1][n + 1] = 0;
			for (register int i = 1; i <= n; i++)
				c[0][i] += c[0][i - 1];
			for (register int i = n; i; i--)
				c[1][i] += c[1][i + 1];
			int len = -1;
			int y;
			for (register int i = 0; i <= n; i++)
			{
				if (c[0][i] + c[1][i + 1] > len)
				{
					len = c[0][i] + c[1][i + 1];
					y = c[1][i + 1];
				}
			}
			ans = (ans + (LL)len * y) % mod;
		}
		printOut(ans);
	}
};

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
	{
		a[i] = readIn();
		if (a[i] == -1)
			pos[++pos[0]] = i;
	}

	if (pos[0] <= 25)
		RunInstance(brute);
}

int main()
{
#ifndef LOCAL
	freopen("calc.in", "r", stdin);
	freopen("calc.out", "w", stdout);
#endif
	run();
	return 0;
}