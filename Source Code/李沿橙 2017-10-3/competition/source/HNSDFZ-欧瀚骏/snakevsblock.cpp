#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#define N 200
#define L 10000
#define max(a, b) ((a) > (b) ? (a) : (b))
using namespace std;
int ans = 0;
void update(int &a, int b, int c) { if (b == -1) return ; a = max(a, b + c); }
int mx = 0, g[6][6][L + 5], a[N + 5][7], f[N + 5][7], dp[2][7][L + 5], n, m, x, y, r[6];
bool now = 0, pre = 1;
void work(int x) {
	memset(g, -1, sizeof(g));
	for (int i = 1; i <= 5; i++) 
		for (int l = 0; l <= mx; l++)
			g[i][i][l] = dp[now][i][l];
	r[5] = 5;
	for (int i = 4; i; i--) {
		if (f[x][i])
			r[i] = i;
		else 
			r[i] = r[i + 1];
	}
	for (int i = 1; i < 5; i++)
		for (int j = 1; i + j <= 5; j++) 
			if (i + j > r[j]) continue; 
			else {
				for (int l = 0; l <= mx; l++) {
					if (l - a[x][j] >= 0 && l - a[x][j] <= mx)
						update(g[j][i + j][l], g[j + 1][i + j][l - a[x][j]], max(0, -a[x][j]));
					if (l - a[x][i + j] >= 0 && l - a[x][i + j] <= mx)
						update(g[j][i + j][l], g[j][i + j - 1][l - a[x][i + j]], max(0, -a[x][i + j]));
					for (int k = j; k <= i + j; k++) update(dp[now][k][l], g[j][i + j][l], 0), ans = max(ans, dp[now][k][l]);
				}
			}
}
int main() {
	freopen("snakevsblock.in", "r", stdin);
	freopen("snakevsblock.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) 
		for (int j = 1; j <= 5; j++) {
			scanf("%d", a[i] + j);
			mx += max(0, a[i][j]);
		}
	scanf("%d", &m);
	for (int i = 1; i <= m; i++) {
		scanf("%d%d", &x, &y);
		f[x][y] = 1;
	}
	memset(dp, -1, sizeof(dp));
	for (int i = 1; i < 6; i++)
		if (i == 3) dp[now][i][4] = 0;
	work(1);
	for (int i = 2; i <= n; i++) {
		now ^= 1, pre ^= 1;
		for (int j = 1; j <= 5; j++)
			for (int k = 0; k <= mx; k++)
				if (k - a[i][j] >= 0 && dp[pre][j][k - a[i][j]] != -1) 
					dp[now][j][k] = dp[pre][j][k - a[i][j]] + max(0, -a[i][j]);
				else 
					dp[now][j][k] = -1;
		work(i);
	}
	printf("%d\n", ans);
	return 0;
}
