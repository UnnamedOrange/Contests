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
}

const int mod = 64123;
const int maxn = 1670;
int n, k, W;
int d[maxn];

std::vector<int> G[maxn];

#define RunInstance(x) delete new x
struct cheat
{
	int nodes[maxn];

	void DFS(int node, int parent)
	{
		nodes[++nodes[0]] = node;
		for (int i = 0; i < G[node].size(); i++)
		{
			int to = G[node][i];
			if (to == parent) continue;
			DFS(to, node);
		}
	}

	cheat()
	{
		nodes[0] = 0;
		for (int i = 1; i <= n; i++)
		{
			if (G[i].size() == 1)
			{
				DFS(i, 0);
				break;
			}
		}

		int ans = 0;
		for (int i = 1; i <= n; i++)
		{
			std::priority_queue<int, std::vector<int>, std::greater<int> > pq;
			for (int j = i; j <= n; j++)
			{
				pq.push(d[nodes[j]]);
				while (pq.size() > k) pq.pop();
				if (pq.size() == k) (ans += pq.top()) %= mod;
			}
		}
		printOut(ans);
	}
};

void run()
{
	n = readIn();
	k = readIn();
	W = readIn();
	for (int i = 1; i <= n; i++)
		d[i] = readIn();

	for (int i = 1; i < n; i++)
	{
		int from = readIn();
		int to = readIn();
		G[from].push_back(to);
		G[to].push_back(from);
	}

	RunInstance(cheat);
}

int main()
{
#ifndef LOCAL
	freopen("coat.in", "r", stdin);
	freopen("coat.out", "w", stdout);
#endif
	run();
	return 0;
}