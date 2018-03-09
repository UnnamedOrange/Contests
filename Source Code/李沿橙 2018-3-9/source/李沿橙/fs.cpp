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
typedef LL INT_PUT;
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
	char buffer[40];
	int length = 0;
	if (x < 0)
		putchar('-');
	else
		x = -x;
	do
	{
		buffer[length++] = -(x % 10) + '0';
	} while (x /= 10);
	do
	{
		putchar(buffer[--length]);
	} while (length);
	putchar('\n');
}

const int maxn = 35;
int k, q;

#define RunInstance(x) delete new x
struct brute
{
	static const int maxn = (1 << 15) + 5;
	int parent[maxn];
	int degree[maxn];
	int n;
	int prufer[maxn];

	brute() : degree()
	{
		n = (1 << k) - 1;
		for (int i = 2; i <= n; i++)
		{
			parent[i] = i >> 1;
			degree[parent[i]]++;
		}
		std::priority_queue<int, std::vector<int>, std::greater<int> > pq;
		for (int i = 1 << (k - 1); i <= n; i++)
			if (parent[i]) pq.push(i);
		for (int i = 1, to = n - 2; i <= to; i++)
		{
			int node = pq.top();
			pq.pop();
			prufer[i] = parent[node];

			degree[parent[node]]--;
			if (!degree[parent[node]])
				pq.push(parent[node]);
		}

		while (q--)
		{
			int a = readIn();
			int d = readIn();
			int m = readIn();
			LL ans = 0;
			for (int i = 0; i < m; i++)
				ans += prufer[a + i * d];
			printOut(ans);
		}
	}
};
struct work
{
	int n;
	int Get(int idx)
	{
		int l = 1, r = n;
		int cnt = 1;
		while (r - l > 1)
		{
			if (idx == r) return cnt >> 1;
			r--;
			int mid = l + ((r - l) >> 1);
			if (idx <= mid)
			{
				r = mid;
				cnt <<= 1;
			}
			else
			{
				l = mid + 1;
				cnt <<= 1;
				cnt++;
			}
		}
		return cnt >> 1;
	}
	void DFS(int node)
	{
		if ((node << 1) < (1 << (k - 1))) DFS(node << 1);
		cout << node << ' ';
		if (((node << 1) + 1) < (1 << (k - 1))) DFS((node << 1) + 1);
		cout << node << ' ';
	}
	work()
	{
		n = (1 << k) - 1;
		while (q--)
		{
			int a = readIn();
			int d = readIn();
			int m = readIn();
			LL ans = 0;
			for (int i = 0; i < m; i++)
				ans += Get(a + i * d);
			printOut(ans);
		}
	}
};

void run()
{
	k = readIn();
	q = readIn();

	if (k <= 15)
		RunInstance(brute);
	else
		RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("fs.in", "r", stdin);
	freopen("fs.out", "w", stdout);
#endif
	run();
	return 0;
}