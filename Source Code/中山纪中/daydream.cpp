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
using std::cin;
using std::cout;
using std::endl;
typedef long long INT;
inline INT readIn()
{
	INT a = 0;
	bool minus = false;
	char ch = getchar();
	while (!(ch == '-' || ch >= '0' && ch <= '9')) ch = getchar();
	if (ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		a *= 10;
		a += ch;
		a -= '0';
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}

const INT mod = 998244353;

const INT maxn = 1000005;
INT n, m, p, p_, d, a, b, c, bc;
INT pA[maxn];

void input()
{
	n = readIn();
	m = readIn();
	p = readIn();
	d = readIn();
	a = readIn();
	b = readIn();
	c = readIn();

	p_ = 1 + mod - p;
	bc = ((b * (1 + mod - d)) % mod + (c * d) % mod) % mod;
}

void run()
{
	input();

	INT ans = 0;
	pA[0] = 1;
	for (int i = 1; i <= n; i++)
	{
		pA[i] = pA[i - 1] * p_ % mod;
		if (i >= m + 1)
		{
			pA[i] += pA[i - (m + 1)] * p;
			pA[i] %= mod;
		}

		ans += pA[i] * a;
		ans %= mod;
		ans += (1 + mod - pA[i]) * bc;
		ans %= mod;
	}
	cout << ans << endl;
}

int main()
{
#ifndef JUDGE
	freopen("daydream.in", "r", stdin);
	freopen("daydream.out", "w", stdout);
#endif
	run();
	return 0;
}
