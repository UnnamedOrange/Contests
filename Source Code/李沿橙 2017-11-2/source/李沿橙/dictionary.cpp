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
INT readIn()
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
void printOut(INT x)
{
	char buffer[20];
	bool minus = x < 0;
	INT length = 0;
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

const INT maxn = 100005;
INT n, m;
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
INT in[maxn];

INT ans[maxn];

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= m; i++)
	{
		INT a = readIn();
		INT b = readIn();
		in[b]++;
		addEdge(a, b);
	}

	std::priority_queue<INT, std::vector<INT>, std::greater<INT> > pq;
	for (int i = 1; i <= n; i++)
		if (!in[i])
			pq.push(i);

	while (!pq.empty())
	{
		INT from = pq.top();
		pq.pop();
		ans[++ans[0]] = from;
		for (int i = head[from]; i; i = edges[i].next)
		{
			INT to = edges[i].to;
			in[to]--;
			if (!in[to]) pq.push(to);
		}
	}
	if (ans[0] != n) printOut(-1);
	else
	{
		for (int i = 1; i <= ans[0]; i++)
		{
			static bool printed;
			if (printed) putchar(' ');
			printOut(ans[i]);
			printed = true;
		}
	}
	putchar('\n');
}

int main()
{
#ifndef JUDGE
	freopen("dictionary.in", "r", stdin);
	freopen("dictionary.out", "w", stdout);
#endif
	run();
	return 0;
}
