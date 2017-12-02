#include <cstdio>
#include <queue>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 25
#define inf 1e9
using namespace std;
struct Edge {
	int next, to, w;
} ed[200];
int s = 24, vis[N + 5], inq[N + 5], last[N + 5], dis[N + 5], a[N + 5], b[N + 5], ecnt = 0;
void add(int u, int v, int w) { ed[++ecnt].to = v, ed[ecnt].next = last[u], ed[ecnt].w = w, last[u] = ecnt; }
bool spfa() {
	for (int i = 0; i < s; i++) dis[i] = -inf, inq[i] = vis[i] = 0;
	dis[s] = 0, inq[s] = 1, vis[s] = 0;
	queue <int> q;
	q.push(s);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		inq[u] = 0;
		if (vis[u] > 25) return 0;
		for (int i = last[u]; i; i = ed[i].next) {
			int v = ed[i].to;
			if (dis[v] >= dis[u] + ed[i].w) continue;
			dis[v] = dis[u] + ed[i].w;
			vis[v]++;
			if (!inq[v]) inq[v] = 1, q.push(v);
		}
	}
	return 1;
}
bool check(int s0) {
	ecnt = 0;
	memset(last, 0, sizeof(last));
	for (int i = 0; i < 24; i++) {
		if (i >= 8) add(i - 8, i, a[i]);
				 else add(i + 16, i, a[i] - s0);
		if (i) add(i, i - 1, -b[i]), add(i - 1, i, 0);
		  else add(i, s, -b[i]), add(s, i, 0);
	}
	add(23, s, -s0), add(s, 23, s0);
	return spfa();
}
int main() {
	freopen("cashier.in", "r", stdin);
	freopen("cashier.out", "w", stdout);
	int t;
	scanf("%d", &t);
	while (t--) {
		int l = 0, r = 0;
		for (int i = 0; i < 24; i++) { scanf("%d", a + i); l = max(l, a[i]); }
		for (int i = 0; i < 24; i++) {
			scanf("%d", b + i);
			r += b[i];
		}
		if (l > r || !check(r)) { puts("-1"); continue; }
		if (l == 0) { puts("0"); continue; }
		while (l < r) {
			int mid = l + r >> 1;
			if (check(mid)) r = mid; else l = mid + 1;
		}
		printf("%d\n", l);
	}
	return 0;
}
