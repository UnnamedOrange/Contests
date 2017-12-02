#include <cstdio>
#include <cassert>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 1000000
#define DICSIZE 26
#define MOD 998244353
using namespace std;
typedef long long LL;
void add(int &a, int b) { a += b, a %= MOD; }
inline int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }
LL fpow(int a, int n) {
	LL ans = 1, tmp = a;
	while (n) {
		if (n & 1) ans = ans * tmp % MOD;
		tmp = tmp * tmp % MOD, n >>= 1;
	}
	return ans;
}
int l[N + 5], r[N + 5], MX = 0, a[N + 5], b[N + 5], n, m;
int main() {
	freopen("blocks.in", "r", stdin);
	freopen("blocks.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) { scanf("%d", b + i); MX = max(MX, b[i]); }
	while (m--) {
		int k;
		scanf("%d", &k);
		LL mi = 0, mx = -MX * 1ll * n - 1;
		int ll = 1, rr = 0;
		l[1] = 0;
		for (int i = 1; i <= n; i++) a[i] = a[i - 1] + b[i] - k;
		for (int i = 1; i <= n; i++) if (mi > a[i]) l[++ll] = i, mi = a[i];
		for (int i = n; i; i--) if (mx < a[i]) r[++rr] = i, mx = a[i];
		for (int i = 1; i <= (rr >> 1); i++) swap(r[i], r[rr - i + 1]);
		int now = 0, ans = 0;
		for (int i = 1; i <= ll; i++) {
			while (now + 1 <= rr && a[r[now + 1]] >= a[l[i]]) now++;
			if (a[r[now]] >= a[l[i]] && r[now] > l[i]) 
				ans = max(ans, r[now] - l[i]);
		}
		printf("%d ", ans);
	}
	puts("");
	return 0;
}
