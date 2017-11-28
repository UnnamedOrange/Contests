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
		a = a * 10 + (ch - '0');
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}
inline void printOut(INT x)
{
	char buffer[15];
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

const INT maxn = 1005;
const INT maxm = 4005;
INT n, m;
struct Edge
{
	INT u;
	INT v;
	INT c;
	bool operator< (const Edge& b) const
	{
		return c < b.c;
	}
} edges[maxm];

struct DS
{
	INT parent[maxn];
	void clear(INT size)
	{
		for (int i = 1; i <= size; i++) parent[i] = i;
	}
	INT find(INT x)
	{
		if (x == parent[x]) return x;
		return parent[x] = find(parent[x]);
	}
	bool unite(INT x, INT y)
	{
		INT px = find(x);
		INT py = find(y);
		if (px == py) return false;
		parent[py] = find(px);
		return true;
	}
	bool judge(INT x, INT y)
	{
		return find(x) == find(y);
	}
} ds;

#define RunInstance(x) delete new x
struct brute
{
	INT ans;

	brute() : ans(-1)
	{
		std::sort(edges + 1, edges + 1 + m);
		for (int i = 1; i <= m; i++)
		{
			ds.clear(n);
			INT count_ = 0;
			for (int j = i; j <= m; j++)
			{
				Edge& e = edges[j];
				INT u = e.u;
				INT v = e.v;
				INT c = e.c;
				count_ += ds.unite(u, v);
				if (count_ == n - 1)
				{
					INT val = c - edges[i].c;
					if (ans == -1 || val < ans)
						ans = val;
					break;
				}
			}
			if (count_ != n - 1) break;
		}
		printOut(ans);
	}
};
struct cheat
{
	cheat()
	{
		ds.clear(n);
		INT count_ = 0;
		for (int i = 1; i <= m; i++)
		{
			Edge& e = edges[i];
			INT u = e.u;
			INT v = e.v;
			count_ += ds.unite(u, v);
		}
		printOut(count_ == n - 1 ? 0 : -1);
	}
};
struct work : brute
{
};

void run()
{
	INT T = readIn();
	while (T--)
	{
		n = readIn();
		m = readIn();

		bool bSame = true;
		INT val = -1;
		for (int i = 1; i <= m; i++)
		{
			edges[i].u = readIn();
			edges[i].v = readIn();
			edges[i].c = readIn();
			if (!~val) val = edges[i].c;
			else if (val != edges[i].c) bSame = false;
		}

		if (bSame)
			RunInstance(cheat);
		else if (n <= 10)
			RunInstance(brute);
		else
			RunInstance(work);
	}
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
