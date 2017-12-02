#include <bits/stdc++.h>
using namespace std;

#define MAXN 100005

struct edge {
	int next, to;
} e[MAXN * 2];

int head[MAXN], ecnt = 0;

void add(int u, int v) {
	e[++ecnt] = (edge) {head[u], v}; head[u] = ecnt;
	e[++ecnt] = (edge) {head[v], u}; head[v] = ecnt;
}

int n, K, t, ans = 0;
int q[MAXN], fa[MAXN], f[MAXN];

void bfs() {
	int he = 1, ta = 2;
	q[he] = 1; fa[1] = 1;
	while (he < ta) {
		int x = q[he++];
		for (int o = head[x]; o; o = e[o].next) {
			if (!fa[e[o].to]) {
				fa[e[o].to] = x;
				q[ta++] = e[o].to;
			}
		}
	}
}

void update(int x) {
	if (!f[x]) return;
	for (int o = head[x]; o; o = e[o].next) {
		if (f[e[o].to] < f[x] - 1) {
			f[e[o].to] = f[x] - 1;
			update(e[o].to);
		}
	}
}

int main() {
	freopen("general.in", "r", stdin);
	freopen("general.out", "w", stdout);
	scanf("%d%d%d", &n, &K, &t);
	for (int i = 1, u, v; i < n; i++) {
		scanf("%d%d", &u, &v);
		add(u, v);
	}
	bfs();
	memset(f, -1, sizeof f);
	for (int i = n; i; i--) {
		if (f[q[i]] == -1) {
			ans++;
			int j = q[i];
			for (int k = K; k; k--) j = fa[j];
			f[j] = K;
			update(j);
		}
	}
	printf("%d\n", ans);
}
