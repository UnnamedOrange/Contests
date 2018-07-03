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
	while (!(std::isdigit(ch) || ch == '-')) ch = getchar();
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

int n, mod;
LL power(LL x, int y)
{
	LL ret = 1;
	while (y)
	{
		if (y & 1) ret = ret * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return ret;
}

#define RunInstance(x) delete new x
struct brute1
{
	int count1[1 << 20];
	int f[1 << 20];

	static inline int reset(int S, int bit)
	{
		return S & ~(1 << bit);
	}

	brute1()
	{
		int U = 1 << n;
		count1[0] = 0;
		for (int S = 1; S < U; S++)
			count1[S] = count1[S ^ (S & -S)] + 1;

		f[0] = 0;
		for (int S = 1; S < U; S++)
		{
			if (count1[S] == 1)
			{
				f[S] = 1;
				continue;
			}
			int& ans = f[S];
			ans = 0;
			for (int i = 1; i <= n; i++)
			{
				if (S & (1 << (i - 1)))
				{
					int T = S;
					for (int j = i; j <= n; j += i)
						T = reset(T, j - 1);
					ans = (ans + f[T]) % mod;
				}
			}
			ans = ((LL)ans * power(count1[S], mod - 2) + 1) % mod;
		}
		printOut(f[U - 1]);
	}
};
struct brute2
{
	static const int maxn = int(1e6) + 5;
	int sigma0[maxn];
	int inv[maxn];

	brute2() : sigma0()
	{
		for (register int i = 1; i <= n; i++)
			for (register int j = i; j <= n; j += i)
				sigma0[j]++;
		inv[1] = 1;
		for (int i = 2, to = *std::max_element(sigma0 + 1, sigma0 + 1 + n); i <= to; i++)
			inv[i] = (LL)(mod - mod / i) * inv[mod % i] % mod;

		int ans = 0;
		for (int i = 1; i <= n; i++)
			ans = (ans + inv[sigma0[i]]) % mod;
		printOut(ans);
	}
};
struct cheat
{


	cheat()
	{

	}
};

void run()
{
	n = readIn();
	mod = readIn();

	if (n <= 20)
		RunInstance(brute1);
	else if (n <= int(1e6))
		RunInstance(brute2);
}

int main()
{
#ifndef LOCAL
	freopen("lakers.in", "r", stdin);
	freopen("lakers.out", "w", stdout);
#endif
	run();
	return 0;
}