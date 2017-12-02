#include <bits/stdc++.h>
using namespace std;

struct edge {
	int next, to;
} e[2333333] ;

int ecnt = 1, head[233333];


void add(int u, int v) {
	e[++ecnt] = (edge) {head[u], v}; head[u] = ecnt;
	e[++ecnt] = (edge) {head[v], u}; head[v] = ecnt;
}



int n, k, t, cnt;

bool vis[233333];

void dfs(int x) {
	vis[x] = 1; cnt++;
	for (int o = head[x]; o; o = e[o].next) {
		if (!vis[e[o].to]) dfs(e[o].to);
	}
}

int main() {
	freopen("general1.in", "r", stdin);
	scanf("%d%d%d", &n, &k, &t);
	for (int i = 1; i <= n; i++) {
		int u, v;
		scanf("%d%d", &u, &v); add(u, v);
	}
	dfs(1);
	printf("%d\n", cnt);
}
