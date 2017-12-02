#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 300000
using namespace std;
struct Edge {
	int next, to;
} ed[2 * N + 5];
struct Interval {
	int l, r;
	bool operator < (const Interval &b) const { return r != b.r ? r < b.r : l < b.l; }
} ques[N + 5];
int top[N + 5], last[N + 5], ecnt = 0, cnt = 0, dep[N + 5], qv[N + 5], qu[N + 5], que[N + 5], mxdep = 0, k, n, m, h[N + 5], dfn[N + 5], ha[N + 5];
void add(int u, int v) {
	ed[++ecnt].to = v, ed[ecnt].next = last[u], last[u] = ecnt;
	ed[++ecnt].to = u, ed[ecnt].next = last[v], last[v] = ecnt;
}
void dfs(int u, int anc) {
	dfn[u] = ++cnt, que[cnt] = u, mxdep = max(mxdep, dep[u]);
	top[u] = anc;
	for (int i = last[u]; i; i = ed[i].next)
		if (!dep[ed[i].to])
			dep[ed[i].to] = dep[u] + 1, dfs(ed[i].to, anc);
}
void solve() {
	for (int i = 1; i <= k; i++) {
		ques[i].l = dfn[qu[i]], ques[i].r = dfn[qv[i]];
		if (ques[i].r < ques[i].l) swap(ques[i].l, ques[i].r);
	}
	sort(ques + 1, ques + 1 + k);
	int mxr = -1, ans = 0;
	for (int i = 1; i <= k; i++)
		if (ques[i].l > mxr) mxr = ques[i].r, h[++ans] = que[mxr];
	printf("%d\n", ans);
	for (int i = 1; i <= ans; i++) printf("%d ", h[i]); puts("");
}
void brute() {
	int mi = n;
	for (int s = 1; s < (1 << n); s++) {
		cnt = 0;
		int ans = 0;
		for (int i = 1; i <= n; i++) {
			if ((1 << i - 1) & s)
				dep[i] = 1, h[++ans] = i;
			else dep[i] = 0;
			dfn[i] = top[i] = 0;
		}
		if (ans >= mi) continue;
		for (int i = 1; i <= n; i++) 
			if (!dfn[i]) dfs(i, i); 
		bool flag = 1;
		for (int i = 1; i <= m && flag; i++)
			if (top[qu[i]] && top[qv[i]] && top[qu[i]] == top[qv[i]])
				flag = 0;
		if (flag) {
			mi = ans;
			for (int i = 1; i <= ans; i++) ha[i] = h[i];
		}
	}
	printf("%d\n", mi);
	for (int i = 1; i <= mi; i++)
		printf("%d ", ha[i]);
	puts("");
}
int main() {
	freopen("ping.in", "r", stdin);
	freopen("ping.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v);
	}
	scanf("%d", &k);
	for (int i = 1; i <= k; i++) scanf("%d%d", qu + i, qv + i);
	dep[1] = 1;
	dfs(1, 1);
	if (mxdep == n) 
		solve();
	else 
		brute();
	return 0;
}
