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

const INT maxn = 100005;
struct EDGE
{
	INT from;
	INT to;
	INT cost;
	bool operator< (const EDGE& b) const
	{
		return cost < b.cost;
	}
} edges[maxn];
INT n, m;
INT chip;
std::map<std::string, INT> mapSI;
inline INT readStr()
{
	char buffer[10];
	scanf("%s", buffer);
	if (mapSI.count(buffer)) return mapSI[buffer];
	return mapSI[buffer] = ++chip;
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

	bool judge(INT x, INT y)
	{
		return find(x) == find(y);
	}
};

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= m; i++)
	{
		edges[i].cost = readIn();
		edges[i].from = readStr();
		edges[i].to = readStr();
	}
	std::sort(edges + 1, edges + 1 + m);

	DS ds(chip);
	INT countEdge = 1;
	for (int i = 1; i <= n; i++)
	{
		bool bOk = false;
		for (; countEdge <= m && !bOk; countEdge++)
		{
			INT from = edges[countEdge].from;
			INT to = edges[countEdge].to;
			INT cost = edges[countEdge].cost;
			if (ds.judge(from, to))
			{
				continue;
			}
			else
			{
				bOk = true;
				ds.unite(from, to);
				printf("%d\n", cost); //INT is int here
			}
		}
		if (!bOk) puts("INF");
	}
}

int main()
{
	run();
	return 0;
}
