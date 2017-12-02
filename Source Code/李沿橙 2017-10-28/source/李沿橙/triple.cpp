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
#include <functional>
typedef long long INT;
using std::cin;
using std::cout;
using std::endl;
inline INT readIn()
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
		a = a * 10 + ch - '0';
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}
inline void printOut(INT x)
{
	if (!x)
	{
		putchar('0');
	}
	else
	{
		char buffer[12];
		INT length = 0;
		bool minus = x < 0;
		if (minus) x = -x;
		while (x)
		{
			buffer[length++] = x % 10 + '0';
			x /= 10;
		}
		if (minus) buffer[length++] = '-';
		do
		{
			putchar(buffer[--length]);
		}
		while (length);
	}
	putchar('\n');
}

const INT maxn = 500005;
INT n;
INT X, Y, Z;
INT x[maxn], y[maxn], z[maxn];

#define RunInstance(x) delete new x
struct cheat1
{
	static const INT maxN = 105;
	INT f[maxN][maxN][maxN];

	cheat1() : f()
	{
		f[1][1][0] = x[1];
		f[1][0][1] = y[1];
		f[1][0][0] = z[1];
		for (int i = 2; i <= n; i++)
		{
			for (int j = 0; j <= i; j++)
			{
				for (int k = 0; k + j <= i; k++)
				{
					if (j) f[i][j][k] = std::max(f[i][j][k], f[i - 1][j - 1][k] + x[i]);
					if (k) f[i][j][k] = std::max(f[i][j][k], f[i - 1][j][k - 1] + y[i]);
					if (i - j - k) f[i][j][k] = std::max(f[i][j][k], f[i - 1][j][k] + z[i]);
				}
			}
		}
		printOut(f[n][X][Y]);
	}
};
struct cheat2
{
	cheat2()
	{
		
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
	X = readIn();
	Y = readIn();
	Z = readIn();
	n = X + Y + Z;
	for (int i = 1; i <= n; i++)
	{
		x[i] = readIn();
		y[i] = readIn();
		z[i] = readIn();
	}

	if (n <= 100)
		RunInstance(cheat1);
	else if(!X)
		RunInstance(cheat2);
	else
		RunInstance(work);
}

int main()
{
#ifndef JUDGE
	freopen("triple.in", "r", stdin);
	freopen("triple.out", "w", stdout);
#endif
	run();
	return 0;
}
