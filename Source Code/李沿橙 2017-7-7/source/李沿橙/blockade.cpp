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
#define FOR(x, f, t) for(int x = (f); x <= (t); x++)
inline int readIn()
{
	int a;
	scanf("%d", &a);
	return a;
}

const int maxn = 50005;
const int maxIndex = 16;
int n,m;
struct edge
{
	int to;
	int cost;

	edge(int to = 0, int cost = 0):to(to), cost(cost)
	{

	}
};
std::vector<std::vector<edge> > edges;
int troops_[maxn];
int troops[maxn];

int depth[maxn];
int parent[maxIndex][maxn];
long long dis[maxIndex][maxn];

bool check(int val)
{
	for (int i = 1; i <= m; i++)
	{
		troops[i] = troops_[i];
		long long length = val;
		for(int k = maxIndex - 1; ~k; k--)
		{
			if(parent[k][troops[i]] && dis[k][troops[i]] <= length)
			{
				length -= dis[k][troops[i]];
				troops[i] = parent[k][troops[i]];
			}
		}
	}
}
void divide()
{
	long long left = 0, right = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j < edges[i].size(); j++)
		{
			right += edges[i][j].cost;
		}
	}
	right /= 2;
	right++;

	while(right - left > 1)
	{
		int mid = left + (right - left) / 2;
		if(!check(mid))
		{
			left = mid;
		}
		else
		{
			right = mid;
		}
	}
	if(check(left)) left++;
	printf("%d\n", left);
}
void multi()
{
	for (int i = 1; 1 << i < n; i++)
	{
		for (int j = 2; j <= n; j++)
		{
			parent[i][j] = parent[i - 1][parent[i - 1][j]];
			dis[i][j] = dis[i - 1][j] + dis[i - 1][parent[i - 1][j]];
		}
	}
}
void dfs(int root = 1, int father = 0, int dep = 1)
{
	for(int i = 0; i < edges[root].size(); i++)
	{
		const int& to = edges[root][i].to;
		const int& cost = edges[root][i].cost;
		if(to == father) continue;
		parent[0][to] = root;
		dis[0][to] = cost;
		depth[to] = dep + 1;
		dfs(to, root, dep + 1);
	}
}
void input()
{
	n = readIn();
	edges.resize(n+1);

	FOR (i, 2, n)
	{
		int from = readIn();
		int to = readIn();
		int cost = readIn();
		edges[from].push_back(edge(to, cost));
		edges[to].push_back(edge(from, cost));
	}
	m = readIn();
	if(edges[1].size() > m)
	{
		printf("-1\n");
		return;
	}
	FOR (i, 1, m)
	{
		troops_[i] = readIn();
	}
}
void run()
{
	input();
	dfs();
	multi();
	divide();
}

int main()
{
	run();
	return 0;
}
