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
		} while (length);
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
struct work
{
	INT ans;

	INT bufY[maxn * 2];
	INT bufZ[maxn * 2];
	struct Node
	{
		INT x;
		INT y;
		INT z;
		bool operator< (const Node& b) const
		{
			return (y - z) > (b.y - b.z);
		}
	} nodes[maxn];

	work() : ans(), bufY(), bufZ()
	{
		for (int i = 1; i <= n; i++)
		{
			nodes[i].x = x[i];
			nodes[i].y = y[i];
			nodes[i].z = z[i];
		}
		std::sort(nodes + 1, nodes + 1 + n);

		for (int i = 1; i <= n; i++)
			ans += x[i];

		const INT delta = 500000;
		for (int i = 1; i <= Y; i++)
			bufY[nodes[i].y - nodes[i].x + delta]++;
		for (int i = Y + 1; i <= n; i++)
			bufZ[nodes[i].z - nodes[i].x + delta]++;

		INT posY = 0;
		INT posZ = 0;

		for (int i = delta * 2; i >= 0; i--)
		{
			if (bufY[i])
			{
				posY = i;
				ans += bufY[i] * (i - delta);
			}
		}
		INT cnt = 0;
		for (int i = delta * 2; i >= 0; i--)
		{
			if (bufZ[i])
			{
				INT nCalc = std::min(bufZ[i], Z - cnt);
				cnt += nCalc;
				ans += nCalc * (i - delta);
				bufZ[i] -= nCalc;
			}
			if (cnt == Z)
			{
				posZ = i;
				break;
			}
		}
		while (!bufZ[posZ]) posZ--;

		INT temp = ans;
		for (int i = Y + 1; i <= n - Z; i++)
		{
			INT py = nodes[i].y - nodes[i].x;
			INT pz = nodes[i].z - nodes[i].x;
			if (py + delta >= posY)
			{
				bufY[posY]--;
				temp -= posY - delta;
				bufY[py + delta]++;
				temp += py;
				while (!bufY[posY]) posY++;
			}
			if (pz + delta >= posZ)
			{
				temp += posZ - delta;
				bufZ[posZ]--;
				temp -= pz;
				while (!bufZ[posZ]) posZ--;
			}
			else
				bufZ[pz + delta]--;

			ans = std::max(ans, temp);
		}
		printOut(ans);
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
