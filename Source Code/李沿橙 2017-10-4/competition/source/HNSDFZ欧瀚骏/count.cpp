#include <cstdio>
#include <cassert>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 100000000
#define DICSIZE 26
#define MOD 998244353
using namespace std;
typedef long long LL;
void add(int &a, LL b) { a += b; if (a >= MOD) a -= MOD; }
inline int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }
LL fpow(int a, int n) {
	LL ans = 1, tmp = a;
	while (n) {
		if (n & 1) ans = ans * tmp % MOD;
		tmp = tmp * tmp % MOD, n >>= 1;
	}
	return ans;
}
int cnt = 0, ans = 0;
int main() {
	freopen("count.in", "r", stdin);
	freopen("count.out", "w", stdout);
	int l, r, k;
	scanf("%d%d%d", &l, &r, &k);
	for (int i = max(l, 2); i <= r; i++) add(ans, fpow(i, k));
	if (l <= 1) add(ans, fpow(2, k));
	printf("%d\n", ans);
	return 0;
}
