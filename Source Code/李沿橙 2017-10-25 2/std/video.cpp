#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;
const int N = 211111;
const int mod = 1000000007;
int n, m;
int fact[N], inverse[N];
int powmod(int x, int y) {
	if (!y) return 1;
	int ret = powmod(x, y >> 1);
	if (y & 1) {
		return 1LL * ret * ret % mod * x % mod;
	} else {
		return 1LL * ret * ret % mod;
	}
}
int main() {
	
	scanf("%d%d", &n, &m);
	fact[0] = 1;
	inverse[0] = 1;
	for (int i = 1; i <= n; i++) {
		fact[i] = 1LL * fact[i - 1] * i % mod;
		inverse[i] = powmod(fact[i], mod - 2);
	}
	int ans = 1LL * fact[n] * inverse[n - m] % mod * inverse[m] % mod;
	printf("%d\n", ans);
	return 0;
}
