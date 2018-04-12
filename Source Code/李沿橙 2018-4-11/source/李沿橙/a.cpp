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
		(a *= 10) -= ch - '0';
		ch = getchar();
	}
	return positive ? -a : a;
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

const int maxn = int(2e5) + 10;
int n, p1 = true;
char str[maxn];
int a[maxn];

#define RunInstance(x) delete new x
struct brute
{
	brute()
	{
		for (int i = 2; i <= n; i++)
			a[i] += a[i - 1];

		LL ans = 0;

		for (int i = 1; i <= n; i++)
			for (int j = i + 1; j <= n; j++)
			{
				if (!str[j]) continue;
				for (int k = j + 1; k <= n; k++)
					if (a[k] - a[j - 1] == a[j] - a[i - 1])
						ans++;
			}
		printOut(ans);
	}
};
struct cheat
{
	cheat()
	{
		LL ans = 0;
		for (int i = 0; i < n; i++)
			ans += (i >> 1);
		printOut(ans);
	}
};
struct work
{
	int nCode;
	int f[maxn];

	work() : nCode(-1), f()
	{
		for (int i = 0; i <= n; i++)
		{
			if (!i || a[i]) nCode++;
			f[nCode]++;
		}

		LL ans = 0;
		LL odd = 0;
		LL even = 0;
		for (int i = 3; i <= nCode; i += 2)
			odd += f[i];
		for (int i = 4; i <= nCode; i += 2)
			even += f[i];

		for (int i = 0; i + 1 <= nCode; i += 2)
		{
			ans += (LL)(f[i] - 1) * (f[i + 1] - 1);
			ans += (LL)f[i] * odd;
			odd -= f[i + 3];
		}

		for (int i = 1; i + 1 <= nCode; i += 2)
		{
			ans += (LL)(f[i] - 1) * (f[i + 1] - 1);
			ans += (LL)f[i] * even;
			even -= f[i + 3];
		}
		printOut(ans);
	}
};

void run()
{
	n = readIn();
	scanf("%s", str + 1);
	for (int i = 1; i <= n; i++)
	{
		a[i] = str[i] -= '0';
		if (!a[i]) p1 = false;
	}

	if (n <= 300)
		RunInstance(brute);
	else if (p1)
		RunInstance(cheat);
	else
		RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
#endif
	run();
	return 0;
}