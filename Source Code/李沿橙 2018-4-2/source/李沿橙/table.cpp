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
		(a *= 10) -= ch - '0';
		ch = getchar();
	}
	return positive ? -a : a;
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

const int mod = 998244353;
const int maxn = int(1e5) + 5;
int n, m;
int val[maxn];
int a, b, p, q;

int power(LL x, int y = mod - 2)
{
	LL ret = 1;
	while (y)
	{
		if (y & 1) ret = ret * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return ret;
}

#define RunInstance(x) delete new x
struct brute
{
	int f[int(1e5) + 5][105];
	int invA, invB;

	brute() : invA(power(a)), invB(power(b))
	{
		for (int i = 1; i <= n; i++) f[i][0] = 0;
		for (int i = 1; i <= m; i++) f[p][i] = val[i];

		for (int i = p - 1; i; i--)
		{
			int* cnt = f[i];
			int* pre = f[i + 1];
			for (int j = 1; j <= m; j++)
			{
				cnt[j] = ((LL)pre[j] - (LL)b * cnt[j - 1]) % mod * invA % mod;
				if (cnt[j] < 0) cnt[j] += mod;
			}
		}
		for (int i = p + 1; i <= n; i++)
		{
			int* cnt = f[i];
			int* pre = f[i - 1];
			for (int j = 1; j <= m; j++)
				cnt[j] = ((LL)a * pre[j] + (LL)b * pre[j - 1]) % mod;
		}

		while (q--)
		{
			int x = readIn();
			int y = readIn();
			printOut(f[x][y]);
		}
	}
};

const int maxm = int(1e7) + maxn + 5;
int fac[maxm];
int inv[maxm];
int invFac[maxm];
int powerA[maxm];
int powerB[maxm];
void init()
{
	int to = n + m;
	fac[0] = 1;
	for (int i = 1; i <= to; i++)
		fac[i] = (LL)fac[i - 1] * i % mod;
	inv[1] = 1;
	for (int i = 2; i <= to; i++)
		inv[i] = (LL)(mod - mod / i) * inv[mod % i] % mod;
	invFac[0] = 1;
	for (int i = 1; i <= to; i++)
		invFac[i] = (LL)invFac[i - 1] * inv[i] % mod;
	powerA[0] = 1;
	for (int i = 1; i <= to; i++)
		powerA[i] = (LL)powerA[i - 1] * a % mod;
	powerB[0] = 1;
	for (int i = 1; i <= to; i++)
		powerB[i] = (LL)powerB[i - 1] * b % mod;
}
inline LL C(int down, int up)
{
	return down < up ? 0 : (LL)fac[down] * invFac[up] % mod * invFac[down - up] % mod;
}

struct cheat
{
	cheat()
	{
		while (q--)
		{
			int x = readIn();
			int y = readIn();
			LL ans = 0;
			for (int idx = y, num = x; idx && ~num; idx--, num--)
				ans = (ans + (LL)C(x, num) * powerA[num] % mod * powerB[x - num] % mod * val[idx] % mod) % mod;
			printOut(ans);
		}
	}
};
struct work
{
	int invA, invB;

	work() : invA(power(a)), invB(power(b))
	{
		while (q--)
		{
			int x = readIn();
			int y = readIn();
			LL ans = 0;
			if (x == p)
				ans = val[y];
			else if (x > p)
			{
				int delta = x - p;
				for (int i = y, idx = delta; i && ~idx; i--, idx--)
					ans = (ans + (LL)C(delta, idx) * powerA[idx] % mod * powerB[delta - idx] % mod * val[i] % mod) % mod;
			}
			else
			{
				int delta = p - x;
				LL pa = power(invA, delta);
				LL pb = 1;
				int down = delta - 1;
				int up = 0;
				int neg = 1;
				for (int i = y; i; i--, down++, up++, pa = pa * invA % mod, pb = pb * b % mod, neg = -neg)
					ans = (ans + neg * (LL)C(down, up) * pa % mod * pb % mod * val[i] % mod) % mod;
				if (ans < 0) ans += mod;
			}
			printOut(ans);
		}
	}
};

void run()
{
	n = readIn();
	m = readIn();
	a = readIn();
	b = readIn();
	p = readIn();
	q = readIn();
	for (int i = 1; i <= m; i++)
		val[i] = readIn();
	init();

	if (n <= int(1e5) && m <= 100)
		RunInstance(brute);
	else
		RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("table.in", "r", stdin);
	freopen("table.out", "w", stdout);
#endif
	run();
	return 0;
}