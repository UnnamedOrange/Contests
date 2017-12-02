#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define K 1000000
#define N 400
using namespace std;
typedef long long LL;
int f[K + 5], s[N + 5][N + 5];
int main() {
	freopen("rally.in", "r", stdin);
	freopen("rally.out", "w", stdout);
	int n, m, k;
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= n; i++) 
		for (int j = 1; j <= m; j++) {
			scanf("%d", s[i] + j);
			s[i][j] += s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
			if (s[i][j] > 0) s[i][j] %= k;
			if (s[i][j] < 0) s[i][j] += k;
		}
	LL ans = 0;
	f[0] = 1;
	for (int l = 1; l <= m; l++)
		for (int r = l; r <= m; r++) {
			for (int i = 1; i <= n; i++) {
				int sum = s[i][r] - s[i][l - 1];
				if (sum < 0) sum += k;
				ans += f[sum];
				f[sum]++;
			}
			for (int i = 1; i <= n; i++) {
				int sum = s[i][r] - s[i][l - 1];
				if (sum < 0) sum += k;
				f[sum]--;
			}
		}
	printf("%lld\n", ans);
	return 0;
}
