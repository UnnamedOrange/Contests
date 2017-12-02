#include <cstdio>
#include <algorithm>
#include <iostream>

using namespace std;

const int N = 1e5 + 5;

struct edge {
	int nxt, to; 
} E[N << 1];
int hd[N], et;

int n, k, t, ans; 

void add(int u, int v) {
	E[++ et].to = v; E[et].nxt = hd[u]; hd[u] = et;
	E[++ et].to = u; E[et].nxt = hd[v]; hd[v] = et;
}

int dfs(int u, int f) {
	int mx = -n, mi = n, tk = 0;
	for (int i = hd[u]; i; i = E[i].nxt) {
		int to = E[i].to;
		if (to == f) continue ;
		tk = 1;
		int x = dfs(to, u);
		mx = max(x, mx); mi = min(x, mi);
	}
	if (tk == 0) return 1;
	if (mi + mx < 0) return mi + 1; 
	else if (mx >= k){
		ans ++; /*printf("%d\n", u);*/ return -k;
	} else if (u == 1 && mx >= 0) {
		ans ++; /*printf("%d\n", u);*/ return -k;
	} else return mx + 1;
}

int main() {
	freopen("general.in", "r", stdin);
	freopen("general.out", "w", stdout);

	scanf("%d%d%d", &n, &k, &t);
	for (int i = 1; i < n; i ++) {
		int a, b; scanf("%d%d", &a, &b);
		add(a, b);
	}
	dfs(1, 0);
	//if (ans == 0) ans ++;
	if (k == 0) {
		printf("%d\n", n);
		return 0;
	}
	if (n <= 1) ans = 1;
	printf("%d\n", ans);
	return 0;
}
