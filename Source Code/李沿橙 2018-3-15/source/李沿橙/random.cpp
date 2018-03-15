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
	do buffer[length++] = -(x % 10) + '0';
	while (x /= 10);
	do putchar(buffer[--length]);
	while (length);
}

const int mod = 998244353;
const int maxn = 15;
int n, m;
int l[maxn], r[maxn];

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

#define RunInstance(x) delete new x
struct cheat
{
	cheat()
	{
		if (l[1] == r[1])
		{
			printOut(std::max(power(l[1], m), 0ll));
			return;
		}

		LL invt = power(m + 1, mod - 2);
		LL right = power(r[1], m + 1);
		LL left = power(l[1], m + 1);
		LL val = invt * (right - left + mod) % mod * power(r[1] - l[1], mod - 2) % mod;
		if (m & 1)
		{
			if (l[1] <= 0)
			{
				LL ans = val * r[1] % mod * power(r[1] - l[1], mod - 2) % mod;
				printOut(ans);
			}
			else
				printOut(val);
		}
		else
		{
			printOut(val);
		}
	}
};
struct work
{
	work()
	{

	}
};

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= n; i++)
	{
		l[i] = readIn();
		r[i] = readIn();
	}

	if (n == 1)
		RunInstance(cheat);
	else
		RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("random.in", "r", stdin);
	freopen("random.out", "w", stdout);
#endif
	run();
	return 0;
}