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
inline void printOut(INT x)
{
	if (!x)
	{
		putchar('0');
		putchar('\n');
		return;
	}
	char buffer[8];
	INT length = 0;
	while (x)
	{
		buffer[length++] = x % 10 + '0';
		x /= 10;
	}
	do
	{
		putchar(buffer[--length]);
	} while (length);
	putchar('\n');
}

const INT maxn = 200005;
const INT maxm = maxn * 2;
INT n, m, q;
INT head[maxn];
INT To[maxm];
INT next[maxm];
void addEdge(INT from, INT to)
{
	static INT count_ = 0;
	count_++;
	To[count_] = to;
	next[count_] = head[from];
	head[from] = count_;
}

class BIT
{
	INT bit[maxn];
	static INT lowbit(INT x)
	{
		return x & -x;
	}

public:
	void modify(INT x, INT val)
	{
		while (x <= n)
		{
			bit[x] += val;
			x += lowbit(x);
		}
	}
	INT query(INT pos)
	{
		INT ret = 0;
		while (pos)
		{
			ret += bit[pos];
			pos -= lowbit(pos);
		}
		return ret;
	}
	INT query(INT x, INT y)
	{
		return query(y) - query(x - 1);
	}
} bit1, bit2;

INT size;
INT parent[19][maxn];
INT depth[maxn];
INT dfn[maxn];
INT end[maxn];
void dfs(INT node = 1)
{
	static INT nDfs = 0;
	dfn[node] = ++nDfs;
	for (int i = head[node]; i; i = next[i])
	{
		INT to = To[i];
		if (to == parent[0][node]) continue;
		depth[to] = depth[node] + 1;
		parent[0][to] = node;
		dfs(to);
	}
	end[node] = nDfs;
}
void init()
{
	while (1 << size < n) size++;
	for (int i = 1; i <= size; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			parent[i][j] = parent[i - 1][parent[i - 1][j]];
		}
	}
}
INT LCA(INT x, INT y)
{
	if (depth[x] < depth[y]) std::swap(x, y);
	for (int i = size; ~i; i--)
	{
		if (depth[parent[i][x]] < depth[y]) continue;
		x = parent[i][x];
	}
	if (x != y)
	{
		for (int i = size; ~i; i--)
		{
			if (parent[i][x] == parent[i][y]) continue;
			x = parent[i][x];
			y = parent[i][y];
		}
		x = parent[0][x];
	}
	return x;
}

INT lca[maxn];
void work(INT from, INT to)
{
	INT ans = 0;
	INT l = LCA(from, to);

	ans += bit1.query(dfn[l], end[l]);
	ans += bit2.query(dfn[from]) + bit2.query(dfn[to]) - (bit2.query(dfn[l]) << 1);
	ans += lca[l];
	printOut(ans);

	bit1.modify(dfn[from], 1);
	bit1.modify(dfn[to], 1);
	bit1.modify(dfn[l], -2);
	bit2.modify(dfn[l], 1);
	bit2.modify(end[l] + 1, -1);
	lca[l]++;
}

void run()
{
	n = readIn();
	m = n - 1;
	for (int i = 1; i <= m; i++)
	{
		INT from = readIn();
		INT to = readIn();
		addEdge(from, to);
		addEdge(to, from);
	}
	depth[1] = 1;
	dfs();
	init();

	q = readIn();
	while (q--)
	{
		INT from = readIn();
		INT to = readIn();
		work(from, to);
	}
}

int main()
{
	run();
	return 0;
}