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
#define AWin() puts("madoka")
#define ALose() puts("Baozika")

const INT maxn = 5005;
const INT maxm = 100005;
INT n, m;
struct E
{
	INT u;
	INT v;
	INT c;
	void read()
	{
		u = readIn();
		v = readIn();
		c = readIn();
	}
	bool operator< (const E& b) const
	{
		return c < b.c;
	}
} es[maxm];
struct DS
{
	INT parent[maxn];
	void resize(INT size)
	{
		for (int i = 1; i <= size; i++)
			parent[i] = i;
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
		parent[py] = px;
		return true;
	}
} ds;

struct Edge
{
	INT to;
	INT cost;
	bool del;
	INT next;
} edges[maxn * 6];
INT head[maxn];
void addEdge(INT from, INT to, INT cost)
{
	static INT i;
	edges[i].to = to;
	edges[i].cost = cost;
	edges[i].next = head[from];
	head[from] = i;
	i++;
}

INT size;
INT depth[maxn];
INT next[14][maxn];
INT maxVal[14][maxn];
void goDouble(INT node)
{
	for (int i = 1; i <= size; i++)
	{
		next[i][node] = next[i - 1][next[i - 1][node]];
		maxVal[i][node] = std::max(maxVal[i - 1][node], maxVal[i - 1][next[i - 1][node]]);
	}
}

INT delu, delv, delc;
void dfs(INT node)
{
	depth[node] = depth[next[0][node]] + 1;
	goDouble(node);
	for (int i = head[node]; ~i; i = edges[i].next)
	{
		Edge& e = edges[i];
		if (e.del) continue;
		INT to = e.to;
		if (e.cost == delc && (node == delu && to == delv || node == delv && to == delu))
		{
			e.del = true;
			edges[i ^ 1].del = true;
			delu = delv = 0;
			continue;
		}

		INT c = e.cost;
		if (to == next[0][node]) continue;
		next[0][to] = node;
		maxVal[0][to] = c;
		dfs(to);
	}
}

INT LCAmax(INT u, INT v, INT* lca = NULL)
{
	if (depth[u] < depth[v]) std::swap(u, v);
	INT ret = 0;
	for (int i = size; ~i; i--)
	{
		if (depth[next[i][u]] < depth[v]) continue;
		ret = std::max(ret, maxVal[i][u]);
		u = next[i][u];
	}
	if (u != v)
	{
		for (int i = size; ~i; i--)
		{
			if (next[i][u] == next[i][v]) continue;
			ret = std::max(ret, maxVal[i][u]);
			ret = std::max(ret, maxVal[i][v]);
			u = next[i][u];
			v = next[i][v];
		}
		ret = std::max(ret, maxVal[0][u]);
		ret = std::max(ret, maxVal[0][v]);
		u = next[0][u];
	}
	if (lca) *lca = u;
	return ret;
}

bool Nim(INT a, INT b) //imitate
{
	if (a == b) return false;
	else return true;
}

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= m; i++)
		es[i].read();
	std::sort(es + 1, es + 1 + m);

	memset(head, -1, sizeof(head));

	INT nEdge = 1;
	ds.resize(n);
	for (int i = 1; i <= m; i++)
	{
		E& e = es[i];
		if (ds.unite(e.u, e.v))
		{
			addEdge(e.u, e.v, e.c);
			addEdge(e.v, e.u, e.c);
			nEdge++;
			if (nEdge == n) break;
		}
	}
	while (1 << size < n) size++;

	dfs(1);

	INT q = readIn();
	while (q--)
	{
		char buffer[8];
		scanf("%s", buffer);
		if (buffer[0] == 'g') //game
		{
			INT m1 = readIn();
			INT m2 = readIn();
			INT b1 = readIn();
			INT b2 = readIn();
			if (Nim(LCAmax(m1, m2), LCAmax(b1, b2))) //O(log * 1)
				AWin();
			else
				ALose();
		}
		else if (buffer[0] == 'a') //add
		{
			E add;
			add.read();

			INT lca;
			INT val = LCAmax(add.u, add.v, &lca); //O(log n)
			if (add.c >= val) continue;
			addEdge(add.u, add.v, add.c);
			addEdge(add.v, add.u, add.c);

			delc = val;
			INT pos = add.u;
			while (pos != lca) //O(n)
			{
				if (maxVal[0][pos] == val)
				{
					delu = pos;
					delv = next[0][pos];
					break;
				}
				pos = next[0][pos];
			}
			if (!delu || !delv) //O(n)
			{
				pos = add.v;
				while (pos != lca)
				{
					if (maxVal[0][pos] == val)
					{
						delu = pos;
						delv = next[0][pos];
						break;
					}
					pos = next[0][pos];
				}
			}
			dfs(lca); //O(n * log n)
		}
	}
}

int main()
{
#ifndef LOCAL
	freopen("game.in", "r", stdin);
	freopen("game.out", "w", stdout);
#endif
	run();
	return 0;
}
