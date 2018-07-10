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

const int mod = int(1e9) + 7;
const int maxn = 15;
int n;
int a[maxn];
LL L, R;
int gcd(int a, int b)
{
	return !b ? a : gcd(b, a % b);
}

LL power(LL x, int y)
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

void add(int& x, const int& y)
{
	register int t;
	x = (t = x + y) >= mod ? t - mod : t;
}
void sub(int& x, const int& y)
{
	register int t;
	x = (t = x - y) < 0 ? t + mod : t;
}

#define RunInstance(x) delete new x
struct brute
{
	static const int maxm = int(1e5) + 5;
	int f[maxm];

	brute() : f()
	{
		f[0] = 1;
		for (int i = 1; i <= n; i++)
			for (int j = a[i]; j <= R; j++)
				f[j] = (f[j] + f[j - a[i]]) % mod;

		int ans = 0;
		for (int i = L; i <= R; i++)
			ans = (ans + f[i]) % mod;
		printOut(ans);
	}
};
struct work
{
	static const int maxm = int(1e5) + 5;
	int f[maxn * maxm];
	int lcm;
	int size;

	int C(LL down, LL up)
	{
		if (down < up) return 0;
		up = std::min(up, down - up);
		LL mul = 1;
		for (int i = 0; i < up; i++)
			mul = mul * ((down - i) % mod) % mod;
		LL div = 1;
		for (LL i = 2; i <= up; i++)
			div = div * i % mod;
		return mul * power(div, mod - 2) % mod;
	}

	int solve(LL x)
	{
		LL ret = 0;
		LL div = (x - size) / lcm;
		if (x - size >= 0) // note
		{
			ret = (LL)C(n + div, n) * f[size] % mod;
			div++;
		}
		else
			div = 0;
		for (LL i = div; lcm * i <= x; i++)
			ret = (ret + (LL)C(n - 1 + i, n - 1) * f[x - i * lcm]) % mod;
		return ret;
	}
	int temp[maxn * maxm];
	int contri[maxn];

	work() : f()
	{
		lcm = 1;
		for (int i = 1; i <= n; i++)
			lcm = lcm / gcd(lcm, a[i]) * a[i];
		size = lcm * n;

		f[0] = 1;
		for (int i = 1; i <= n; i++)
		{
			std::memset(temp, 0, sizeof(temp));
			for (int j = 0; j < a[i]; j++)
			{
				int contri = 0;
				for (int k = a[i] + j; k <= size; k += a[i])
				{
					add(contri, f[k - a[i]]);
					if (k - lcm >= 0)
						sub(contri, f[k - lcm]);
					add(temp[k], contri);
				}
			}
			for (int i = 0; i <= size; i++)
				add(f[i], temp[i]);
		}
		for (int i = 1; i <= size; i++)
			add(f[i], f[i - 1]);

		printOut((solve(R) - solve(L - 1) + mod) % mod);
	}
};

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
		a[i] = readIn();
	L = readIn();
	R = readIn();

	if (R <= LL(1e5))
		RunInstance(brute);
	else
		RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("gugu.in", "r", stdin);
	freopen("gugu.out", "w", stdout);
#endif
	run();
	return 0;
}