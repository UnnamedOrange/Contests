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
	putchar('\n');
}

const int mod = int(1e9) + 7;
const int maxn = 505;
const int maxto = 500;
const int maxe = maxto * (maxto - 1) / 2;

int f[maxn][maxn * maxn / 2];
int C[maxn][maxn];
int fac[maxn];
void init()
{
	C[0][0] = 1;
	for (register int i = 1; i <= maxto; i++)
	{
		C[i][0] = 1;
		for (register int j = 1; j <= i; j++)
		{
			int temp;
			C[i][j] = (temp = C[i - 1][j - 1] + C[i - 1][j]) >= mod ? temp - mod : temp;
		}
	}

	for (register int i = 0; i <= maxe; i++)
		f[1][i] = 1;
	for (register int i = 2; i <= maxto; i++)
	{
		for (register int j = 0, to = i * (i - 1) / 2; j <= to; j++)
		{
			f[i][j] = ((LL)f[i][j] + f[i - 1][j] - (j - i >= 0 ? f[i - 1][j - i] : 0) + mod) % mod;
		}
		for (register int j = 1; j <= maxe; j++)
		{
			register int temp;
			f[i][j] = (temp = f[i][j] + f[i][j - 1]) >= mod ? temp - mod : temp;
		}
	}
	fac[0] = 1;
	for (int i = 1; i <= maxto; i++)
		fac[i] = (LL)fac[i - 1] * i % mod;
}

int n, E;

void run()
{
	init();

	int T = readIn();
	while (T--)
	{
		n = readIn();
		E = std::min(readIn(), n * (n - 1) / 2);
		LL ans = 0;
		for (register int i = 1; i <= n; i++)
			ans = (ans + (LL)fac[n - i] * fac[n - i] % mod * (n - i + 1) % mod * f[i][E] % mod * C[n][i] % mod * C[n][i] % mod) % mod;
		printOut(ans);
	}
}

int main()
{
#ifndef LOCAL
	freopen("perm.in", "r", stdin);
	freopen("perm.out", "w", stdout);
#endif
	run();
	return 0;
}