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
typedef long long INT;
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

const INT maxn = 105;
INT n, m;
INT inDgr[maxn];
INT outDgr[maxn];
struct node
{
	INT c;
	INT u;

	node():c(0), u(0)
	{
	}
} nodes[maxn];
struct edge
{
	INT to;
	INT w;
	edge(INT to = 0, INT w = 0): to(to), w(w)
	{
	}
};
std::vector<std::vector<edge> > edges;
bool vis[maxn];

void run()
{
	n = readIn();
	m = readIn();
	edges.resize(n + 1);
	for(int i = 1; i <= n; i++)
	{
		nodes[i].c = readIn();
		nodes[i].u = readIn();
	}
	for(int i = 1; i <= m; i++)
	{
		INT from = readIn();
		INT to = readIn();
		INT w = readIn();
		edges[from].push_back(edge(to, w));
		inDgr[to]++;
		outDgr[from]++;
	}

	std::queue<INT> q;
	for(int i = 1; i <= n; i++)
	{
		if(!inDgr[i])
		{
			q.push(i);
			vis[i] = true;
		}
	}

	while(!q.empty())
	{
		INT from = q.front();
		q.pop();
		if(inDgr[from]) nodes[from].c -= nodes[from].u;
		for(int i = 0; i < edges[from].size(); i++)
		{
			INT& to = edges[from][i].to;
			INT& w = edges[from][i].w;
			if(nodes[from].c > 0)
			{
				nodes[to].c += w * nodes[from].c;
			}
			if(!vis[to])
			{
				q.push(to);
				vis[to] = true;
			}
		}
	}

	bool bOut = false;
	for(int i = 1; i <= n; i++)
	{
		if(!outDgr[i] && nodes[i].c)
		{
			bOut = true;
			break;
		}
	}

	if(bOut)
	{
		for(int i = 1; i <= n; i++)
		{
			if(!outDgr[i] && nodes[i].c > 0)
			{
				printf("%d %d\n", i, nodes[i].c);
			}
		}
	}
	else
	{
		puts("NULL");
	}
}

int main()
{
	run();
	return 0;
}
