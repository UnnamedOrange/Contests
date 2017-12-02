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
using std::cin;
using std::cout;
using std::endl;
typedef int INT;
inline INT readIn()
{
	INT a = 0;
	bool minus = false;
	char ch = getchar();
	while (!(ch == '-' || ch >= '0' && ch <= '9')) ch = getchar();
	if (ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		a *= 10;
		a += ch;
		a -= '0';
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}
inline void printOut(INT a)
{
	if (!a)
	{
		putchar('0');
		putchar('\n');
		return;
	}
	INT length = 0;
	char buffer[10];
	while (a)
	{
		buffer[length++] = a % 10 + '0';
		a /= 10;
	}
	do
	{
		putchar(buffer[--length]);
	} while (length);
	putchar('\n');
}

const INT maxn = 1000005;
INT n, m;
INT origin[maxn];
struct NODE
{
	INT lc;
	INT rc;
	INT parent;
} nodes[maxn];
INT root;

struct QUERY
{
	INT l;
	INT r;
	INT lca;
} querys[maxn];
INT headLCA[maxn];
INT LCA[maxn * 2];
INT nextLCA[maxn * 2];
inline void addLCA(INT index);
{
	LCA[0]++;
	LCA[LCA[0]] = index;
	nextLCA[LCA[0]] = headLCA[querys[index].l];
	headLCA[querys[index].l] = LCA[0];
	
	LCA[0]++;
	LCA[LCA[0]] = index;
	nextLCA[LCA[0]] = headLCA[querys[index].r];
	headLCA[querys[index].r] = LCA[0];
}

struct DS
{
	std::vector<INT> parent;
	
	DS(INT size) : parent(size + 1)
	{
		for(int i = 1; i <= size; i++)
		{
			ds[i] = i;
		}
	}
	
	INT find(INT x)
	{
		if(x == parent[x]) return x;
		return parent[x] = find(parent[x]);
	}
	
	void unite(INT x, INT y)
	{
		INT px = find(x);
		INT py = find(y);
		parent[py] = px;
	}
	
	bool judge(INT x, INT y)
	{
		return find(x) == find(y);
	}
};

void Tarjan(DS& ds)
{
	ds.
	for(int i = 0; i < )
}

void build()
{
	std::vector<INT> mono;
	for (int i = 1; i <= n; i++)
	{
		INT abandoned = 0;
		while (!mono.empty() && origin[mono.back()] < origin[i])
		{
			abandoned = mono.back();
			mono.pop_back();
		}
		nodes[i].lc = abandoned;
		if (abandoned)
		{
			nodes[abandoned].parent = i;
		}
		if (!mono.empty())
		{
			nodes[i].parent = mono.back();
			nodes[mono.back()].rc = i;
		}
		mono.push_back(i);
	}
	root = mono[0];
}

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= n; i++)
	{
		origin[i] = readIn();
	}

	build();
	for(int i = 1; i <= m; i++)
	{
		querys[i].l = readIn();
		querys[i].r = readIn();
		addQuery(i);
	}
	
	DS ds(n);
	Tarjan(ds);
}

int main()
{
#ifndef JUDGE
	freopen("trip.in", "r", stdin);
	freopen("trip.out", "w", stdout);
#endif
	run();
	return 0;
}
