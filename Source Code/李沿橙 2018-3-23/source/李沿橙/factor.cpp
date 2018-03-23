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
}

LL l, r;

#define RunInstance(x) delete new x
struct brute
{
	static const int maxN = int(1e7) + 5;
	bool isntPrime[maxN];
	int prime[664585];
	int val[maxN];

	brute() : isntPrime(), prime(), val()
	{
		isntPrime[1] = true;
		for (register int i = 2; i <= r; i++)
		{
			if (!isntPrime[i])
			{
				prime[++prime[0]] = i;
			}
			for (register LL j = 1, p = prime[j], s = i * p; j <= prime[0] && s <= r; j++, p = prime[j], s = i * p)
			{
				isntPrime[s] = true;
				val[s] = s / p;
				if (!(i % p)) break;
			}
		}

		LL ans = 0;
		for (int i = l; i <= r; i++)
			ans += val[i];
		printOut(ans);
	}
};
struct cheat
{
	static const int maxN = int(1e6) + 5;
	bool isntPrimeS[maxN];
	bool isntPrimeL[maxN];
	LL val[maxN];

	cheat() : isntPrimeS(), isntPrimeL(), val()
	{
		int to = std::sqrt(r);
		for (register LL i = 2; i <= to; i++)
		{
			if (!isntPrimeS[i])
			{
				for (register LL j = i * i; j <= to; j += i)
					isntPrimeS[j] = true;
				for (register LL j = std::max(i * i, (l - 1) / i * i); j <= r; j += i)
				{
					isntPrimeL[j - l] = true;
					if (!val[j - l]) val[j - l] = j / i;
				}
			}
		}
		LL ans = 0;
		for (int i = 0, to = r - l; i <= to; i++)
			ans += val[i];
		printOut(ans);
	}
};

void run()
{
	l = readIn();
	r = readIn();
	if (r <= LL(1e7))
		RunInstance(brute);
	else if (r - l <= LL(1e6))
		RunInstance(cheat);
}

int main()
{
#ifndef LOCAL
	freopen("factor.in", "r", stdin);
	freopen("factor.out", "w", stdout);
#endif
	run();
	return 0;
}