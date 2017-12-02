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
INT C(INT x, INT y)
{
	return fac[x] * invFac[y] % mod * invFac[x - y] % mod;
}

INT f[maxn];
void dp()
{
	f[1] = 1;
	for(int i = 2; i <= n; i++)
	{
		f[i] = power(i, n);
		for(int j = 1; j < i; j++)
		{
			f[i] = (f[i] - f[j] * C(i, j) % mod + mod) % mod;
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
		INT p = power(i, n * (m - 2));
		for(int j = i; j <= std::min(n, k); j++)
		{
			if(!i && !j) continue;
			if(!i && m != 2) continue;
			ans = (ans + (f[j] * f[j] % mod * C(k, i) % mod * C(k - i, j - i) % mod * C(k - j, j - i) % mod * p % mod)) % mod;
		}
	}
	cout << ans % mod << endl;
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
