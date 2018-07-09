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
	while (!(std::isdigit(ch) || ch == '-')) ch = getchar();
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
	int f[maxm];

	work() : f()
	{
		int mul = 1;
		for (int i = 1; i <= n; i++)
			mul = mul * a[i];

		f[0] = 1;
		for (int i = 1; i <= n; i++)
			for (int j = a[i]; j <= maxm; j++)
				f[j] = (f[j] + f[j - a[i]]) % mod;

		for (int i = 0; i <= 100; i++)
		{
			LL sum = 0;
			for (int j = 1 + mul * i; j <= mul * (i + 1); j++)
				sum += f[j], printf("%d\t", f[j]);
			printf("sum = %lld\n", sum);
		}
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