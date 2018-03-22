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
	INT_PUT a = 0; bool positive = true;
	char ch = getchar();
	while (!(ch == '-' || std::isdigit(ch))) ch = getchar();
	if (ch == '-') { positive = false; ch = getchar(); }
	while (std::isdigit(ch)) { a = a * 10 - (ch - '0'); ch = getchar(); }
	return positive ? -a : a;
}
void printOut(INT_PUT x)
{
	char buffer[20]; int length = 0;
	if (x < 0) putchar('-'); else x = -x;
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
}

LL INF;
const int maxn = 405;
int n;
int v[maxn];
int w[maxn];

LL f[maxn][maxn];
LL g[maxn][maxn][2];

LL ans[maxn];

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
		v[i] = readIn();
	for (int i = 1; i <= n; i++)
		w[i] = readIn();
	memset(&INF, -0x3f, sizeof(INF));

	memset(f, -0x3f, sizeof(f));
	memset(g, -0x3f, sizeof(g));
	for (int i = 1; i <= n; i++)
	{
		g[i][i][0] = g[i][i][1] = 0;
		f[i][i] = v[1];
	}
	for (int length = 2; length <= n; length++)
	{
		for (int l = 1; l + length - 1 <= n; l++)
		{
			int r = l + length - 1;
			for (int i = l; i <= r; i++)
			{
				if (w[i] + 1 == w[r])
					g[l][r][true] = g[l][i][true] != INF ? std::max(g[l][r][true], g[l][i][true] + (r - i == 1 ? 0 : f[i + 1][r - 1])) : g[l][r][true];
				if (w[i] - 1 == w[r])
					g[l][r][false] = g[l][i][false] != INF ? std::max(g[l][r][false], g[l][i][false] + (r - i == 1 ? 0 : f[i + 1][r - 1])) : g[l][r][false];
			}
			for (int i = l; i < r; i++)
				f[l][r] = std::max(f[l][r], f[l][i] + f[i + 1][r]);
			for (int i = l; i <= r; i++)
				if (g[l][i][true] > INF + 100 && g[i][r][false] > INF + 100)
					f[l][r] = std::max(f[l][r], g[l][i][true] + g[i][r][false] + v[w[i] - w[r] + w[i] - w[l] + 1]);
		}
	}
	for (int i = 1; i <= n; i++)
	{
		ans[i] = ans[i - 1];
		for (int j = 0; j < i; j++)
			ans[i] = std::max(ans[i], ans[j] + f[j + 1][i]);
	}
	printOut(ans[n]);
}

int main()
{
#ifndef LOCAL
	freopen("haha.in", "r", stdin);
	freopen("haha.out", "w", stdout);
#endif
	run();
	return 0;
}