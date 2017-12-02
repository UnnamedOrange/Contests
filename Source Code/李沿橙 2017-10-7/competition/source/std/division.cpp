#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

#define N 131073

int n, m = 0, K;
int a[N], b[N];
bool vis[N], dvis[N], issqr[N * 2];
int f[N * 2];

int getf(int x) {return f[x] > 0 ? (f[x] = getf(f[x])) : x;}

void merge(int u, int v) {
	u = getf(u), v = getf(v);
	if (u != v) {
		if (f[u] > f[v]) swap(u, v);
		f[u] += f[v];
		f[v] = u;
	}
}

bool check(int u, int v) {
	int s1 = getf(u), s2 = getf(u + N);
	int t1 = getf(v), t2 = getf(v + N);
	if (s1 == t1) return 1;
	if (s2 == t2) return 1;
	merge(s1, t2); merge(s2, t1);
	return 0;
}

void solve_1() {
	for (int i = n, j = n; i;) {
		for (bool flag = 1; j; j--) {
			for (int k = 1; k * k - a[j] < N; k++) {
				if (k * k - a[j] <= 0) continue;
				if (vis[k * k - a[j]]) {flag = 0; break;} 
			}
			if (!flag) break;
			vis[a[j]] = 1;
		}
		if (!j) break;
		b[++m] = j;
		for ( ; i > j; i--) vis[a[i]] = 0;
	}
}

void solve_2() {
	memset(f, -1, sizeof f);
	for (int i = 1; i * i < 2 * N; i++) issqr[i * i] = 1;
	for (int i = n, j = n; i;) {
		for (bool flag = 1; j; j--) {
			if (vis[a[j]]) {
				if (issqr[a[j] + a[j]]) {
					if (dvis[a[j]]) break;
					for (int k = 1; k * k - a[j] < N; k++) {
						if (k * k - a[j] <= 0) continue;
						if (vis[k * k - a[j]] && k * k != a[j] * 2) {
							flag = 0; break;
						} 
					}
					if (!flag) break;
					dvis[a[j]] = 1;
				}
			}
			else {
				for (int k = 1; k * k - a[j] < N; k++) {
					if (k * k - a[j] <= 0) continue;
					if (vis[k * k - a[j]]) {
						if (check(k * k - a[j], a[j])) {flag = 0; break;}
					} 
				}
				if (!flag) break;
				vis[a[j]] = 1;
			}
		}
		if (!j) break;
		b[++m] = j;
		for ( ; i > j; i--) f[a[i]] = f[a[i] + N] = -1, vis[a[i]] = 0, dvis[a[i]] = 0;
	}
}

int main() {
	freopen("division.in", "r", stdin);
	freopen("division.out", "w", stdout);
	scanf("%d%d", &n, &K);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	if (K == 1) solve_1();
	else solve_2();
	printf("%d\n", m + 1);
	for (int i = m; i; i--) printf("%d ", b[i]);
	putchar('\n');
	return 0;
}

