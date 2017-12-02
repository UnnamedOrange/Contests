#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
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
	int a;
	scanf("%d", &a);
	return a;
}

int n, m;
std::vector<int> cost;
std::vector<std::vector<int> > G;
std::vector<std::vector<int> > GT;
std::vector<bool> linkEnd;
std::vector<bool> vis;
std::vector<int> minCost;

void init()
{
	n = readIn();
	m = readIn();
	cost.resize(n + 1);
	G.resize(n + 1);
	GT.resize(n + 1);
	linkEnd.resize(n + 1);
	vis.resize(n + 1);
	minCost.resize(n + 1, 0x3fffffff);
	for (int i = 1; i <= n; i++)
	{
		cost[i] = readIn();
	}
	for (int i = 1; i <= m; i++)
	{
		int from = readIn();
		int to = readIn();
		int type = readIn();
		G[from].push_back(to);
		GT[to].push_back(from);
		if (type == 2)
		{
			G[to].push_back(from);
			G[from].push_back(to);
		}
	}
}
void dfs(int start = n)
{
	if (linkEnd[start]) return;
	linkEnd[start] = true;
	for (int i = 0; i < GT[start].size(); i++)
	{
		dfs(GT[start][i]);
	}
}
void SPFA()
{
	minCost[1] = cost[1];
	std::queue<int> Q;
	Q.push(1);
	vis[1] = true;
	while (!Q.empty())
	{
		int from = Q.front();
		Q.pop();
		vis[from] = false;
		for (int i = 0; i < G[from].size(); i++)
		{
			int& to = G[from][i];
			int toVal = std::min(minCost[from], cost[to]);
			if (toVal < minCost[to])
			{
				minCost[to] = toVal;
				if (vis[to]) continue;
				Q.push(to);
				vis[to] = true;
			}
		}
	}
}

int main()
{
	init();
	dfs();
	SPFA();
	int ans = 0;
	for (int i = 1; i <= n; i++)
	{
		if (!linkEnd[i]) continue;
		ans = std::max(ans, cost[i] - minCost[i]);
	}
	printf("%d\n", ans);
	return 0;
}