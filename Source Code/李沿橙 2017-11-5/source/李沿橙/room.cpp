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
typedef int INT;
using std::cin;
using std::cout;
using std::endl;
inline INT readIn()
{
	INT a = 0;
	bool minus = false;
	char ch = getchar();
	while (!(ch == '-' || (ch >= '0' && ch <= '9'))) ch = getchar();
	if (ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		a = a * 10 + (ch - '0');
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}
inline void printOut(INT x)
{
	char buffer[20];
	INT length = 0;
	bool minus = x < 0;
	if (minus) x = -x;
	do
	{
		buffer[length++] = x % 10 + '0';
		x /= 10;
	} while (x);
	if (minus) buffer[length++] = '-';
	do
	{
		putchar(buffer[--length]);
	} while (length);
	putchar('\n');
}

const INT INF = 0x3f3f3f3f;
const INT maxn = 5005;
const INT maxm = 6005;
const INT maxk = 1030;
INT n, m, k;
INT key[maxn];
struct Edge
{
	INT to;
	INT need;
	INT next;
} edges[maxm];
INT head[maxn];
void addEdge()
{
	static INT i;
	i++;
	INT from = readIn();
	INT to = readIn();
	edges[i].to = to;
	edges[i].next = head[from];
	head[from] = i;
	for (int j = 0; j < k; j++)
		edges[i].need |= readIn() << j;
}

template<typename T, INT size>
struct Queue
{
	T c[size];
	INT head, tail;
	Queue() : head(), tail() {}
	bool empty()
	{
		return head == tail;
	}
	void push(T x)
	{
		c[tail++] = x;
	}
	T pop()
	{
		return c[head++];
	}
};

#define RunInstance(x) delete new x
struct cheat
{
	INT dis[maxn];
	Queue<INT, maxn> q;

	cheat()
	{
		std::fill(dis + 1, dis + 1 + n, INF);
		dis[1] = 0;
		q.push(1);
		while (!q.empty())
		{
			INT from = q.pop();
			for (int i = head[from]; i; i = edges[i].next)
			{
				INT to = edges[i].to;
				if (dis[to] >= INF)
				{
					dis[to] = dis[from] + 1;
					q.push(to);
				}
			}
		}
		if (dis[n] >= INF)
			puts("No Solution");
		else
			printOut(dis[n]);
	}
};
struct work
{
	INT dis[maxn][(1 << 10) + 5];
	struct Node
	{
		INT u;
		INT s;
		Node() {}
		Node(INT u, INT s) : u(u), s(s) {}
	};
	Queue<Node, maxn * maxk> q;

	work()
	{
		memset(dis, 0x3f, sizeof(dis));
		dis[1][key[1]] = 0;
		q.push(Node(1, key[1]));
		while (!q.empty())
		{
			Node from = q.pop();
			for (int i = head[from.u]; i; i = edges[i].next)
			{
				Edge& e = edges[i];
				if ((from.s & e.need) != e.need) continue;
				INT to = e.to;
				INT s = from.s | key[to];
				if (dis[to][s] >= INF)
				{
					dis[to][s] = dis[from.u][from.s] + 1;
					q.push(Node(to, s));
				}
			}
		}
		INT ans = INF;
		for (int i = 0; i < (1 << k); i++)
			ans = std::min(ans, dis[n][i]);
		if (ans >= INF)
			puts("No Solution");
		else
			printOut(ans);
	}
};

void run()
{
	n = readIn();
	m = readIn();
	k = readIn();
	for (int i = 1; i <= n; i++)
		for (int j = 0; j < k; j++)
			key[i] |= readIn() << j;

	for (int i = 1; i <= m; i++)
		addEdge();

	if (!k)
		RunInstance(cheat);
	else
		RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("room.in", "r", stdin);
	freopen("room.out", "w", stdout);
#endif
	run();
	return 0;
}