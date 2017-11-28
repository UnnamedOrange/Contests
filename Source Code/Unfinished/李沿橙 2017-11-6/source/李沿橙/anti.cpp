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
typedef long long INT;
using std::cin;
using std::cout;
using std::endl;
INT readIn()
{
	INT a = 0;
	bool minus = false;
	char ch = getchar();
	while (!(ch == '-' || (ch >= '0' && ch <= '9'))) ch = getchar();
	if (ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		a = a * 10 + (ch - '0');
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}
void printOut(INT x)
{
	char buffer[20];
	INT length = 0;
	bool minus = x < 0;
	if (minus) x = -x;
	do
	{
		buffer[length++] = x % 10 + '0';
		x /= 10;
	} while (x);
	if (minus) buffer[length++] = '-';
	do
	{
		putchar(buffer[--length]);
	} while (length);
	putchar('\n');
}

const INT mod = INT(1e9) + 7;
INT n, m;
#define RunInstance(x) delete new x
struct brute
{
	static const INT maxN = 505;
	INT f[2][maxN][maxN];

	brute() : f()
	{
		f[0][0][0] = 1;
		for (int i = 1; i <= n; i++)
		{
			INT cnt = i & 1;
			INT pre = !cnt;
			memset(f[cnt], 0, sizeof(f[cnt]));
			for (int j = 1; j <= m; j++)
				for (int k = 0; k <= m; k++)
					for (int l = 0; l <= m; l++)
					{
						if (j != k && j != l)
							f[cnt][j][k] = (f[cnt][j][k] + f[pre][k][l]) % mod;
					}
		}
		INT ans = 0;
		for (int i = 0; i <= m; i++)
			for (int j = 0; j <= m; j++)
				ans = (ans + f[n & 1][i][j]) % mod;
		printOut(ans);
	}
};
struct cheat
{
	INT power(INT x, INT y)
	{
		INT ret = 1;
		while (y)
		{
			if (y & 1) ret = ret * x % mod;
			x = x * x % mod;
			y >>= 1;
		}
		return ret;
	}

	cheat()
	{
		if (m == 1)
		{
			if (n == 1) printOut(1);
			else printOut(0);
		}
		else if (m == 2)
		{
			if (n <= 2) printOut(2);
			else printOut(0);
		}
		else if (m == 3)
		{
			if (n == 1) printOut(3);
			else printOut(6);
		}
		else
		{
			if (n == 1) printOut(m);
			else printOut(m * (m - 1) % mod * power(m - 2, n - 2) % mod);
		}
	}
};
struct work
{
	INT mul(unsigned long long x, unsigned long long y)
	{
		const INT part = INT(1e9);
		INT xh = x / part;
		INT xl = x % part;
		INT yh = y / part;
		INT yl = y % part;
		INT t = xh * yh % mod * part % mod * part % mod;
		t = (t + xh * yl % mod * part % mod) % mod;
		t = (t + xl * yh % mod * part % mod) % mod;
		t = (t + xl * yl % mod) % mod;
		return t;
	}
	INT power(INT x, INT y)
	{
		INT ret = 1;
		while (y)
		{
			if (y & 1) ret = mul(ret, x);
			x = mul(x, x);
			y >>= 1;
		}
		return ret;
	}
	work()
	{
		if (m == 1)
		{
			if (n == 1) printOut(1);
			else printOut(0);
		}
		else if (m == 2)
		{
			if (n <= 2) printOut(2);
			else printOut(0);
		}
		else if (m == 3)
		{
			if (n == 1) printOut(3);
			else printOut(6);
		}
		else
		{
			if (n == 1) printOut(m % mod);
			else printOut(mul(m, m - 1) % mod * power(m - 2, n - 2) % mod);
		}
	}
};

void run()
{
	INT T = readIn();
	while (T--)
	{
		n = readIn();
		m = readIn();
		if (n <= 20 && m <= 20)
			RunInstance(brute);
		else if (n <= INT(2e9) && m <= INT(2e9))
			RunInstance(cheat);
		else
			RunInstance(work);
	}
}

int main()
{
#ifndef LOCAL
	freopen("anti.in", "r", stdin);
	freopen("anti.out", "w", stdout);
#endif
	run();
	return 0;
}
