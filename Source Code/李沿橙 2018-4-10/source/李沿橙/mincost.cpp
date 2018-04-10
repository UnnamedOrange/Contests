#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cassert>
#include <cctype>
#include <climits>
#include <ctime>
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
#include <list>
#include <functional>
typedef long long LL;
typedef unsigned long long ULL;
using std::cin;
using std::cout;
using std::endl;
typedef int INT_PUT;
INT_PUT readIn()
{
	INT_PUT a = 0;
	bool positive = true;
	char ch = getchar();
	while (!(ch == '-' || std::isdigit(ch))) ch = getchar();
	if (ch == '-')
	{
		positive = false;
		ch = getchar();
	}
	while (std::isdigit(ch))
	{
		(a *= 10) -= ch - '0';
		ch = getchar();
	}
	return positive ? -a : a;
}
void printOut(INT_PUT x)
{
	char buffer[20];
	int length = 0;
	if (x < 0) putchar('-');
	else x = -x;
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
	putchar('\n');
}

const int INF = (~(int(1) << (sizeof(int) * 8 - 1)));
const int maxn = int(3e5) + 5;
const int maxm = int(5e5) + 5;
int n, m, K;
int a[maxn];
int b[maxn];

std::vector<std::vector<int> > G;

#define RunInstance(x) delete new x
struct brute1
{
	static const int maxN = 25;
	int count1[(1 << 20) + 5];
	int S;
	int vis[maxN];
	
	void DFS(int node)
	{
		vis[node] = S;
		for(int i = 0; i < G[node].size(); i++)
		{
			int to = G[node][i];
			if(vis[to] == S || !(S & (1 << (to - 1)))) continue;
			DFS(to);
		}
	}
	
	brute1() : vis()
	{
		int U = 1 << n;
		count1[0] = 0;
		for(int i = 1; i < U; i++)
			count1[i] = count1[i ^ (i & -i)] + 1;
		
		int ans = INF;
		for(S = 1; S < U; S++)
		{
			if(count1[S] != K) continue;
			bool bOk = true;
			bool visited = false;
			int maxa = 0;
			int maxb = 0;
			for(int i = 0; i < n; i++)
			{
				if(S & (1 << i))
				{
					if(visited && vis[i + 1] != S) 
					{
						bOk = false;
						break;
					}
					maxa = std::max(maxa, a[i + 1]);
					maxb = std::max(maxb, b[i + 1]);
					visited = true;
					DFS(i + 1);
				}
			}
			if (bOk)
			{
				ans = std::min(ans, maxa + maxb);
			}
		}
		if(ans >= INF) puts("no solution");
		else printOut(ans);
	}
};
struct brute2
{
	static const int maxN = 5005;
	int idxa[maxN];
	int idxb[maxN];
	
	static bool comp1(const int& x, const int& y)
	{
		return a[x] < a[y];
	}
	static bool comp2(const int& x, const int& y)
	{
		return b[x] < b[y];
	}
	bool visa[maxN];
	int visb[maxN];
	
	struct DS
	{
		int parent[maxN];
		int size[maxN];
		void clear()
		{
			for(register int i = 1; i <= n; i++)
				parent[i] = i;
			for(register int i = 1; i <= n; i++)
				size[i] = 1;
		}
		int find(int x)
		{
			if(x == parent[x]) return x;
			return parent[x] = find(parent[x]);
		}
		void unite(int x, int y)
		{
			int px = find(x), py = find(y);
			if(px == py) return;
			if(size[px] < size[py]) std::swap(size[px], size[py]);
			size[px] += size[py];
			parent[py] = px;
		}
	} ds;
	
	brute2() : visa()
	{
		int ans = INF;
		if(K == 1)
		{
			for(int i = 1; i <= n; i++)
				ans = std::min(ans, a[i] + b[i]);
			printOut(ans);
			return;
		}
		
		for (int i = 1; i <= n; i++)
			idxa[i] = i;
		for (int i = 1; i <= n; i++)
			idxb[i] = i;
		std::sort(idxa + 1, idxa + 1 + n, comp1);
		std::sort(idxb + 1, idxb + 1 + n, comp2);
		
		for (int i = 1; i <= n; i++)
		{
			visa[idxa[i]] = true;
			ds.clear();
			for (int j = 1; j <= n; j++)
			{
				bool bBreak = false;
				int node = idxb[j];
				visb[node] = i;
				if(visa[node])
				{
					for(int k = 0; k < G[node].size(); k++)
					{
						int to = G[node][k];
						if(!visa[to] || visb[to] != i) continue;
						ds.unite(node, to);
						if(ds.size[ds.find(node)] >= K)
						{
							ans = std::min(ans, a[idxa[i]] + b[node]);
							bBreak = true;
							break;
						}
					}
				}
				if(bBreak) break;
			}
		}
		if(ans >= INF) puts("no solution");
		else printOut(ans);
	}
};
struct cheat
{
	cheat()
	{
		
	}
};

void run()
{
	n = readIn();
	m = readIn();
	K = readIn();
	G.resize(n + 1);
	for(int i = 1; i <= n; i++)
	{
		a[i] = readIn();
		b[i] = readIn();
	}
	
	for(int i = 1; i <= m; i++)
	{
		int from = readIn();
		int to = readIn();
		G[from].push_back(to);
		G[to].push_back(from);
	}
	
	if(n <= 20)
		RunInstance(brute1);
	else if(n <= 5000)
		RunInstance(brute2);
	else
		RunInstance(cheat);
}

int main()
{
#ifndef LOCAL
	freopen("mincost.in", "r", stdin);
	freopen("mincost.out", "w", stdout);
#endif
	run();
	return 0;
}
