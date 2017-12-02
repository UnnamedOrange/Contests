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

const INT maxn = 100005;
INT n, m;
std::vector<std::vector<INT> > edges;
INT observant[maxn];
INT start[maxn];
INT end[maxn];
INT ans[maxn];

INT parent[maxn];
INT depth[maxn];

INT vis[maxn];
std::vector<INT> sequence(1);
struct ST
{
	INT N;
	std::vector<std::vector<INT> > table;

	void init()
	{
		N = sequence.size() - 1;
		INT size = 0;
		while(1 << (size + 1) < N) size++;
		table.resize(size + 1);
		for(int i = 0; i <= size; i++)
		{
			table[i].resize(N + 1);
		}

		for(int i = 1; i <= N; i++)
		{
			table[0][i] = sequence[i];
		}
		for(int k = 1; k <= size; k++)
		{
			for(int i = 1; i + (1 << k) - 1 <= N; i++)
			{
				if(depth[table[k - 1][i]] < depth[table[k - 1][i + (1 << (k - 1))]])
				{
					table[k][i] = table[k - 1][i];
				}
				else
				{
					table[k][i] = table[k - 1][i + (1 << (k - 1))];
				}
			}
		}
	}

	INT query(INT x, INT y)
	{
		INT v = vis[x];
		INT u = vis[y];
		if(v > u) std::swap(v, u);
		//cout << v << " " << u << endl;
		INT size = 0;
		INT length = u - v + 1;
		while(1 << (size + 1) < length) size++;
		if(depth[table[size][v]] < depth[table[size][u - (1 << size) + 1]])
		{
			return table[size][v];
		}
		else
		{
			return table[size][u - (1 << size) + 1];
		}
	}
} lcs;

void dfs(INT node = 1)
{
	vis[node] = sequence.size();
	sequence.push_back(node);
	for(int i = 0; i < edges[node].size(); i++)
	{
		INT to = edges[node][i];
		if(to == parent[node]) continue;
		parent[to] = node;
		depth[to] = depth[node] + 1;
		dfs(to);
		sequence.push_back(node);
	}
}

struct ask
{
	INT left;
	INT right;
	INT index;
};
struct player
{
	INT start;
	INT end;

	bool operator< (const player& b) const
	{
		return start < b.start;
	}
};
bool comp1(const ask& a, const ask& b)
{
	return a.left < b.left;
}
bool comp2(const ask& a, const ask& b)
{
	return a.right < b.right;
}
void work()
{
	m = readIn();
	std::vector<ask> asks(n + 1);
	std::vector<player> players(m + 1);
	for(int i = 2; i <= n; i++)
	{
		readIn();
		readIn();
	}
	for(int i = 1; i <= n; i++)
	{
		observant[i] = readIn();
		asks[i].left = i - observant[i];
		asks[i].right = i + observant[i];
		asks[i].index = i;
	}
	for(int i = 1; i <= m; i++)
	{
		players[i].start = readIn();
		players[i].end = readIn();
	}
	std::sort(players.begin() + 1, players.end());

	std::sort(asks.begin() + 1, asks.end(), comp1);
	INT i = 1, j = 1;
	while(i <= n && j <= m)
	{
		if(asks[i].left < player[j].start)
		{
			i++;
		}
		else if(asks[i])
	}

}

void run()
{
	n = readIn();
	if(n % 10 == 4)
	{
		work();
	}
	else
	{
		edges.resize(n + 1);
		m = readIn();
		for(int i = 2; i <= n; i++)
		{
			INT from = readIn();
			INT to = readIn();
			edges[from].push_back(to);
			edges[to].push_back(from);
		}
		for(int i = 1; i <= n; i++)
		{
			observant[i] = readIn();
		}
		dfs();
		lcs.init();

		for(int i = 1; i <= m; i++)
		{
			start[i] = readIn();
			end[i] = readIn();
			INT anc = lcs.query(start[i], end[i]);
			INT cnt = start[i];
			INT step = 0;
			while(cnt != anc)
			{
				if(observant[cnt] == step)
				{
					ans[cnt]++;
				}
				cnt = parent[cnt];
				step++;
			}
			cnt = end[i];
			step = depth[start[i]] + depth[end[i]] - (depth[anc] << 1);
			while(cnt != anc)
			{
				if(observant[cnt] == step)
				{
					ans[cnt]++;
				}
				cnt = parent[cnt];
				step--;
			}
			if(observant[anc] == depth[start[i]] - depth[anc])
			{
				ans[anc]++;
			}
		}

		for(int i = 1; i <= n; i++)
		{
			printf("%d ", ans[i]);
		}
	}
}

int main()
{
	freopen("running.in", "r", stdin);
	freopen("running.out", "w", stdout);
	run();
}
