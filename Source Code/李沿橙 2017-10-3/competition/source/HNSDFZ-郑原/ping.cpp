#include <cstdio>
#include <algorithm>
#include <iostream>

using namespace std;

const int N = 1e5 + 5; 

struct edge {
	int nxt, to;
} E[N << 1];
int hd[N], tot;

void add(int a, int b) {
	E[++ tot].to = b; E[tot].nxt = hd[a]; hd[a] = tot;
	E[++ tot].to = a; E[tot].nxt = hd[b]; hd[b] = tot;
}

int n, m, k;

int cnt[N], bk[N];

int fa[N][20], dep[N], hgt;

int ans, ax[20], sx[20], qry[N * 3][2];

void ddd(int x) {
	for (int i = hd[x]; i; i = E[i].nxt) {
		int to = E[i].to;
		if (fa[x][0] == to) continue ;
		fa[to][0] = x; 
		dep[to] = dep[x] + 1;
		ddd(to);
	}
}

void build() {
	for (int i = 1; ; i ++) {
		hgt = i;
		int tk = 0; 
		for (int j = 1; j <= n; j ++) {
			fa[j][i] = fa[fa[j][i - 1]][i - 1];
			if (fa[j][i]) tk = 1;
		}
		if (tk == 0) break ;
	}
}

int qlca(int a, int b) {
	if (dep[a] < dep[b]) swap(a, b);
	for (int i = hgt; i >= 0; i --) 
		if (dep[fa[a][i]] >= dep[b])
			a = fa[a][i];
	for (int i = hgt; i >= 0; i --) 
		if (fa[a][i] != fa[b][i])
			a = fa[a][i], b = fa[b][i];
	return a != b ? fa[a][0] : a;
}

bool check() {
	int ret = 1;
	for (int i = 1; i <= k && ret; i ++) {
		int p1 = qry[i][0], p2 = qry[i][1];
		int lca = qlca(p1, p2);
		int tok = 0;
		while (p1 && !tok) {if (sx[p1]) tok = 1; if (p1 == lca) break; p1 = fa[p1][0];}
		while (p2 && !tok) {if (sx[p2]) tok = 1; if (p2 == lca) break; p2 = fa[p2][0];}
		if (tok == 0) ret = 0;
	}
	return ret;
}

void dfs(int now, int cnt) {
	if (now == n) {
		if (cnt >= ans) return ;
		if (check()) {
			ans = cnt; 
			for (int i = 1; i <= n; i ++) 
				ax[i] = sx[i];
		}
		return ;
	}
	sx[now + 1] = 0; 
	dfs(now + 1, cnt);
	sx[now + 1] = 1; 
	dfs(now + 1, cnt + 1);
}

int main() {
	freopen("ping.in", "r", stdin);
	freopen("ping.out", "w", stdout);

	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i ++) {
		int a, b; scanf("%d%d", &a, &b);
		add(a, b);
	}
	dep[1] = 1;
	ddd(1);
	build();
	/*for (int i = 1; i <= n; i ++) sx[i] = 0;
	sx[3] = 1;
	if (check()) printf("^_^\n");
	else printf("QAQ\n");*/
	//if (n <= 15 && m <= 15) {
		ans = n; 
		for (int i = 1; i <= n; i ++) ax[i] = 1;
		scanf("%d", &k);
		for (int i = 1; i <= k; i ++)
			scanf("%d%d", &qry[i][0], &qry[i][1]);
		dfs(0, 0);
		int sc[n + 1], dt = 0; 
		for (int i = 1; i <= n; i ++) 
			if (ax[i]) sc[++ dt] = i; 
		printf("%d\n", dt);
		for (int i = 1; i <= dt; i ++) 
			printf("%d ", sc[i]);
		return 0;
	//}
	//return 0;
}
