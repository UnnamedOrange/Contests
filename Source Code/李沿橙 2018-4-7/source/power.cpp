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

const int maxn = int(1e5) + 5;
int n, m;
int w[maxn];
int q;

int gcd(int a, int b)
{
	return b ? gcd(b, a % b) : a;
}
LL power(LL x, int y, int mod)
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
	static int Phi(int x)
	{
		int ret = x;
		int to = std::sqrt(x);
		for (int i = 2; i <= to; i++)
		{
			if (x % i) continue;
			while (!(x % i)) x /= i;
			(ret /= i) *= i - 1;
		}
		if (x != 1) (ret /= x) *= x - 1;
		return ret;
	}
	LL query(int l, int r, int mod)
	{
		if (l == r) return w[l] % mod;
		int phi = Phi(mod);
		return power(w[l], query(l + 1, r, phi), mod);
	}
	brute()
	{
		while (q--)
		{
			int l = readIn();
			int r = readIn();
			printOut(query(l, r, m));
		}
	}
};

void run()
{
	cout << brute::Phi(10) << endl;
	n = readIn();
	m = readIn();
	for (int i = 1; i <= n; i++)
		w[i] = readIn();
	q = readIn();
	if (n <= 10)
		RunInstance(brute);
}

int main()
{
#ifndef LOCAL
	freopen("power.in", "r", stdin);
	freopen("power.out", "w", stdout);
#endif
	run();
	return 0;
}