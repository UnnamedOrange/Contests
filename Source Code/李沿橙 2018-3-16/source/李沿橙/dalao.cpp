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
}

const int mod = int(1e9) + 7;
const int maxn = 205;
int atX, atY, t, n, m;

LL power(LL x, int y = mod - 2)
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
	static const int offset = 302;
	static inline int code(int x)
	{
		return x + offset;
	}
	static inline int decode(int x)
	{
		return x - offset;
	}
	int rect[605][605];

	int C[305];

	cheat() : rect()
	{
		C[0] = 1;
		for (int i = 1; i <= t; i++)
			C[i] = (LL)C[i - 1] * (t - i + 1) % mod * power(i) % mod;

		for (int cntx = 0, cnty = t; ~cnty; cntx--, cnty--)
			for (int x = code(cntx), y = code(cnty), i = 0; i <= t; x++, y--, i++)
				rect[x][y] = C[i];

		for (int cntx = 0, cnty = t; ~cnty; cntx++, cnty--)
			for (int x = code(cntx), y = code(cnty), i = 0; i <= t; x--, y--, i++)
				rect[x][y] = (LL)rect[x][y] * C[i] % mod;

		int ans = 0;
		for (int x = -t, tx = code(x); x <= t; x++, tx++)
			for (int y = -t, ty = code(y); y <= t; y++, ty++)
				if (rect[tx][ty])
					ans = (ans + (LL)rect[tx][ty] * power(x + atX, n) % mod * power(y + atY, m) % mod) % mod;
		printOut(ans);
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
	atX = readIn();
	atY = readIn();
	t = readIn();
	n = readIn();
	m = readIn();

	if (!n && !m)
	{
		printOut(0);
		return;
	}

	if (t <= 300)
		RunInstance(cheat);
	else
		RunInstance(work);

}

int main()
{
#ifndef LOCAL
	freopen("dalao.in", "r", stdin);
	freopen("dalao.out", "w", stdout);
#endif
	run();
	return 0;
}