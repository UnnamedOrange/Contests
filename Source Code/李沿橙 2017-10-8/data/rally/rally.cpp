/* Never Say Die. */
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

#define N 405

int n, m, K;
int a[N][N], b[N], cnt[1000005];
LL ans = 0;

int main() {
//	freopen("rally.in", "r", stdin);
//	freopen("rally.out", "w", stdout);
	scanf("%d%d%d", &n, &m, &K);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			scanf("%d", a[i] + j);
			(a[i][j] += a[i - 1][j] + a[i][j - 1] + K - a[i - 1][j - 1]) %= K;
		}
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j <= n; j++) {
			cnt[0] = 1;
			for (int k = 1; k <= m; k++) ans += cnt[(b[k] = a[j][k] + K - a[i][k]) %= K]++;
			for (int k = 1; k <= m; k++) cnt[b[k]] = 0;
		}
	}
	printf("%lld\n", ans);
	return 0;
}

