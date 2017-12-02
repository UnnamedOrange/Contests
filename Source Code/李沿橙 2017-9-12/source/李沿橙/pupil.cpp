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

const INT maxn = INT(1e3) + 5;
INT n;
INT A, B;
struct City
{
	INT x;
	INT y;

	void read()
	{
		x = readIn();
		y = readIn();
	}
} cities[maxn];
struct Edge
{
	INT from;
	INT to;
	INT cost;

	Edge() {}
	Edge(INT from, INT to) : from(from), to(to), cost(std::abs(cities[from].x - cities[to].x) + std::abs(cities[from].y - cities[to].y)) {}

	bool operator< (const Edge& b) const
	{
		return cost < b.cost;
	}

	Edge& DebugPrint()
	{
		cout << from << ", " << to << " " << cost << endl;
		return *this;
	}
};
std::vector<Edge> edges;
struct DS
{
	std::vector<INT> parent;

	DS(INT size) : parent(size + 1)
	{
		for(int i = 1; i <= size; i++)
		{
			parent[i] = i;
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

void run()
{
	n = readIn();
	A = readIn();
	B = readIn();
	for(int i = 1; i <= n; i++) cities[i].read();

	edges.reserve(n * (n - 1) / 2);
	for(int i = 1; i <= n; i++)
	{
		for(int j = i + 1; j <= n; j++)
		{
			edges.push_back(Edge(i, j));
		}
	}
	std::sort(edges.begin(), edges.end());

	DS ds(n);
	INT ans = n * A;
	for(int i = 0; i < edges.size(); i++)
	{
		if(edges[i].cost * B >= A) break;
		if(ds.judge(edges[i].from, edges[i].to)) continue;
		ans -= A;
		ans += edges[i].cost * B;
		ds.unite(edges[i].from, edges[i].to);
	}
	cout << ans << endl;
}

int main()
{
#ifndef JUDGE
	freopen("pupil.in", "r", stdin);
	freopen("pupil.out", "w", stdout);
#endif
	run();
	return 0;
}
