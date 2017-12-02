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
	while(!(ch == '-' || ch >= '0' && ch <= '9')) ch = getchar();
	if(ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9')
	{
		a *= 10;
		a += ch;
		a -= '0';
		ch = getchar();
	}
	if(minus) a = -a;
	return a;
}

const INT maxn = 2005;
INT n, m;
INT ans;

struct Node
{
	INT value;
	INT cost;
} nodes[maxn];
std::vector<std::vector<INT> > edges;

#define RunInstance(x) delete new x
struct work
{
	INT f[maxn][maxn];
	INT parent[maxn];
	INT seq[maxn];
	INT size[maxn];

	work() : f(), parent(), size(), seq()
	{
		dfs();

		for (int i = n; i >= 1; i--)
		{
			INT node = seq[i];
			INT c = nodes[node].cost;
			INT v = nodes[node].value;
			INT s = size[node];
			for (int j = 0; j <= m; j++)
			{
				if (j < c) f[i][j] = std::max(f[i + s][j], 0);
				else f[i][j] = std::max(std::max(f[i + 1][j - c] + v, f[i + s][j]), 0);
			}
		}
		cout << f[1][m] << endl;
	}

	void dfs(INT node = 1)
	{
		static INT clock = 0;
		seq[++clock] = node;
		for(int i = 0; i < edges[node].size(); i++)
		{
			INT to = edges[node][i];
			if(to == parent[node]) continue;
			parent[to] = node;
			dfs(to);
			size[node] += size[to];
		}
		size[node]++;
	}
};
struct cheat1
{
	INT next[maxn];

	cheat1() : next()
	{
		dfs();
		INT ans = 0;
		INT sum = 0;
		INT poison = 0;
		INT pos = 1;
		while(pos)
		{
			if(m - poison < nodes[pos].cost) break;
			sum += nodes[pos].value;
			poison += nodes[pos].cost;
			ans = std::max(ans, sum);
			pos = next[pos];
		}
		cout << ans << endl;
	}
	INT dfs(INT node = 1, INT parent = 0)
	{
		for(int i = 0; i < edges[node].size(); i++)
		{
			INT to = edges[node][i];
			if(to == parent) continue;
			next[node] = to;
			dfs(to, node);
		}
	}
};

bool isLine(INT node = 1, INT parent = 0)
{
	bool haveParent = false;
	INT to = 0;
	for(int i = 0; i < edges[node].size(); i++)
	{
		if(edges[node][i] == parent)
		{
			haveParent = true;
			continue;
		}
		if(to) return false;
		to = edges[node][i];
	}
	if(!to) return true;
	return isLine(to, node);
}

void run()
{
	n = readIn();
	m = readIn();
	edges.resize(n + 1);
	for(int i = 1; i <= n; i++)
	{
		nodes[i].value = readIn();
		nodes[i].cost = readIn();
	}

	for(int i = 2; i <= n; i++)
	{
		INT from = readIn();
		INT to = readIn();
		edges[from].push_back(to);
		edges[to].push_back(from);
	}
	if(isLine()) RunInstance(cheat1);
	else RunInstance(work);
}

int main()
{
	run();
	return 0;
}
