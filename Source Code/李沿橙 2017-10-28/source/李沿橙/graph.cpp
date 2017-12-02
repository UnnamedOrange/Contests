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
		char buffer[13];
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

const INT maxn = 100005;
INT n, A, B, q;
struct Edge
{
	INT u;
	INT v;
	INT k;
	void read()
	{
		u = readIn();
		v = readIn();
		k = readIn();
	}
	bool operator< (const Edge& b) const
	{
		return k < b.k;
	}
} kA[maxn], kB[maxn];
struct DS
{
	INT parent[maxn];
	DS() {}
	DS(INT size) { clear(size); }
	void clear(INT size) { for (int i = 1; i <= size; i++) parent[i] = i; }
	INT find(INT x)
	{
		if (x == parent[x]) return x;
		return parent[x] = find(parent[x]);
	}
	bool judge(INT x, INT y)
	{
		return find(x) == find(y);
	}
	void unite(INT x, INT y)
	{
		parent[find(y)] = find(x);
	}
};

#define RunInstance(x) delete new x
struct cheat
{
	DS ds;

	cheat()
	{
		while (q--)
		{
			INT x = readIn();
			ds.clear(n);
			INT a = 1, b = 1;
			INT l = 1;
			INT ans = 0;
			while (a <= A || b <= B)
			{
				if (l == n) break;
				if (b > B || a <= A && kA[a].k + x < kB[b].k - x)
				{
					if (!ds.judge(kA[a].u, kA[a].v))
					{
						ans += kA[a].k + x;
						ds.unite(kA[a].u, kA[a].v);
						l++;
					}
					a++;
				}
				else
				{
					if (!ds.judge(kB[b].u, kB[b].v))
					{
						ans += kB[b].k - x;
						ds.unite(kB[b].u, kB[b].v);
						l++;
					}
					b++;
				}
			}
			printOut(ans);
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
	A = readIn();
	B = readIn();
	q = readIn();
	for (int i = 1; i <= A; i++) kA[i].read();
	for (int i = 1; i <= B; i++) kB[i].read();
	std::sort(kA + 1, kA + 1 + A);
	std::sort(kB + 1, kB + 1 + B);

	if (n <= 1000 && q <= 1000)
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
