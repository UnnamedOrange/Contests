#include <iostream>
#include <cstdio>
#include <cstring>

const int maxn = 210;

using namespace std;

int n, m;
int a[maxn][10];
bool p[maxn][10] = { false };
int vis[maxn][10] = { 0 };

int dfs(int x, int y, int l);

int main()
{
	freopen("snakevsblock.in", "r", stdin);
	freopen("snakevsblock.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= 5; j++)
			scanf("%d", &a[i][j]);
	scanf("%d", &m);
	for (int i = 0; i < m; i++)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		p[x][y] = true;
	}
	printf("%d", dfs(1, 3, 4));
	return 0;
}

int dfs(int x, int y, int l)
{
	if (vis[x][y] >= 3)
		return 0;
	int ans = 0;
	if (a[x][y] > 0)
	{
		int t = a[x][y];
		a[x][y] = 0;
		vis[x][y]++;
		if (x + 1 <= n)
			ans = max(ans, dfs(x + 1, y, l + t));
		if (y - 1 > 0 && !p[x][y - 1])
			ans = max(ans, dfs(x, y - 1, l + t));
		if (y + 1 <= 5 && !p[x][y])
			ans = max(ans, dfs(x, y + 1, l + t));
		vis[x][y]--;
		a[x][y] = t;
	}
	if (a[x][y] == 0)
	{
		vis[x][y]++;
		if (x + 1 <= n)
			ans = max(ans, dfs(x + 1, y, l));
		if (y - 1 > 0 && !p[x][y - 1])
			ans = max(ans, dfs(x, y - 1, l));
		if (y + 1 <= 5 && !p[x][y])
			ans = max(ans, dfs(x, y + 1, l));
		vis[x][y]--;
	}
	if (a[x][y] < 0 && l + a[x][y] >= 0)
	{
		int t = a[x][y];
		a[x][y] = 0;
		vis[x][y]++;
		if (x + 1 <= n)
			ans = max(ans, dfs(x + 1, y, l + t));
		if (y - 1 > 0 && !p[x][y - 1])
			ans = max(ans, dfs(x, y - 1, l + t));
		if (y + 1 <= 5 && !p[x][y])
			ans = max(ans, dfs(x, y + 1, l + t));
		vis[x][y]--;
		a[x][y] = t;
		ans -= t;
	}
	return ans;
}

