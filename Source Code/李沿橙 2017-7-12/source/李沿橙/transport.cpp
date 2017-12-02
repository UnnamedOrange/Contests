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
using std::cin;
using std::cout;
using std::endl;
inline int readIn()
{
	int a = 0;
	char ch = getchar();
	while(!(ch >= '0' && ch <= '9')) ch = getchar();
	while(ch >= '0' && ch <= '9')
	{
		a *= 10;
		a += ch;
		a -= '0';
		ch = getchar();
	}
	return a;
}

const int maxn = 300005;
int n, m;
struct edge
{
	int to;
	int cost;
	int index;
	edge(int to = 0, int cost = 0, int index = 0) : to(to), cost(cost), index(index)
	{
	}
};
std::vector<std::vector<edge> > edges;
int eCost[maxn];
int from[maxn];
int to[maxn];

int parent[maxn];
int edgeIndex[maxn];
int depth[maxn];
int length[maxn];

void solve()
{

}

void dfs(int node, int par = 0)
{
	depth[node] = depth[par] + 1;
	parent[node] = par;
	for(int i = 0; i < edges[node].size(); i++)
	{
		int& to = edges[node][i].to;
		int& cost = edges[node][i].cost;
		if(to == par) continue;
		length[to] = length[node] + cost;
		edgeIndex[to] = edges[node][i].index;
		dfs(to, node);
	}
}
void solve1()
{
	int& f = from[1];
	int& t = to[1];
	dfs(f);
	std::vector<int> Index;
	int node = t;
	int ans = length[t];
	while(parent[node])
	{
		Index.push_back(edgeIndex[node]);
		node = parent[node];
	}
	for(int i = 0; i < Index.size(); i++)
	{
		ans = std::min(ans, length[t] - eCost[Index[i]]);
	}
	printf("%d\n", ans);
}
void run()
{
	n = readIn();
	m = readIn();
	edges.resize(n + 1);
	for(int i = 1; i <= n - 1; i++)
	{
		int from = readIn();
		int to = readIn();
		int cost = eCost[i] = readIn();
		edges[from].push_back(edge(to, cost, i));
		edges[to].push_back(edge(from, cost, i));
	}
	for(int i = 1; i <= m; i++)
	{
		from[i] = readIn();
		to[i] = readIn();
	}

	if(m == 1)
	{
		solve1();
	}
	else
	{
		solve();
	}
}

int main()
{
#ifndef DEBUG
	freopen("transport.in","r",stdin);
	freopen("transport.out","w",stdout);
#endif
	run();
	return 0;
}
