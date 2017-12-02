#include <cstdio>
#include <algorithm>
#include <iostream>

using namespace std;

typedef long long ll; 

const int N = 50000 + 5;
const int mod = 1e9 + 7; 
const int i2 = 5e8 + 4;

ll S1[N << 2], S2[N << 2];
ll ta[N << 2], tr[N << 2]; 
ll A[N];
ll dp[N][12];
int n, m; 

void upd(int u) {
	S1[u] = S1[u << 1] + S1[u << 1 | 1];
	S1[u] %= mod;
	S2[u] = S2[u << 1] + S2[u << 1 | 1];
	S2[u] %= mod;  
}

void push(int u, int l, int r) {
	int mid = (l + r) >> 1;
	if (ta[u]) {
		ll add = ta[u];
		S2[u << 1] = S2[u << 1] + (2 * S1[u << 1] % mod * add % mod); S2[u << 1] %= mod;
		S2[u << 1] = S2[u << 1] + ((ll) add * add % mod * (mid - l + 1) % mod);
		S2[u << 1] %= mod;  
		S1[u << 1] += (ll) add * (mid - l + 1) % mod;
		S1[u << 1] %= mod; while (S1[u << 1] < 0) S1[u << 1] += mod;
		
		S2[u << 1 | 1] = S2[u << 1 | 1] + (2 * S1[u << 1 | 1] % mod * add % mod); S2[u << 1 | 1] %= mod;
		S2[u << 1 | 1] = S2[u << 1 | 1] + ((ll) add * add % mod * (r - mid) % mod);
		S2[u << 1 | 1] %= mod;  
		S1[u << 1 | 1] += (ll) add * (r - mid) % mod;
		S1[u << 1 | 1] %= mod; while (S1[u << 1 | 1] < 0) S1[u << 1 | 1] += mod;
		
		ta[u] = 0; 
		ta[u << 1] += add; ta[u << 1 | 1] += add;
		ta[u << 1] %= mod; ta[u << 1 | 1] %= mod;
	}
	if (tr[u]) {
		S1[u << 1] = -S1[u << 1]; S1[u << 1 | 1] = -S1[u << 1 | 1];
		tr[u] = 0;
		tr[u << 1] ^= 1; tr[u << 1 | 1] ^= 1; 
	}
}

void build(int u, int l, int r) {
	if (l == r) {
		S1[u] = A[l]; S2[u] = A[l] * A[l] % mod; 
		while (S1[u] < 0) S1[u] += mod;
		return ;
	}
	int mid = (l + r) >> 1;
	build(u << 1, l, mid); build(u << 1 | 1, mid + 1, r);
	upd(u);
}

void plu(int u, int l, int r, int ql, int qr, int add) {
	if (l != r) push(u, l, r);
	if (ql <= l && r <= qr) {
		S2[u] = S2[u] + (2 * S1[u] % mod * add % mod); S2[u] %= mod;
		S2[u] = S2[u] + ((ll) add * add % mod * (r - l + 1) % mod);
		S2[u] %= mod;  
		S1[u] += (ll) add * (r - l + 1) % mod;
		S1[u] %= mod; while (S1[u] < 0) S1[u] += mod;
		ta[u] += add; ta[u] %= mod; 
		return ;
	} else if (l > qr || r < ql) return ;
	//push(u, l, r);
	int mid = (l + r) >> 1;
	plu(u << 1, l, mid, ql, qr, add);
	plu(u << 1 | 1, mid + 1, r, ql, qr, add);
	upd(u);
}

void rev(int u, int l, int r, int ql, int qr) {
	if (l != r) push(u, l, r);
	if (ql <= l && r <= qr) {
		S1[u] = -S1[u]; S1[u] += mod;
		tr[u] ^= 1;
		return ;
	} else if (l > qr || r < ql) return ;
	int mid = (l + r) >> 1;
	//push(u, l, r);
	rev(u << 1, l, mid, ql, qr);
	rev(u << 1 | 1, mid + 1, r, ql ,qr);
	upd(u);
}

ll qry1(int u, int l, int r, int ql, int qr) {
	if (ql <= l && r <= qr) return S1[u];
	else if (l > qr || r < ql) return 0;
	push(u, l, r);
	int mid = (l + r) >> 1;
	ll x1 = qry1(u << 1, l, mid, ql, qr);
	ll x2 = qry1(u << 1 | 1, mid + 1, r, ql, qr);
	return (x1 + x2) % mod;
}

ll qry2(int u, int l, int r, int ql, int qr) {
	if (ql <= l && r <= qr) return S2[u];
	else if (l > qr || r < ql) return 0;
	push(u, l, r);
	int mid = (l + r) >> 1;
	ll x1 = qry2(u << 1, l, mid, ql, qr);
	ll x2 = qry2(u << 1 | 1, mid + 1, r, ql, qr);
	return (x1 + x2) % mod;
}

int main() {
	freopen("game.in", "r", stdin);
	freopen("game.out", "w", stdout);

	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i ++) {
		scanf("%lld", &A[i]);
		A[i] %= mod; while (A[i] < 0) A[i] += mod;
	}
	if (n * m <= 5000000) {
		for (int i = 0; i <= n; i ++) dp[i][0] = 1;
		while (m --) {
			int tp; scanf("%d", &tp);
			if (tp == 1) {
				int l, r, add; scanf("%d%d%d", &l, &r, &add);
				add %= mod; if (add < 0) add += mod;
				for (int i = l; i <= r; i ++) 
					A[i] = (A[i] + add) % mod;
			} else if (tp == 2) {
				int l, r; scanf("%d%d", &l, &r);
				for (int i = l; i <= r; i ++) 
					A[i] = mod - A[i];
			} else {
				int l, r, k; scanf("%d%d%d", &l, &r, &k);
				for (int i = 1; i <= k; i ++) dp[l - 1][i] = 0;
				for (int i = l; i <= r; i ++) 
					for (int j = 1; j <= k; j ++) 
						dp[i][j] = (dp[i - 1][j] + (dp[i - 1][j - 1] * A[i] % mod)) % mod;
				printf("%lld\n", dp[r][k]);
			}
		}
		return 0;
	}
	build(1, 1, n);
	while (m --) {
		int tp; scanf("%d", &tp);
		if (tp == 1) {
			int l, r, add; scanf("%d%d%d", &l ,&r, &add);
			plu(1, 1, n, l, r, add);
		} else if (tp == 2) {
			int l, r; scanf("%d%d", &l, &r);
			rev(1, 1, n, l, r);
		} else {
			int l, r, k; scanf("%d%d%d", &l, &r, &k);
			ll r1 = qry1(1, 1, n, l, r);
			if (k == 1) {printf("%lld\n", r1);}
			else if (k == 2) {
				ll r2 = qry2(1, 1, n, l, r);
				ll ans = ((r1 * r1 % mod) + mod - r2) % mod * i2 % mod;
				//printf("%lld %lld ", r1, r2);
				printf("%lld\n", ans);
			}
		}
	}
	return 0;
}
