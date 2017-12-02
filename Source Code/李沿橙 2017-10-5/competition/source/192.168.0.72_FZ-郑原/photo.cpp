#include <cstdio>
#include <algorithm>
#include <iostream>

using namespace std;

typedef long long ll;

const int Z = 1000000 + 5;
const int N = 2000 + 5;
const int mod = 1e9 + 7;

int dp[N][N], n, m, k, ans, rec[N];
int fac[Z] = {1}, inv[Z] = {1};

int pow(int x, int a) {
	int ret = 1;
	while (a) {
		if (a & 1) ret = (ll) ret * x % mod;
		a >>= 1;
		x = (ll) x * x % mod; 
	}
	return ret; 
}

int inc(int a, int b) {
	return a + b - (a + b >= mod ? mod : 0);
}	

int co(int x, int y) {
	if (x < y) return 0;
	return (ll) fac[x] * inv[x - y] % mod * inv[y] % mod;
}

int main() {
	freopen("photo.in", "r", stdin);
	freopen("photo.out", "w", stdout);

	scanf("%d%d%d", &n, &m, &k);
	
	for (int i = 1; i <= k; i ++) fac[i] = (ll) fac[i - 1] * i % mod;
	inv[k] = pow(fac[k], mod - 2);
	for (int i = k - 1; i; i --) inv[i] = (ll) inv[i + 1] * (i + 1) % mod; 
	
	for (int kd = 1; kd <= k && kd <= n; kd ++) {
		dp[0][0] = 1;
		for (int i = 1; i <= n; i ++) 
			for (int j = 1; j <= kd; j ++)
				dp[i][j] = inc((ll) dp[i - 1][j - 1] * (kd - j + 1) % mod, (ll) dp[i - 1][j] * j % mod);
		rec[kd] = dp[n][kd];
		//printf("%d %d\n", kd, rec[kd]);
	}
	
	for (int kd = 0; kd <= k && kd <= n; kd ++) {
		if (m > 2 && kd == 0) continue ;
		dp[0][0] = 1;
		for (int i = 1; i <= n; i ++) 
			for (int j = 1; j <= kd; j ++) 
				dp[i][j] = inc((ll) dp[i - 1][j - 1] * (kd - j + 1) % mod, (ll) dp[i - 1][j] * j % mod);
		int tim = 0; 
		for (int i = 1; i <= kd; i ++) tim = inc(tim, dp[n][i]);
		int tht = 0;
		for (int i = 0; (i >> 1) <= n - kd && i <= k - kd; i += 2) 
			tht = inc(tht, (ll) pow(rec[kd + (i >> 1)], 2) * co(i, i >> 1) % mod * co(k - kd, i) % mod);
		int ths = (ll) tht * pow(tim, m - 2) % mod * co(k, kd) % mod; 
		ans = inc(ans, ths);
	}
	 
	 printf("%d\n", ans);
	 
	return 0;
}
