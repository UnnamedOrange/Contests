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
			putchar(buffer[--length]);
		while (length);
	}
	putchar('\n');
}

const INT mod = INT(1e9) + 7;
const INT maxn = INT(2e5) + 5;
INT n, m;

INT fac[maxn];
INT inv[maxn];
INT invFac[maxn];

void init()
{
	fac[0] = 1;
	for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % mod;
	inv[1] = 1;
	for (int i = 2; i <= n; i++) inv[i] = (mod - mod / i) * inv[mod % i] % mod;
	invFac[0] = 1;
	for (int i = 1; i <= n; i++) invFac[i] = invFac[i - 1] * inv[i] % mod;
}

void run()
{
	n = readIn();
	m = readIn();
	init();
	printOut(fac[n] * invFac[m] % mod * invFac[n - m] % mod);
}

int main()
{
#ifndef JUDGE
	freopen("video.in", "r", stdin);
	freopen("video.out", "w", stdout);
#endif
	run();
	return 0;
}
