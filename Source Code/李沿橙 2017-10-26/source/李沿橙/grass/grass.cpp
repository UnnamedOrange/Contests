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

const INT INF = (~(INT(1) << (sizeof(INT) * 8 - 1)));
const INT maxn = 300005;
INT n, t;
struct Area
{
	INT l, r;
	INT mid;
	Area() {}
	Area(INT l, INT r) : l(l), r(r), mid((l + r) >> 1) {}
	void read()
	{
		l = readIn();
		r = readIn();
		mid = (l + r) >> 1;
	}
	static bool compR(const Area& a, const Area& b)
	{
		return a.r < b.r;
	}
} areas[maxn];
INT ans1;

#define RunInstance(x) delete new x

INT sum[maxn];
INT mulSum[maxn];
INT f[maxn];
INT g[maxn];
#define calc(i, j, mid) (f[j] + (mulSum[mid] - mulSum[j] - (sum[mid] - sum[j]) * j) + (-mulSum[i] + mulSum[mid] + (sum[i] - sum[mid]) * i))

void run()
{
	n = readIn();
	t = readIn();
	for (int i = 1; i <= n; i++)
		areas[i].read();
	std::sort(areas + 1, areas + 1 + n, Area::compR);

	for (int i = 1; i <= n; i++)
		sum[areas[i].mid]++;
	for (int i = 1; i <= areas[n].r; i++)
	{
		mulSum[i] = mulSum[i - 1] + sum[i] * i;
		sum[i] += sum[i - 1];
	}

	INT maxL = 0;
	INT w = 1;
	for (int i = 1; i <= areas[n].r; i++)
	{
		f[i] = g[i] = INF;
		for (; w <= n && areas[w].r < i; w++)
			maxL = std::max(maxL, areas[w].l);
		for (int j = maxL; j <= i - 1; j++)
		{
			if (g[i] >= g[j] + 1)
			{
				INT mid = (i + j) >> 1;
				if (g[i] > g[j] + 1)
				{
					g[i] = g[j] + 1;
					f[i] = INF;
				}
				f[i] = std::min(f[i], calc(i, j, mid));
			}
			else break;
		}
	}
	for (; w <= n; w++) maxL = std::max(maxL, areas[w].l);
	INT ans = INF;
	for (int i = maxL; i <= areas[n].r; i++) ans = std::min(ans, g[i]);
	printOut(ans);
	if (t)
	{
		INT ans2 = INF;
		for (int i = maxL; i <= areas[n].r; i++)
		{
			if (g[i] == ans)
			{
				ans2 = std::min(ans2, f[i] + mulSum[areas[n].r] - mulSum[i] - (sum[areas[n].r] - sum[i]) * i);
			}
		}
		printOut(ans2 * 2);
	}
}

int main()
{
#ifndef JUDGE
	freopen("grass.in", "r", stdin);
	freopen("grass.out", "w", stdout);
#endif
	run();
	return 0;
}
