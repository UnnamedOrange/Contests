#include <cstdio>
#include <queue>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 1500000
#define inf 1e9
#define L(p) ((p) << 1)
#define R(p) ((p) << 1 | 1)
#define MOD 1000000007
using namespace std;
typedef long long LL;
LL fpow(int a, int n) {
	LL tmp = a, ans = 1;
	while (n) {
		if (n & 1) ans = ans * tmp % MOD;
		tmp = tmp * tmp % MOD, n >>= 1; 
	}
	return ans;
}
struct Question {
	int a, b, c, op;
} ques[N + 5];
void addto(int &a, int b) { a += b; if (a >= MOD) a -= MOD; }
int f[N + 5][11], pow[11], ad[N + 5], rev[N + 5], g[11], tmp[11], mx = 0, fac[N + 5], inv[N + 5], a[N + 5];
LL c(int n, int m) { return fac[n] * 1ll * inv[m] % MOD * inv[n - m] % MOD; }
void update(int p, int l, int r) {
	int mid = l + r >> 1;
	for (int i = 1; i <= min(r - l + 1, mx); i++) {
		f[p][i] = 0;
		for (int j = 0; j <= mid - l + 1 && j <= i; j++)
			if (i - j <= r - mid) 
				addto(f[p][i], f[L(p)][j] * 1ll * f[R(p)][i - j] % MOD);
	}
}
void add(int p, int l, int r, int x) {
	pow[0] = 1;
	if (x < 0) x += MOD;
	for (int i = 1; i <= min(r - l + 1, mx); i++)
		pow[i] = pow[i - 1] * 1ll * x % MOD;
//	printf("l = %d r = %d add %d ->\n", l, r, x);
//	for (int i = 1; i <= mx; i++) printf("%d ", f[p][i]); puts("");
	for (int i = min(r - l + 1, mx); i; i--)
		for (int j = 1; j <= i; j++)
			addto(f[p][i], pow[j] * 1ll * f[p][i - j] % MOD * c(r - l + 1 - i + j, j) % MOD);
//	for (int i = 1; i <= mx; i++) printf("%d ", f[p][i]); puts("");
	addto(ad[p], x);
}
void reverse(int p, int l, int r) {
	for (int i = 1; i <= min(r - l + 1, mx); i += 2) f[p][i] = (MOD - f[p][i]) % MOD;
	ad[p] = (MOD - ad[p]) % MOD;
	rev[p] ^= 1;
}
void pushdown(int p, int l, int r) {
	int mid = l + r >> 1;
	if (rev[p]) reverse(L(p), l, mid), reverse(R(p), mid + 1, r), rev[p] = 0; 
	if (ad[p]) add(L(p), l, mid, ad[p]), add(R(p), mid + 1, r, ad[p]), ad[p] = 0; 
}
void build(int l, int r, int p) {
	ad[p] = rev[p] = 0, f[p][0] = 1;
	if (l == r) { f[p][1] = a[l] < 0 ? a[l] + MOD : a[l]; return ; }
	int mid = l + r >> 1;
	build(l, mid, L(p));
	build(mid + 1, r, R(p));
	update(p, l, r);
}
void insert(int p, int l, int r, int k) {
	memset(tmp, 0, sizeof(tmp));
//	printf("l = %d r = %d\n", l, r);
//	for (int i = 1; i <= k; i++) printf("%d ", f[p][i]); puts("");
	for (int i = 1; i <= min(r - l + 1, k); i++)
		for (int j = 0; i + j <= k; j++)
			addto(tmp[i + j], g[j] * 1ll * f[p][i] % MOD);
	for (int i = 1; i <= k; i++) addto(g[i], tmp[i]);
}
void query(int ll, int rr, int k, int l, int r, int p) {
	if (ll <= l && r <= rr) { insert(p, l, r, k); return ; }
	int mid = l + r >> 1;
	pushdown(p, l, r);
	if (ll <= mid) query(ll, rr, k, l, mid, L(p));
	if (rr >  mid) query(ll, rr, k, mid + 1, r, R(p));
}
void Q_add(int ll, int rr, int x, int l, int r, int p) {
	if (ll <= l && r <= rr) { add(p, l, r, x); return ; }
	int mid = l + r >> 1;
	pushdown(p, l, r);
	if (ll <= mid) Q_add(ll, rr, x, l, mid, L(p));
	if (rr >  mid) Q_add(ll, rr, x, mid + 1, r, R(p));
	update(p, l, r);
}
void Q_rev(int ll, int rr, int l, int r, int p) {
	if (ll <= l && r <= rr) { reverse(p, l, r); return ; }
	int mid = l + r >> 1;
	pushdown(p, l, r);
	if (ll <= mid) Q_rev(ll, rr, l, mid, L(p));
	if (rr >  mid) Q_rev(ll, rr, mid + 1, r, R(p));
	update(p, l, r);
}
int main() {
	freopen("game.in", "r", stdin);
	freopen("game.out", "w", stdout);
	fac[0] = 1;
	for (int i = 1; i <= N; i++) fac[i] = fac[i - 1] * 1ll * i % MOD;
	inv[N] = fpow(fac[N], MOD - 2);
	for (int i = N; i; i--) inv[i - 1] = inv[i] * 1ll * i % MOD;
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	for (int i = 1; i <= m; i++) {
		scanf("%d", &ques[i].op);
		if (ques[i].op == 1) scanf("%d%d%d", &ques[i].a, &ques[i].b, &ques[i].c);
		if (ques[i].op == 2) scanf("%d%d", &ques[i].a, &ques[i].b);
		if (ques[i].op == 3) { scanf("%d%d%d", &ques[i].a, &ques[i].b, &ques[i].c); mx = max(mx, ques[i].c); }
	}
	build(1, n, 1);
	for (int i = 1; i <= m; i++) {
		if (ques[i].op == 1) Q_add(ques[i].a, ques[i].b, ques[i].c, 1, n, 1);
		if (ques[i].op == 2) Q_rev(ques[i].a, ques[i].b, 1, n, 1);
		if (ques[i].op == 3) { memset(g, 0, sizeof(g)); g[0] = 1, query(ques[i].a, ques[i].b, ques[i].c, 1, n, 1); printf("%d\n", g[ques[i].c]); }
	}
	return 0;
}
