#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define eps 1e-8
#define N 1000000
#define MOD 1000000007
using namespace std;
typedef long long LL;
inline int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }
void add(int &a, LL b) { a += b; if (a >= MOD) a -= MOD; if (a < 0) a += MOD; }
inline LL fpow(LL a, LL n) {
	LL ans = 1, tmp = a;
	while (n) {
		if (n & 1) ans = ans * tmp % MOD;
		tmp = tmp * tmp % MOD, n >>= 1;
	}
	return ans;
}
int fac[N + 5], inv[N + 5], dp[N + 5], n, m, k;
LL c(int n, int m) { if (n < 0) return 0; return m > n ? 0 : fac[n] * 1ll * inv[m] % MOD * inv[n - m] % MOD; }
int main() {
//	freopen("photo.in", "r", stdin);
//	freopen("photo.out", "w", stdout);
	fac[0] = 1;
	for (int i = 1; i <= N; i++) fac[i] = fac[i - 1] * 1ll * i % MOD;
	inv[N] = fpow(fac[N], MOD - 2);
	for (int i = N; i; i--) inv[i - 1] = inv[i] * 1ll * i % MOD;
	scanf("%d%d%d", &n, &m, &k);
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		dp[i] = fpow(i, n);
		for (int j = 1; j < i; j++)
			add(dp[i], -dp[j] * c(i, j) % MOD);
	}
	if (m == 2) {
		for (int i = 1; i <= n; i++) 
			add(ans, dp[i] * 1ll * dp[i] % MOD * c(k, i) % MOD * c(k, i) % MOD);
		printf("%d\n", ans);
		return 0;
	}
	for (int i = 1; i <= n; i++) {
		int tmp = fpow(i, n * (m - 2));
		for (int j = i; j <= n; j++) 
			add(ans, dp[j] * 1ll * dp[j] % MOD * c(k - i, j - i) % MOD * c(k - j, j - i) % MOD * c(k, i) % MOD * tmp % MOD);
	}
	printf("%d\n", ans);
	return 0;
}
