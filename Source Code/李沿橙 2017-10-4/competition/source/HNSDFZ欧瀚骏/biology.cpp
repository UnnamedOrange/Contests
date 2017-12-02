#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 1000000 
#define DICSIZE 26
using namespace std;
int dep[N + 5], father[N + 5][21], next[N + 5][DICSIZE], num[N + 5], cnt = 0;
char s[N + 5];
int newnode(int rt) {
	int p = ++cnt;
	dep[p] = dep[rt] + 1;
	memset(next[p], 0, sizeof(next[p]));
	father[p][0] = rt;
	for (int i = 1; i <= 20; i++)
		father[p][i] = father[father[p][i - 1]][i - 1];
	return p;
}
void insert(int x) {
	int len = strlen(s), p = 1;
	for (int i = 0; i < (len >> 1); i++) swap(s[i], s[len - i - 1]);
	for (int i = 0; i < len; i++) {
		if (!next[p][s[i] - 'a']) next[p][s[i] - 'a'] = newnode(p);
		p = next[p][s[i] - 'a'];
	}
	num[x] = p;
}
int getlca(int u, int v) {
	int i = 20;
	if (dep[u] < dep[v]) swap(u, v);
	while (dep[u] != dep[v]) {
		while (dep[father[u][i]] < dep[v] && i) i--;
		u = father[u][i];
	}
	i = 20;
	while (u != v) {
		while (father[u][i] == father[v][i] && i) i--;
		u = father[u][i], v = father[v][i];
	}
	return u;
}
int main() {
	freopen("biology.in", "r", stdin);
	freopen("biology.out", "w", stdout);
	int n, m;
	scanf("%d%d", &n, &m);
	cnt = 1;
	dep[0] = -1;
	for (int i = 1; i <= n; i++) {
		scanf("%s", s);
		insert(i);
	}
	while (m--) {
		int op, t;
		scanf("%d", &op);
		if (op == 1) {
			scanf("%s", s);
			insert(++n);
		}
		if (op == 2) {
			scanf("%d", &t);
			int lca; scanf("%d", &lca);
			lca = num[lca];
			for (int i = 2; i <= t; i++) {
				int x; scanf("%d", &x);
				lca = getlca(lca, num[x]);
			}
			printf("%d\n", dep[lca]);
		}
	}
	return 0;
}
