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

const INT maxn = 2e5 + 5;
const INT maxm = 4e5 + 5;
INT n, m;
INT num[maxn];
struct edge
{
	INT to;
	INT cost;
	INT next;
} edges[maxm];
INT head[maxn];

INT dis[maxn];
INT next[maxn];
bool vis[maxn];
INT SPFA()
{
	std::queue<INT> q;
	q.push(n);
	vis[n] = true;
	dis[n] = 0;
	next[n] = -1;
	while (!q.empty())
	{
		INT from = q.front();
		q.pop();
		vis[from] = false;
		for (int i = head[from]; i; i = edges[i].next)
		{
			INT to = edges[i].to;
			INT cost = edges[i].cost;
			if (!next[to] || dis[to] > dis[from] + cost || dis[to] == dis[from] + cost && num[next[to]] > num[from])
			{
				dis[to] = dis[from] + cost;
				next[to] = from;
				if (!vis[to])
				{
					q.push(to);
					vis[to] = true;
				}
			}
		}
	}
	return dis[1];
}

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= n; i++)
	{
		num[i] = readIn();
	}
	for (int i = 1; i <= m; i++)
	{
		edges[i].to = readIn();
		INT from = readIn();
		edges[i].cost = readIn();
		edges[i].next = head[from];
		head[from] = i;
	}

	printf("%lld\n", SPFA()); //INT is long long here

	INT pos = 1;
	while (~pos)
	{
		printf("%lld ", num[pos]); //INT is long long here
		pos = next[pos];
	}
}

int main()
{
	run();
	return 0;
}