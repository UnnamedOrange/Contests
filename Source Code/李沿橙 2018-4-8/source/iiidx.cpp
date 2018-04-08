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
	putchar(' ');
}

const int maxn = int(5e5) + 5;
int n;
double k;
int d[maxn];
int pre[maxn];

#define RunInstance(x) delete new x
struct brute
{
	static const int maxN = 15;
	int idx[maxN];
	int ans[maxN];

	brute()
	{
		for (int i = 1; i <= n; i++)
			idx[i] = i;
		do
		{
			bool bOk = true;
			for (int i = 1; i <= n; i++)
			{
				if (pre[i] && d[idx[i]] < d[idx[pre[i]]])
				{
					bOk = false;
					break;
				}
			}
			if (bOk) memcpy(ans, idx, sizeof(ans));
		} while (std::next_permutation(idx + 1, idx + 1 + n));
		for (int i = 1; i <= n; i++)
			printOut(d[ans[i]]);
	}
};
bool comp(const int& a, const int& b)
{
	if (pre[a] != pre[b]) return pre[a] < pre[b];
	return a > b;
}
struct cheat
{
	int idx[maxn];

	std::vector<int> G[maxn];
	int stamp;
	void DFS(int node)
	{
		idx[node] = stamp;
		stamp++;
		for (int i = 0; i < G[node].size(); i++)
			DFS(G[node][i]);
	}

	cheat()
	{
		for (int i = 1; i <= n; i++)
			G[pre[i]].push_back(i);
		for (int i = 0; i <= n; i++)
			std::reverse(G[i].begin(), G[i].end());
		stamp = 0;
		DFS(0);
		for (int i = 1; i <= n; i++)
			printOut(d[idx[i]]);
	}
};

void run()
{
	n = readIn();
	cin >> k;
	for (int i = 1; i <= n; i++)
		d[i] = readIn();
	std::sort(d + 1, d + 1 + n);
	for (int i = 1; i <= n; i++)
		pre[i] = (double)i / k;

	if (n <= 10)
		RunInstance(brute);
	else
		RunInstance(cheat);
}

int main()
{
#ifndef LOCAL
	freopen("iiidx.in", "r", stdin);
	freopen("iiidx.out", "w", stdout);
#endif
	run();
	return 0;
}