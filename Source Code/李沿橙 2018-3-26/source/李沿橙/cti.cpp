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
		a = a * 10 - (ch - '0');
		ch = getchar();
	}
	if (positive) a = -a;
	return a;
}
void printOut(INT_PUT x)
{
	char buffer[20];
	int length = 0;
	if (x < 0) putchar('-');
	else x = -x;
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
}

const int INF = (~(int(1) << (sizeof(int) * 8 - 1))) >> 1;
int nVertex;
struct NetworkFlow
{
	static const int maxv = 10005;
	struct Edge
	{
		int from, to, cap, flow;
		Edge() {}
		Edge(int from, int to, int cap) : flow(), from(from), to(to), cap(cap) {}
	};
	std::vector<Edge> edges;
	std::vector<int> G[maxv];

	void addEdge(int from, int to, int cap)
	{
		edges.push_back(Edge(from, to, cap));
		edges.push_back(Edge(to, from, 0));
		int i = edges.size();
		G[from].push_back(i - 2);
		G[to].push_back(i - 1);
	}

	int s, t;

	int level[maxv];
	int cur[maxv];
	int DFS(int node, int opt)
	{
		if (node == t || !opt) return opt;
		int flow = 0;
		for (int& i = cur[node]; i < G[node].size(); i++)
		{
			Edge& e = edges[G[node][i]];
			int t;
			if (level[node] + 1 == level[e.to] && (t = DFS(e.to, std::min(opt, e.cap - e.flow))))
			{
				flow += t;
				e.flow += t;
				edges[G[node][i] ^ 1].flow -= t;
				opt -= t;
				if (!opt) break;
			}
		}
		return flow;
	}

	int vis[maxv];
	struct Queue
	{
		int c[maxv];
		int head, tail;
		Queue() : head(), tail() {}
		bool empty() { return head == tail; }
		void clear() { head = tail = 0; }
		void push(int x) { c[tail++] = x; }
		void pop() { head++; }
		int front() { return c[head]; }
	} q;
	bool BFS()
	{
		static int stamp;
		stamp++;
		q.clear();
		level[s] = 0;
		q.push(s);
		vis[s] = stamp;
		while (!q.empty())
		{
			int from = q.front();
			q.pop();
			for (register int i = 0; i < G[from].size(); i++)
			{
				const Edge& e = edges[G[from][i]];
				if (e.cap > e.flow && vis[e.to] != stamp)
				{
					level[e.to] = level[from] + 1;
					q.push(e.to);
					vis[e.to] = stamp;
				}
			}
		}
		return vis[t] == stamp;
	}

	int Dinic()
	{
		int flow = 0;
		while (BFS())
		{
			memset(cur, 0, sizeof(cur));
			flow += DFS(s, INF);
		}
		return flow;
	}
} nf;

const int maxn = 55;
int n, m;
int rect[maxn][maxn];

struct CodeHelper
{
	int x, y;
	int code;
	int sum;
	CodeHelper() {}
	CodeHelper(int x, int y, int code, int sum) : x(x), y(y), code(code), sum(sum) {}
};
std::vector<CodeHelper> helper;
std::vector<std::pair<int, int> > row;
std::vector<std::pair<int, int> > colum;
int cross[maxn][maxn];

int accum;
void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			rect[i][j] = readIn();

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			if (rect[i][j] == -1)
				nVertex += i - 1;
			else if (rect[i][j] == -2)
				nVertex += n - i;
			else if (rect[i][j] == -3)
				nVertex += j - 1;
			else if (rect[i][j] == -4)
				nVertex += m - j;
		}
	nf.s = 0;
	nf.t = nVertex + 1;

	for (int x = 1; x <= n; x++)
	{
		int sum = 0;
		for (int y = 1; y <= m; y++)
		{
			if (rect[x][y] > 0) sum += rect[x][y];
			if (rect[x][y] == -3)
			{
				accum += sum;
				row.push_back(std::make_pair(helper.size(), 0));
				for (int i = y - 1; i; i--)
				{
					helper.push_back(CodeHelper(x, i, helper.size() + 1, sum));
					cross[x][i] = helper.size();
				}
				row.back().second = helper.size() - 1;
			}
		}
		sum = 0;
		for (int y = m; y; y--)
		{
			if (rect[x][y] > 0) sum += rect[x][y];
			if (rect[x][y] == -4)
			{
				accum += sum;
				row.push_back(std::make_pair(helper.size(), 0));
				for (int i = y + 1; i <= m; i++)
				{
					helper.push_back(CodeHelper(x, i, helper.size() + 1, sum));
					cross[x][i] = helper.size();
				}
				row.back().second = helper.size() - 1;
			}
		}
	}
	for (int i = 0; i < row.size(); i++)
	{
		int begin = row[i].first;
		int end = row[i].second;
		nf.addEdge(nf.s, helper[begin].code, helper[begin].sum);
		for (int j = begin; j < end; j++)
		{
			int x = helper[j].x;
			int y = helper[j].y;
			nf.addEdge(helper[j].code, helper[j + 1].code, helper[j].sum - rect[x][y]);
		}
		nf.addEdge(helper[end].code, nf.t, helper[end].sum - rect[helper[end].x][helper[end].y]);
	}

	for (int y = 1; y <= m; y++)
	{
		int sum = 0;
		for (int x = 1; x <= n; x++)
		{
			if (rect[x][y] > 0) sum += rect[x][y];
			if (rect[x][y] == -1)
			{
				accum += sum;
				colum.push_back(std::make_pair(helper.size(), 0));
				for (int i = x - 1; i; i--)
				{
					helper.push_back(CodeHelper(i, y, helper.size() + 1, sum));
					if (cross[i][y])
					{
						nf.addEdge(cross[i][y], helper.size(), INF);
					}
				}
				colum.back().second = helper.size() - 1;
			}
		}
		sum = 0;
		for (int x = n; x; x--)
		{
			if (rect[x][y] > 0) sum += rect[x][y];
			if (rect[x][y] == -2)
			{
				accum += sum;
				colum.push_back(std::make_pair(helper.size(), 0));
				for (int i = x + 1; i <= n; i++)
				{
					helper.push_back(CodeHelper(i, y, helper.size() + 1, sum));
					if (cross[i][y])
					{
						nf.addEdge(cross[i][y], helper.size(), INF);
					}
				}
				colum.back().second = helper.size() - 1;
			}
		}
	}
	for (int i = 0; i < colum.size(); i++)
	{
		int begin = colum[i].first;
		int end = colum[i].second;
		nf.addEdge(helper[begin].code, nf.t, helper[begin].sum);
		for (int j = begin + 1; j <= end; j++)
		{
			int x = helper[j - 1].x;
			int y = helper[j - 1].y;
			nf.addEdge(helper[j].code, helper[j - 1].code, helper[j - 1].sum - rect[x][y]);
		}
		nf.addEdge(nf.s, helper[end].code, helper[end].sum - rect[helper[end].x][helper[end].y]);
	}

	printOut(accum - nf.Dinic());
}

int main()
{
#ifndef LOCAL
	freopen("cti.in", "r", stdin);
	freopen("cti.out", "w", stdout);
#endif
	run();
	return 0;
}