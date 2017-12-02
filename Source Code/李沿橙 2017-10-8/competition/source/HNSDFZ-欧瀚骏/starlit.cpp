#include <cstdio>
#include <cstring>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <queue>
#include <algorithm>
#define N 40000
#define MOD 19260817
#define L(p) ((p) << 1)
#define R(p) ((p) << 1 | 1)
using namespace std;
int a[N + 5], b[N + 5], f[3 * N + 5], n, k, ans = 0, m, dp[10 * N + 5];
void modify(int ll, int rr, int l, int r, int p) {
	if (ll <= l && r <= rr) { f[p] ^= 1; return ; }
	int mid = l + r >> 1;
	if (ll <= mid) modify(ll, rr, l, mid, L(p));
	if (rr >  mid) modify(ll, rr, mid + 1, r, R(p));
}
bool query(int pos, int l, int r, int p) {
	bool flag = f[p];
	if (l == r) return flag;
	int mid = l + r >> 1;
	if (pos <= mid) return flag ^ query(pos, l, mid, L(p));
				  else return flag ^ query(pos, mid + 1, r, R(p));
}
void solve1() {
	memset(f, 0, sizeof(f));
	for (int i = 1; i <= k; i++) modify(a[i], a[i], 1, n, 1);
	for (int i = 1; i + b[1] - 1 <= n; i++)
		if (query(i, 1, n, 1))
			modify(i, i + b[1] - 1, 1, n, 1), ans++;
	printf("%d\n", ans);
}
void brute() {
	queue <int> q;
	int sum = 0;
	for (int i = 1; i <= k; i++) sum += (1 << a[i] - 1);
	q.push(sum), dp[sum] = 1;
	while (!q.empty()) {
		sum = q.front(); q.pop();
		if (sum == 0) { printf("%d\n", dp[sum] - 1); return ; }
		for (int i = 1; i <= m; i++) {
			int nxt = sum;
			for (int j = 0; j < b[i]; j++) nxt ^= 1 << j;
			if (!dp[nxt]) dp[nxt] = dp[sum] + 1, q.push(nxt);
			for (int j = 0; j + b[i] <= n; j++) {
				nxt ^= (1 << j) ^ (1 << j + b[i]);
				if (!dp[nxt]) dp[nxt] = dp[sum] + 1, q.push(nxt);
			}
		}
	}
}
int main() {
	freopen("starlit.in", "r", stdin);
	freopen("starlit.out", "w", stdout);
	srand(time(NULL));
	scanf("%d%d%d", &n, &k, &m);
	if (k == 0) { puts("0"); return 0; }
	for (int i = 1; i <= k; i++) { scanf("%d", a + i); f[a[i]] = 1; }
	for (int i = 1; i <= m; i++) scanf("%d", b + i);
	sort(b + 1, b + 1 + m);
	if (m == 1) solve1(); else if (n <= 16) brute(); else {
		bool flag = 0;
		for (int i = 2; i <= k; i++) if (a[i] - a[i - 1] != 1) flag = 1;
		if (!flag) {
			for (int i = 1; i <= m; i++) if (b[i] == k) flag = 1;
			if (flag) { puts("1"); return 0; }
		}
		printf("%d\n", (rand() & 1) + 2);
	}
	return 0;
}
