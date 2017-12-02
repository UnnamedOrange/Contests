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

const INT mod = INT(1e9) + 7;
const INT maxn = 2005;
const INT maxk = 1000005;
INT n, m, k;

INT fac[maxk];
INT inv[maxk];
INT invFac[maxk];
INT power(INT x, INT y)
{
	INT ret = 1;
	while(y)
	{
		if(y & 1) ret = ret * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return ret;
}

void init()
{
	inv[1] = 1;
	for(int i = 2; i <= k; i++)
		inv[i] = (mod - mod / i) * inv[mod % i] % mod;

	fac[0] = 1;
	invFac[0] = 1;
	for(int i = 1; i <= k; i++)
	{
		fac[i] = fac[i - 1] * i % mod;
		invFac[i] = invFac[i - 1] * inv[i] % mod;
	}
}
INT A(INT x, INT y)
{
	return fac[x] * invFac[x - y] % mod;
}
INT C(INT x, INT y)
{
	return fac[x] * invFac[y] % mod * invFac[x - y] % mod;
}

INT f[maxn][maxn];
void dp()
{
	f[0][0] = 1;
	f[1][1] = 1;
	for(int i = 2; i <= n; i++)
	{
		f[i][1] = 1;
		for(int j = 2; j <= std::min(INT(i), k); j++)
		{
			f[i][j] = f[i - 1][j - 1] * i % mod;
			if(j <= i - 1) f[i][j] = (f[i][j] + f[i - 1][j] * j % mod) % mod;
		}
	}
}

void run()
{
	n = readIn();
	m = readIn();
	k = readIn();
	init();
	dp();

	INT ans = 0;
	for(int i = 1; i <= std::min(n, k); i++)
	{
		INT left = f[n][i];
		INT right = left;
		INT lr = left * right % mod;
		for(int j = i; j <= std::min(2ll * i, k); j++)
		{
			INT intersection = 2 * i - j;
			ans = (ans + C(k, i) * left % mod * C(k - i, i - intersection) % mod * right % mod * power(intersection, n * (m - 2)) % mod) % mod;
		}
	}
	cout << ans << endl;
}

int main()
{
#ifndef JUDGE
	freopen("photo.in", "r", stdin);
	freopen("photo.out", "w", stdout);
#endif
	run();
	return 0;
}
