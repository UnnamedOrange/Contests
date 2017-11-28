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
	char buffer[15];
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
}

const INT maxn = INT(5e5) + 5;
INT n;
INT color[maxn];
struct Edge
{
	INT to;
	INT next;
} edges[maxn];
INT head[maxn];
void addEdge(INT from, INT to)
{
	static INT i;
	i++;
	edges[i].to = to;
	edges[i].next = head[from];
	head[from] = i;
}

INT ans[maxn];
struct Node
{
	INT u;
	bool flip;
	Node() {}
	Node(INT u, bool flip) : u(u), flip(flip) {}
};
void bfs()
{
	std::queue<Node> q;
	q.push(Node(1, false));
	while (!q.empty())
	{
		Node from = q.front();
		q.pop();
		bool c = color[from.u] ^ from.flip;
		if (c) ans[++ans[0]] = from.u;
		for (int i = head[from.u]; i; i = edges[i].next)
		{
			q.push(Node(edges[i].to, from.flip ^ c));
		}
	}
}

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
		color[i] = readIn();
	for (int i = 2; i <= n; i++)
	{
		INT from = readIn();
		INT to = readIn();
		addEdge(from, to);
	}

	bfs();
	std::sort(ans + 1, ans + 1 + ans[0]);
	for (int i = 1; i <= ans[0]; i++)
	{
		static bool output;
		if (output) putchar(' ');
		printOut(ans[i]);
		output = true;
	}
	putchar('\n');
}

int main()
{
#ifndef JUDGE
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
#endif
	run();
	return 0;
}
