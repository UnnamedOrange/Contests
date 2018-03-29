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

const LL mod = 100003;
const LL maxn = mod + 5;
LL n, m;

LL fac[maxn];
LL inv[maxn];
LL invFac[maxn];
void init()
{
	fac[0] = 1;
	for (int i = 1; i < mod; i++)
		fac[i] = fac[i - 1] * i % mod;
	inv[1] = 1;
	for (int i = 2; i < mod; i++)
		inv[i] = (mod - mod / i) * inv[mod % i] % mod;
	invFac[0] = 1;
	for (int i = 1; i < mod; i++)
		invFac[i] = invFac[i - 1] * inv[i] % mod;
}
LL C(LL down, LL up)
{
	if (up > down) return 0;
	return fac[down] * invFac[up] % mod * invFac[down - up] % mod;
}
LL calc(LL a, LL b)
{
	if (a > b) std::swap(a, b);
	LL ret = 0, power = 1;
	for (int i = 0; i <= a; i++)
	{
		ret = (ret + C(a, i) * C(b, i) % mod * power) % mod;
		power = (power << 1) % mod;
	}
	return ret;
}

void solve()
{
	LL ans = 1;
	while (n || m)
	{
		ans = ans * calc(n % mod, m % mod) % mod;
		n /= mod;
		m /= mod;
	}
	printOut(ans);
}

void run()
{
	init();
	n = readIn();
	m = readIn();
	if (n < m)
	{
		printOut(0);
		return;
	}
	else if (n == m)
	{
		printOut(1);
		return;
	}
	else if ((n - m) & 1)
	{
		printOut(0);
		return;
	}
	LL x = n;
	LL y = m;
	n = (x - y) >> 1;
	m = (x + y) >> 1;
	solve();
}

int main()
{
#ifndef LOCAL
	freopen("move.in", "r", stdin);
	freopen("move.out", "w", stdout);
#endif
	run();
	return 0;
}