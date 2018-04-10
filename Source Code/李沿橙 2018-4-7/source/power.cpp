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
	putchar('\n');
}

const int maxn = int(1e5) + 5;
int n;
int m;
int a[maxn];

const int threshold = int(1e6) + 5;
int phi[threshold];
bool isntPrime[threshold];
int prime[78500];
void init()
{
	phi[1] = 1;
	isntPrime[1] = true;
	for (int i = 2; i < threshold; i++)
	{
		if (!isntPrime[i])
		{
			prime[++prime[0]] = i;
			phi[i] = i - 1;
		}
		for (int j = 1, p = prime[j], s = i * p; j <= prime[0] && s < threshold; j++, p = prime[j], s = i * p)
		{
			isntPrime[s] = true;
			if (i % p)
				phi[s] = phi[i] * (p - 1);
			else
			{
				phi[s] = phi[i] * p;
				break;
			}
		}
	}
}
std::map<int, int> map;
int Phi(int x)
{
	if (x < threshold) return phi[x];
	if (map.count(x)) return map[x];
	int origin = x;
	int ret = x;
	int to = std::sqrt(x);
	for (int i = 2; i <= to; i++)
	{
		if (x % i) continue;
		while (!(x % i)) x /= i;
		(ret /= i) *= i - 1;
	}
	if (x != 1) (ret /= x) *= x - 1;
	return map[origin] = ret;
}

LL powerWithRulerEx(LL x, int y, int mod)
{
	bool xGreaterThanMod = false;
	bool retGreaterThanMod = false;
	LL ret = 1;
	while (y)
	{
		if (y & 1)
		{
			ret = ret * x;
			if (xGreaterThanMod || ret >= mod) retGreaterThanMod = true;
			ret %= mod;
		}
		x = x * x;
		if (x >= mod) xGreaterThanMod = true;
		x %= mod;
		y >>= 1;
	}
	return ret + (retGreaterThanMod ? mod : 0);
}

int solve(int l, int r, int mod) // 返回值可能加上了一个 mod
{
	if (l == r || mod == 1) return powerWithRulerEx(a[l], 1, mod);
	return powerWithRulerEx(a[l], solve(l + 1, r, Phi(mod)), mod);
}

void run()
{
	init();
	n = readIn();
	m = readIn();
	for (int i = 1; i <= n; i++)
		a[i] = readIn();
	int q = readIn();
	while (q--)
	{
		int l = readIn();
		int r = readIn();
		printOut(solve(l, r, m) % m);
	}
}

int main()
{
#ifndef LOCAL
	freopen("power.in", "r", stdin);
	freopen("power.out", "w", stdout);
#endif
	run();
	return 0;
}