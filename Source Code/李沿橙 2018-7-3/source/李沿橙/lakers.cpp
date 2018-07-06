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
	INT_PUT a = 0; bool positive = true;
	char ch = getchar();
	while (!(ch == '-' || std::isdigit(ch))) ch = getchar();
	if (ch == '-') { positive = false; ch = getchar(); }
	while (std::isdigit(ch)) { a = a * 10 - (ch - '0'); ch = getchar(); }
	return positive ? -a : a;
}
void printOut(INT_PUT x)
{
	char buffer[20]; int length = 0;
	if (x < 0) putchar('-'); else x = -x;
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
}

int mod;

struct Min_25
{
	static const int maxn = 32000;
	bool isntprime[maxn + 5];
	int prime[3433];
	int inv[maxn + 5];
	static LL power(LL x, int y)
	{
		LL ret = 1;
		while (y)
		{
			if (y & 1) ret = ret * x % mod;
			x = x * x % mod;
			y >>= 1;
		}
		return y;
	}
	Min_25() : isntprime()
	{
		prime[0] = 0;
		isntprime[1] = true;
		for (int i = 2; i <= maxn; i++)
		{
			if (!isntprime[i])
			{
				prime[++prime[0]] = i;
			}
			for (int j = 1, p = prime[j], s = i * p; j <= prime[0] && s <= maxn; j++, p = prime[j], s = i * p)
			{
				isntprime[s] = true;
				if (!(i % p))
					break;
			}
		}
	}
	void init()
	{
		inv[1] = 1;
		for (int i = 2; i <= maxn; i++)
			inv[i] = (LL)(mod - mod / i) * inv[mod % i] % mod;
	}

	int n;
	int sqrtN;
	int k;
	int N;
	int id[2][maxn];
	int appear[maxn * 2];
	void initBlocks()
	{
		N = 0;
		for (int i = 1, t; n / i > 1; i = t + 1)
		{
			int a = n / i;
			t = n / a;
			appear[++N] = a;
			if (a <= sqrtN) id[0][a] = N;
			else id[1][n / a] = N;
		}
	}
	int getId(int x)
	{
		if (x <= sqrtN) return id[0][x];
		else return id[1][n / x];
	}
	int g[maxn * 2];
	int s[maxn * 2];
	void solveG()
	{
		for (int i = 1; i <= N; i++)
			g[i] = appear[i] - 1;
		for (int j = 1, p = prime[j]; j <= k; j++, p = prime[j])
			for (int i = 1; i <= N && p * p <= appear[i]; i++)
				g[i] = ((LL)g[i] - (g[getId(appear[i] / p)] - (j - 1)) + mod) % mod;
	}
	void solveS()
	{
		for (int i = 1; i <= N; i++)
			s[i] = (LL)g[i] * inv[2] % mod;
		for (int j = k, p = prime[j]; j; j--, p = prime[j])
			for (int i = 1; i <= N && p * p <= appear[i]; i++)
			{
				int power = p;
				for (int e = 1; p <= appear[i] / power; e++, power *= p)
					s[i] = (s[i] + (LL)inv[e + 1] * (s[getId(appear[i] / power)] - ((LL)inv[2] * j % mod)) % mod + inv[e + 2] + mod) % mod;
			}
	}

	int operator()(int param)
	{
		n = param;
		sqrtN = std::sqrt(n);
		k = std::upper_bound(prime + 1, prime + 1 + prime[0], sqrtN) - prime - 1;
		init();
		initBlocks();
		solveG();
		solveS();
		return s[1] + (n >= 1);
	}
} min_25;

void run()
{
	int n = readIn();
	mod = readIn();
	printOut(min_25(n));
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