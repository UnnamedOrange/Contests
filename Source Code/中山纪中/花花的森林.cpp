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
typedef long long INT;
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
	char buffer[10];
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

const INT mod = 1e9 + 7;
const INT maxn = 1e5 + 5;
const INT maxm = 2 * maxn;
INT n, m, q;
INT weight[maxn];
struct ESTORAGE
{
	INT from;
	INT to;
} eStorage[maxn];
INT count_;
struct EDGE
{
	INT to;
	INT next;
} edges[maxm];
INT head[maxn];

INT size;
INT depth[maxn];
INT next[18][maxn];
INT length[18][maxn];

INT querys[maxn];
INT ans[maxn];

INT Inv(INT x)
{
	INT ret = 1;
	INT y = mod - 2;
	while (y)
	{
		if (y & 1) ret = ret * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return ret;
}
INT getDis(INT x, INT y)
{
	INT ret = 0;
	if (depth[x] < depth[y]) std::swap(x, y);
	INT originX = x, originY = y;
	for (int i = size; ~i; i--)
	{
		if (depth[next[i][x]] < depth[y]) continue;
		ret += length[i][x];
		x = next[i][x];
	}
	if (x != y)
	{
		for (int i = size; ~i; i--)
		{
			if (next[i][x] == next[i][y]) continue;
			ret += length[i][x] + length[i][y];
			x = next[i][x];
			y = next[i][y];
		}
		ret += length[0][x] + length[0][y];
		x = next[0][x];
		y = next[0][y];
	}
	ret += weight[originX] + weight[originY] - weight[x];
	return ret;
}
struct DS
{
	std::vector<INT> parent;

	DS(INT size) : parent(size + 1)
	{
		for (int i = 1; i <= size; i++)
		{
			parent[i] = i;
		}
	}

	INT find(INT x)
	{
		if (x == parent[x]) return x;
		return parent[x] = find(parent[x]);
	}
	void unite(INT x, INT y)
	{
		INT px = find(x);
		INT py = find(y);
		parent[py] = px;
	}
};

struct NODE
{
	INT d1;
	INT d2;
	INT val;
} nodes[maxn];

void work()
{
	ans[n] = 1;
	for (int i = 1; i <= n; i++)
	{
		ans[n] = ans[n] * weight[i] % mod;
	}
	for (int i = 1; i <= n; i++)
	{
		nodes[i].d1 = i;
		nodes[i].val = weight[i];
	}

	q = n - 1;
	for (int i = 1; i <= q; i++)
	{
		querys[i] = readIn();
	}

	DS ds(n);
	for (int i = q; i >= 1; i--)
	{
		INT from = ds.find(eStorage[querys[i]].from);
		INT to = ds.find(eStorage[querys[i]].to);
		INT d1 = nodes[from].d1, d2 = nodes[to].d1;
		INT dis = getDis(nodes[from].d1, nodes[to].d1);
		INT temp;
		if (nodes[from].d2)
		{
			temp = getDis(nodes[from].d1, nodes[from].d2);
			if (temp > dis)
			{
				dis = temp;
				d1 = nodes[from].d1;
				d2 = nodes[from].d2;
			}

			temp = getDis(nodes[to].d1, nodes[from].d2);
			if (temp > dis)
			{
				dis = temp;
				d1 = nodes[to].d1;
				d2 = nodes[from].d2;
			}
		}
		if (nodes[to].d2)
		{
			temp = getDis(nodes[to].d1, nodes[to].d2);
			if (temp > dis)
			{
				dis = temp;
				d1 = nodes[to].d1;
				d2 = nodes[to].d2;
			}

			temp = getDis(nodes[from].d1, nodes[to].d2);
			if (temp > dis)
			{
				dis = temp;
				d1 = nodes[from].d1;
				d2 = nodes[to].d2;
			}
		}
		if (nodes[from].d2 && nodes[to].d2)
		{
			temp = getDis(nodes[from].d2, nodes[to].d2);
			if (temp > dis)
			{
				dis = temp;
				d1 = nodes[from].d2;
				d2 = nodes[to].d2;
			}
		}

		ans[i] = ans[i + 1] * Inv(nodes[from].val) % mod * Inv(nodes[to].val) % mod * dis % mod;
		ds.unite(from, to);
		nodes[from].d1 = d1;
		nodes[from].d2 = d2;
		nodes[from].val = dis;
	}

	for (int i = 1; i <= n; i++)
	{
		printOut(ans[i]);
	}
}

void mul()
{
	while (1 << size < n) size++;
	for (int i = 1; i <= size; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			next[i][j] = next[i - 1][next[i - 1][j]];
			length[i][j] = length[i - 1][j] + length[i - 1][next[i - 1][j]];
		}
	}
}
void dfs(INT node = 1)
{
	for (int i = head[node]; i; i = edges[i].next)
	{
		INT to = edges[i].to;
		if (to == next[0][node]) continue;
		depth[to] = depth[node] + 1;
		next[0][to] = node;
		length[0][to] = weight[node];
		dfs(to);
	}
}
void init()
{
	for (int i = 1; i <= n; i++)
	{
		weight[i] = readIn();
	}
	for (int i = 1; i <= m; i++)
	{
		INT from = readIn();
		INT to = readIn();
		eStorage[i].from = from;
		eStorage[i].to = to;

		count_++;
		edges[count_].to = to;
		edges[count_].next = head[from];
		head[from] = count_;

		count_++;
		edges[count_].to = from;
		edges[count_].next = head[to];
		head[to] = count_;
	}
}
void run()
{
	n = readIn();
	m = n - 1;
	init();
	depth[1] = 1;
	dfs();
	mul();

	work();
}

int main()
{
	run();
	return 0;
}