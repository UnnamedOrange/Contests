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
typedef int INT;
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
			putchar(buffer[--length]);
		while (length);
	}
	putchar('\n');
}

const INT INF = (~(INT(1) << (sizeof(INT) * 8 - 1))) >> 1;
const INT maxn = 35;
const INT maxm = 20005;
INT n, m, q;
struct Edge
{
	INT x, y, c, r;
	void read()
	{
		x = readIn();
		y = readIn();
		c = readIn();
		r = readIn();
	}
} edges[maxm];

#define RunInstance(x) delete new x
struct cheat
{
	INT x[maxn], y[maxn];

	cheat()
	{
		while (q--)
		{
			INT u = readIn();
			INT v = readIn();
			INT l = readIn();
			INT r = readIn();
			INT* f = x;
			INT* g = y;
			std::fill(f + 1, f + 1 + n, INF);
			f[u] = 0;
			for (int i = l; i <= r; i++)
			{
				Edge& e = edges[i];
				std::swap(f, g);
				std::fill(f + 1, f + 1 + n, INF);
				for (int j = 1; j <= n; j++)
				{
					f[j] = g[j] + e.r;
					if (j == e.y)
						f[j] = std::min(f[j], g[e.x] + e.c);
					else if (j == e.x)
						f[j] = std::min(f[j], g[e.y] + e.c);
				}
			}
			if (f[v] >= INF) f[v] = -1;
			printOut(f[v]);
		}
	}
};
struct work
{
	struct Query
	{
		INT from;
		INT to;
		
		INT next;
	} 
	
	work()
	{
		
	}
};

void run()
{
	n = readIn();
	m = readIn();
	q = readIn();
	for (int i = 1; i <= m; i++)
	{
		edges[i].read();
	}

	if(n <= 10 && m <= 1000 && q <= 1000)
		RunInstance(cheat);
	else
		RunInstance(work);
}

int main()
{
#ifndef JUDGE
	freopen("graph.in", "r", stdin);
	freopen("graph.out", "w", stdout);
#endif
	run();
	return 0;
}
