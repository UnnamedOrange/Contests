#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 200000
using namespace std;
typedef long long LL;
struct Edge {
	int next, to;
} ed[2 * N + 5];
int last[N + 5], ans = 0, ecnt = 0, n, k, t, dp[N + 5];
bool vis[N + 5];
void add(int u, int v) {
	ed[++ecnt].to = v, ed[ecnt].next = last[u], last[u] = ecnt;
	ed[++ecnt].to = u, ed[ecnt].next = last[v], last[v] = ecnt;
}
int getAns(int u) {
	int mx = -N, mi = N;
	vis[u] = 1;
	for (int i = last[u]; i; i = ed[i].next) {
		int v = ed[i].to;
		if (vis[v]) continue;
		mx = max(mx, getAns(v) + 1);
		mi = min(mi, dp[v] + 1);
	}
//	printf("%d %d %d\n", u, mx, mi);
	if (-mi > mx) return dp[u] = mi;
	if (mx == -N) return dp[u] = 0;
	if (mx == k) { ans++; return dp[u] = - k - 1; }
	return dp[u] = mx;
}
int main() {
	freopen("general.in", "r", stdin);
	freopen("general.out", "w", stdout);
	scanf("%d%d%d", &n, &k, &t);
	for (int i = 1; i < n; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v);
	}
	int tmp = getAns(1);
	printf("%d\n", ans + (tmp >= 0 ? 1 : 0));
	return 0;
}
