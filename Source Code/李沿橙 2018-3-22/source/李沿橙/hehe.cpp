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

const LL mod = int(1e9) + 7;
const int maxn = 2005;
int n;
int w[maxn];
LL temp;
LL ans;
LL mul = 1;
LL sum;

LL inv[maxn];
LL invFac[maxn];
LL power[maxn];

LL f[maxn][maxn];

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
	{
		w[i] = readIn();
		mul = mul * w[i] % mod;
		sum = (temp = sum + w[i]) >= mod ? temp - mod : temp;
	}
	inv[1] = 1;
	for (int i = 2; i <= n; i++)
		inv[i] = (mod - mod / i) * inv[mod % i] % mod;
	invFac[0] = 1;
	for (int i = 1; i <= n; i++)
		invFac[i] = invFac[i - 1] * inv[i] % mod;
	power[0] = 1;
	for (int i = 1; i <= n; i++)
		power[i] = power[i - 1] * sum % mod;

	f[0][0] = 1;
	for (int i = 1; i <= n; i++)
	{
		f[i][0] = 1;
		for (int j = 1; j <= i; j++)
			f[i][j] = (f[i - 1][j] + f[i - 1][j - 1] * w[i]) % mod;
	}

	LL ans = 0;
	for (int k = 0; k <= n - 2; k++)
		ans = (ans + power[n - 2 - k] * invFac[n - 2 - k] % mod * f[n][k]) % mod;

	ans = ans * mul % mod;
	for (int i = 2; i <= n - 2; i++)
		ans = ans * i % mod;

	printOut(ans);
}

int main()
{
#ifndef LOCAL
	freopen("hehe.in", "r", stdin);
	freopen("hehe.out", "w", stdout);
#endif
	run();
	return 0;
}