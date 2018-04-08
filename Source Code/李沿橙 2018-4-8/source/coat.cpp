#pragma GCC optimize(3)
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
struct work
{
	int idx[maxn];
	int val;
	struct Poly
	{
		int size;
		int c[maxn];
		int& operator[](int x) { return c[x]; }
		const int& operator[](int x) const { return c[x]; }
		void clear() { size = 1; c[0] = 0; }
		void operator*=(const Poly& b)
		{
			Poly& a = *this;
			static int temp[maxn];
			int to = std::min(k + 1, a.size + b.size - 1);
			for (register int i = 0; i < to; i++)
			{
				temp[i] = 0;
				LL sum = 0;
				for (register int j = std::max(0, i - b.size + 1), t = std::min(a.size - 1, i); j <= t; j++)
					sum += (LL)a[j] * b[i - j];
				temp[i] = (temp[i] + sum) % mod;
			}
			memcpy(c, temp, sizeof(int) * to);
			size = to;
			while (size && !c[size - 1]) size--;
		}
		void add(const Poly& b, bool mov)
		{
			Poly& a = *this;
			if (a.size < b.size + mov)
			{
				for (int i = a.size; i < b.size + mov; i++)
					a[i] = 0;
				a.size = b.size + mov;
			}
			int to = std::min(a.size, b.size + mov);
			int temp;
			if (!mov) a[0] = (temp = a[0] + b[0]) >= mod ? temp - mod : temp;
			for (register int i = 1; i < to; i++)
				a[i] = (temp = a[i] + b[i - mov]) >= mod ? temp - mod : temp;
		}
		void operator=(const Poly& b)
		{
			size = b.size;
			memcpy(c, b.c, sizeof(int) * size);
		}
		void times()
		{
			for (int i = size; i; i--)
				c[i] = c[i - 1];
			c[0] = 0;
			size++;
		}
	};

	int stamp;
	int dfn[maxn];
	int seq[maxn];
	int end[maxn];
	void DFS(int node, int parent)
	{
		stamp++;
		dfn[node] = stamp;
		seq[stamp] = node;
		for (int i = 0; i < G[node].size(); i++)
		{
			int to = G[node][i];
			if (to == parent) continue;
			DFS(to, node);
		}
		end[node] = stamp;
	}

	int ans;
	Poly polys[maxn];
	Poly temp;
	work() : ans()
	{
		for (int i = 1; i <= n; i++)
		{
			val = d[i];
			stamp = 0;
			DFS(i, 0);

			polys[n + 1].clear();
			polys[n + 1][0] = 1;
			for (int j = n; j; j--)
			{
				int node = seq[j];
				temp.clear();
				temp[0] = 1;

				temp *= polys[j + 1];
				polys[j].clear();
				polys[j][0] = 1;
				polys[j] *= polys[end[node] + 1];
				polys[j].add(temp, j == 1 || d[node] > val || (d[node] == val && node > i));
			}
			if (polys[1].size > k)
				ans = (ans + LL(val) * polys[1][k]) % mod;
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

	RunInstance(work);
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