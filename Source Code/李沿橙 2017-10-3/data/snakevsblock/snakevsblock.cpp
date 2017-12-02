#include <bits/stdc++.h>
using namespace std;
int n, a[205][5], m, x, y, f[205][10005][5] = {{{0}}};
int g[10005][5][5] = {{{0}}}, maxi, ans = 0;
bool flag[205][4] = {{false}};
int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		for (int j = 0; j < 5; j++)
			scanf("%d", &a[i][j]);
	scanf("%d", &m);
	for (int i = 1; i <= m; i++)
	{
		scanf("%d%d", &x, &y);
		flag[x][y - 1] = true;
	}
	memset(f, -0x7f7f7f, sizeof f);
	f[0][4][2] = 0;
	maxi = n * 50;
	for (int i = 1; i <= n; i++)
	{
		memset(g, -0x7f7f7f, sizeof g);
		for (int j = 0; j <= maxi; j++)
			for (int k = 0; k < 5; k++)
				if (j - a[i][k] >= 0 && j - a[i][k] <= maxi)
					f[i][j][k] = g[j][k][k] = f[i - 1][j - a[i][k]][k] + max(-a[i][k], 0);
		for (int l = 1; l <= 4; l++)
			for (int j = 0, k = j + l; k < 5; j++, k++)
				for (int v = 0, val; v <= maxi; v++)
				{
					if (!flag[i][j] && (val = v - a[i][j]) >= 0 && val <= maxi) g[v][j][k] = g[val][j + 1][k] + max(-a[i][j], 0);
					if (!flag[i][k - 1] && (val = v - a[i][k]) >= 0 && val <= maxi) g[v][j][k] = max(g[v][j][k], g[val][j][k - 1] + max(-a[i][k], 0));
					for (int to = j; to <= k; to++) f[i][v][to] = max(f[i][v][to], g[v][j][k]);
				}
	}
	for (int l = 0; l <= n; l++)
		for (int i = 0; i <= maxi; i++)
			for (int j = 0; j < 5; j++)
				ans = max(ans, f[l][i][j]);
	printf("%d\n", ans);
	return 0;
}
