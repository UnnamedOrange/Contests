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
typedef int INT;
int readIn()
{
	bool minus = false;
	int a = 0;
	int ch = getchar();
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
	if(minus) a = -a;
	return a;
}

const int maxn = 10005;
int n, m;
std::vector<std::vector<int> > G;
std::vector<std::vector<int> > GT;
int s, t;

struct node
{
	int v;
	int dis;
	node(int v = 0, int dis = 0) : v(v), dis(dis)
	{
	}
};
bool unavailable[maxn];
bool vis[maxn];
int bfs(bool final = false)
{
	memset(vis, 0, sizeof(vis));
	if(unavailable[t]) return 0;
	vis[t] = true;
	std::queue<node> q;
	q.push(node(t, 0));
	while (!q.empty())
	{
		node status = q.front();
		q.pop();
		int& from = status.v;
		int& dis = status.dis;
		for (int i = 0; i < GT[from].size(); i++)
		{
			int& to = GT[from][i];
			if (vis[to]) continue;
			if (unavailable[to]) continue;
			vis[to] = true;
			q.push(node(to, dis + 1));
			if (final && to == s) return dis + 1;
		}
	}
	return 0;
}

void run()
{
	n = readIn();
	m = readIn();
	G.resize(n + 1);
	GT.resize(n + 1);
	for (int i = 1; i <= m; i++)
	{
		int from = readIn();
		int to = readIn();
		if(from == to) continue;
		G[from].push_back(to);
		GT[to].push_back(from);
	}
	s = readIn();
	t = readIn();

	bfs();
	for (int i = 1; i <= n; i++)
	{
		unavailable[i] = !vis[i];
		if (unavailable[i]) continue;
		for (int j = 0; j < G[i].size(); j++)
		{
			if (!vis[G[i][j]])
			{
				unavailable[i] = true;
				break;
			}
		}
	}
	if (int dis = bfs(true))
	{
		cout << dis << endl;
	}
	else
	{
		cout << -1 << endl;
	}
}

int main()
{
	run();
	return 0;
}
