#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define eps 1e-8
#define N 100000
#define MOD 1000000007
using namespace std;
typedef long long LL;
inline int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }
inline LL fpow(LL a, LL n) {
	LL ans = 1, tmp = a;
	while (n) {
		if (n & 1) ans = ans * tmp % MOD;
		tmp = tmp * tmp % MOD, n >>= 1;
	}
	return ans;
}
struct Edge {
	int next, to;
} ed[2 * N + 5];
struct edge {
	int u, v;
} e[N + 5];
int que[2 * N + 5], father[N + 5], dep[N + 5], dis[N + 5], st[20][2 * N + 5], ln[2 * N + 5], l[N + 5], r[N + 5], d[N + 5], ans[N + 5], last[N + 5], ecnt = 0, cnt = 0, dfn[N + 5], a[N + 5], n, f[N + 5], k[N + 5];
int getfather(int u) { return u == f[u] ? u : f[u] = getfather(f[u]); }
void add(int u, int v) {
	ed[++ecnt].to = v, ed[ecnt].next = last[u], last[u] = ecnt;
	ed[++ecnt].to = u, ed[ecnt].next = last[v], last[v] = ecnt;
}
void dfs(int u) { 
	que[++cnt] = u, dfn[u] = cnt;
	dep[u] = dep[father[u]] + 1;
	dis[u] = dis[father[u]] + a[u];
	for (int i = last[u]; i; i = ed[i].next) {
		int v = ed[i].to;
		if (v == father[u]) continue;
//		printf("%d -> %d\n", u, v);
		father[v] = u, dfs(v);
		que[++cnt] = u;
	}
}
void buildST() {
	ln[0] = -1;
	for (int i = 1; i <= cnt; i++) 
		st[0][i] = que[i],
		ln[i] = ln[i >> 1] + 1;
	for (int j = 1; j < 20; j++) 
		for (int i = 1; i <= cnt; i++) 
			if (dep[st[j - 1][i]] < dep[st[j - 1][min(cnt, i + (1 << j - 1))]])
				st[j][i] = st[j - 1][i];
			else 
				st[j][i] = st[j - 1][min(cnt, i + (1 << j - 1))];
}
int getlca(int u, int v) {
	int ll = dfn[u], rr = dfn[v];
	if (ll > rr) swap(ll, rr);
	int len = ln[rr - ll + 1];
	if (dep[st[len][ll]] < dep[st[len][rr - (1 << len) + 1]]) 
		return st[len][ll]; 
	else return st[len][rr - (1 << len) + 1];
}
int getdis(int u, int v) {
	int lca = getlca(u, v);
	return dis[u] + dis[v] - 2 * dis[lca] + a[lca];
}
void merge(int u, int v) {
	int d1 = getdis(l[u], l[v]),
		 d2 = getdis(l[u], r[v]),
		 d3 = getdis(r[u], l[v]),
		 d4 = getdis(r[u], r[v]),
		 mx = max(max(max(d1, d2), max(d3, d4)), max(d[u], d[v]));
	if (d1 == mx)
		r[u] = l[v], d[u] = d1; else
	if (d2 == mx) 
		r[u] = r[v], d[u] = d2; else 
	if (d3 == mx)
		l[u] = l[v], d[u] = d3; else 
	if (d4 == mx)
		l[u] = r[v], d[u] = d4; else
	if (d[v] == mx)
		l[u] = l[v], r[u] = r[v], d[u] = d[v];
	f[v] = u;
}
int main() {
	freopen("forest.in", "r", stdin);
	freopen("forest.out", "w", stdout);
	scanf("%d", &n);
	ans[n] = 1;
	for (int i = 1; i <= n; i++) { scanf("%d", a + i); f[i] = l[i] = r[i] = i, d[i] = a[i], ans[n] = ans[n] * 1ll * a[i] % MOD; }
	for (int i = 1; i < n; i++) {
		scanf("%d%d", &e[i].u, &e[i].v);
		add(e[i].u, e[i].v);
	}
	dfs(1);
	buildST();
	for (int i = 1; i < n; i++) scanf("%d", k + i);
	for (int i = n - 1; i; i--) {
		e[k[i]].u = getfather(e[k[i]].u), e[k[i]].v = getfather(e[k[i]].v);
		ans[i] = ans[i + 1] * 1ll * fpow(d[e[k[i]].u] * 1ll * d[e[k[i]].v] % MOD, MOD - 2) % MOD;
//		printf("%d %d\n", d[e[k[i]].u], d[e[k[i]].v]);
		merge(e[k[i]].u, e[k[i]].v);
//		printf("%d\n", d[e[k[i]].u]);
		ans[i] = ans[i] * 1ll * d[e[k[i]].u] % MOD;
	}
	for (int i = 1; i <= n; i++) printf("%d\n", ans[i]);
	return 0;
}
