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
const INT maxn = 100005;
INT n, m;
INT a[maxn];

#define RunInstance(x) delete new x
struct cheat1
{
	INT ans;

	void search(INT x, INT start, INT sum)
	{
		if (x == m)
		{
			ans = (ans + sum) % mod;
			return;
		}
		for (int i = start; i <= n; i++)
		{
			search(x + 1, i + 1, sum ^ a[i]);
		}
	}

	cheat1() : ans()
	{
		search(0, 1, 0);
		cout << ans << endl;
	}
};
struct work
{
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

#define C(a, b) ((b > a) ? 0 : (fac[a] * invFac[b] % mod * invFac[(a) - (b)] % mod))

	work() : fac(), inv(), invFac()
	{
		init();

		INT ans = 0;
		for (int i = 0; i < 31; i++)
		{
			INT mask = 1 << i;
			INT appear = 0;
			for (int j = 1; j <= n; j++)
			{
				appear += bool(a[j] & mask);
			}

			INT contribution = 0;
			for (int j = 1; j <= appear; j += 2)
			{
				contribution = (contribution + C(appear, j) * C(n - appear, m - j) % mod) % mod;
			}
			ans = (ans + (1 << i) * contribution % mod) % mod;
		}
		cout << ans << endl;
	}
};

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= n; i++) a[i] = readIn();

	if (n <= 20)
		RunInstance(cheat1);
	else
		RunInstance(work);
}

int main()
{
#ifndef JUDGE
	freopen("card.in", "r", stdin);
	freopen("card.out", "w", stdout);
#endif
	run();
	return 0;
}
