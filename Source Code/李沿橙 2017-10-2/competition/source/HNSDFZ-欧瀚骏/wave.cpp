#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#define N 2000000
#define L(p) ((p) << 1)
#define R(p) ((p) << 1 | 1)
#define B 1024
using namespace std;
typedef long long LL;
int dp[2][N + 5], s[2][N + 5], num[N + 5], cnt = 0, a[N + 5], u[N + 5], d[N + 5], n;
void add(LL &a, LL b) { a += b; }
inline int lowbit(int x) { return x & (-x); }
int query(bool flag, int x) {
	int mx = 0, p = x;
	if (flag)
		while (x) mx = max(mx, s[flag][x]), x -= lowbit(x);
	else
		while (x <= cnt) mx = max(mx, s[flag][x]), x += lowbit(x);
	return mx;
}
void insert(bool flag, int x, int c) {
	int p = x;
	if (flag) 
		while (x <= cnt) s[flag][x] = max(s[flag][x], c), x += lowbit(x);
	else
		while (x) s[flag][x] = max(s[flag][x], c), x -= lowbit(x);
}
int gf(int x) {
	int l = 1, r = cnt;
	while (l < r) {
		int mid = l + r >> 1;
		if (num[mid] == x) return mid;
		if (num[mid] >  x) r = mid; else l = mid + 1;
	}
	return l;
}
int main() {
	freopen("wave.in", "r", stdin);
	freopen("wave.out", "w", stdout);
	int k;
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++) { scanf("%d", a + i); num[i] = a[i]; }
	sort(num + 1, num + 1 + n);
	cnt = unique(num + 1, num + 1 + n) - num - 1;
	for (int i = 1, j = 1; i <= cnt; i++) {
		while (j <= cnt && num[j] - num[i] < k) j++;
		u[i] = j;
	}
	for (int i = cnt, j = cnt; i; i--) {
		while (j && num[i] - num[j] < k) j--;
		d[i] = j;
	}
//	for (int i = 1; i <= cnt; i++) printf("%d ", num[i]); puts("");
	for (int i = 1; i <= n; i++) {
		a[i] = gf(a[i]);
//		printf("%d ", a[i]);
	} 
//	puts("");
//	for (int i = 1; i <= cnt; i++) printf("%d ", u[i]); puts("");
//	for (int i = 1; i <= cnt; i++) printf("%d ", d[i]); puts("");
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		dp[0][i] = query(1, d[a[i]]) + 1, dp[1][i] = query(0, u[a[i]]) + 1;
		insert(0, a[i], dp[0][i]), insert(1, a[i], dp[1][i]);
		ans = max(ans, max(dp[0][i], dp[1][i]));
	}
	printf("%d\n", ans);
	return 0;
}
