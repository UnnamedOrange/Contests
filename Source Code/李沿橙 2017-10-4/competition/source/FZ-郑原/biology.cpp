#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>

using namespace std;

const int N = 1000000 + 10;

struct edge {
	int nxt, to, kd;
} E[N];
int hd[N], et, nt, rc; 

int n, m, len, pt[N], fa[N][23], dep[N], hgt, rt = 1;
char s[10000 + 5];

void add(int a, int b, int c) {
	E[++ et].to = b; E[et].nxt = hd[a]; hd[a] = et; E[et].kd = c;
}

void insert(int wh) {
	int u = rt;
	for (int i = 0; i < len; i ++) {
		int wi = -1; 
		for (int j = hd[u]; j; j = E[j].nxt)
			if (E[j].kd == s[i] - 'a') {
				wi = j; 
				break ;
			}
		if (wi == -1) {
			add(u, ++ nt, s[i] - 'a');
			wi = et; 
			int to = E[wi].to;
			dep[to] = dep[u] + 1; fa[to][0] = u; 
		}
		int to = E[wi].to;
		//dep[to] = dep[u] + 1; fa[to][0] = u; 
		u = to;
	}
	pt[wh] = u; 
}

void build() {
	for (int i = 1; ; i ++) {
		int tk = 0; hgt = i;
		for (int j = 1; j <= nt; j ++) {
			fa[j][i] = fa[fa[j][i - 1]][i - 1];
			if (fa[j][i]) tk = 1;
		}
		if (!tk) break ;
	}
}

void change() {
	for (int i = 1; ; i ++) {
		int tk = 0; hgt = i;
		for (int j = rc + 1; j <= nt; j ++) {
			fa[j][i] = fa[fa[j][i - 1]][i - 1];
			if (fa[j][i]) tk = 1;
		}
		if (!tk) break ;
	}
}

int qry(int a, int b) {
	a = pt[a], b = pt[b];
	if (dep[a] < dep[b]) swap(a, b);
	for (int i = hgt; i >= 0; i --) 
		if (dep[fa[a][i]] >= dep[b]) a = fa[a][i];
	if (a == b) return dep[a];
	for (int i = hgt; i >= 0; i --) 
		if (fa[a][i] != fa[b][i]) 
			a = fa[a][i], b = fa[b][i];
	return dep[fa[a][0]];
}

int main() {
	freopen("biology.in", "r", stdin);
	freopen("biology.out", "w", stdout);

	scanf("%d%d", &n, &m);
	nt = 1;
	for (int i = 1; i <= n; i ++) {
		scanf("%s", s); len = strlen(s);
		int l = 0, r = len - 1;
		while (l < r) {swap(s[l], s[r]); l ++, r --;}
		insert(i);
	}
	build();
	int ct = n; 
	for (int i = 1; i <= m; i ++) {
		int tp; scanf("%d", &tp);
		if (tp == 1) {
			scanf("%s", s); len = strlen(s);
			int l = 0, r = len - 1;
			while (l < r) {swap(s[l], s[r]); l ++, r --;}
			rc = nt;
			insert(++ ct);
			change();
		} else {
			int Tt, x; scanf("%d%d", &Tt, &x); 
			//int md = pt[x];
			int y, ans = dep[pt[x]]; 
			for (int j = 2; j <= Tt; j ++) {
				scanf("%d", &y);
				ans = min(ans, qry(x, y));
			}
			printf("%d\n", ans);
		}
	}
	return 0;
}
