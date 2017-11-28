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
#include <functional>
typedef long long INT;
using std::cin;
using std::cout;
using std::endl;
inline INT readIn()
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
		a = a * 10 + ch - '0';
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}
inline void printOut(INT x)
{
	if (!x)
	{
		putchar('0');
	}
	else
	{
		char buffer[12];
		INT length = 0;
		bool minus = x < 0;
		if (minus) x = -x;
		while (x)
		{
			buffer[length++] = x % 10 + '0';
			x /= 10;
		}
		if (minus) buffer[length++] = '-';
		do
		{
			putchar(buffer[--length]);
		} while (length);
	}
	putchar('\n');
}

INT gcd(INT a, INT b)
{
	return !b ? a : gcd(b, a % b);
}

#define RunInstance(x) delete new x
INT n, m, mod;
struct cheat1
{
	cheat1()
	{
		INT ans = 0;
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= m; j++)
			{
				if (gcd(i, j) == 1)
				{
					ans = (ans + std::min(n / i, m / j)) % mod;
				}
			}
		}
		printOut(ans);
	}
};
struct work
{
	work()
	{
		printOut(n * m % mod);
	}
};

void run()
{
	n = readIn();
	m = readIn();
	mod = readIn();
	if (n <= 2000 && m <= 2000)
		RunInstance(cheat1);
	else
		RunInstance(work);
}

int main()
{
#ifndef JUDGE
	freopen("math.in", "r", stdin);
	freopen("math.out", "w", stdout);
#endif
	run();
	return 0;
}
