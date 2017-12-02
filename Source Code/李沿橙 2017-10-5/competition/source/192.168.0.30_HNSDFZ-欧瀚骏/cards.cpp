#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define eps 1e-8
#define N 1000 
using namespace std;
inline int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }
int sg[N + 5][N + 5], g[N + 5][N + 5], f[N + 5], n, a[N + 5];
double dp[N + 5][N + 5], ans = 0;
bool getsg(int x, int y) {
	if (x == 1) return 1;
	if (sg[x][y] != -1) return sg[x][y];
	bool flag = 1;
	if (f[x] > y) flag &= getsg(x, y + 1);
	for (int i = 1; i <= n; i++)
		if (g[x][i] != x)
			flag &= getsg(g[x][i], y + 1);
	sg[x][y] = !flag;
	return sg[x][y];
}
int main() {
	freopen("cards.in", "r", stdin);
	freopen("cards.out", "w", stdout);
	scanf("%d", &n);
	int mx = 0;
	for (int i = 1; i <= n; i++) { scanf("%d", a + i); mx = max(mx, a[i]); g[0][i] = a[i]; }
	for (int i = 1; i <= mx; i++)
		for (int j = 1; j <= n; j++)
			f[i] += (a[j] % i == 0), g[i][j] = gcd(i, a[j]);
	dp[0][0] = 1;
	for (int i = 1; i <= n; i++)
		for (int j = 0; j <= mx; j++)
			if (dp[i - 1][j] > eps) {
				dp[i][j] += dp[i - 1][j] * (f[j] - i + 1) / (n - i + 1);
				for (int k = 1; k <= n; k++)
					if (g[j][k] != j) {
						if (g[j][k] != 1)
							dp[i][g[j][k]] += dp[i - 1][j] / (n - i + 1);
						else 
							ans += (i + 1 & 1) * dp[i - 1][j] / (n - i + 1);
					}
			}
	if (n & 1)
		for (int j = 0; j <= mx; j++) ans += dp[n][j];
	printf("%.9lf ", ans);
	memset(sg, -1, sizeof(sg));
	if (getsg(0, 0)) puts("1.000000000"); else puts("0.000000000");
	return 0;
}
