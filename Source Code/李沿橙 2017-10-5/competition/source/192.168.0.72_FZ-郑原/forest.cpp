#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

const int N = 100000 + 5; 
const int mod = 1e9 + 7;

struct edge {
	int nxt, to, tok; 
} E[N << 1];
int hd[N], tot;

void add(int a, int b) {
	E[++ tot].to = b; E[tot].nxt = hd[a]; hd[a] = tot; E[tot].tok = 0; 
	E[++ tot].to = a; E[tot].nxt = hd[b]; hd[b] = tot; E[tot].tok = 0;
}

int pow(int x, int a) {
	int ret = 1;
	while (a) {
		if (a & 1) ret = (ll) ret * x % mod;
		x = (ll) x * x % mod;
		a >>= 1;
	}
	return ret;
}

int vis[N], A[N], inq[N], n;
int ans, mx, wh; 
int ass[N];
int fa[N], len[N]; 

int find(int x) {
	return fa[x] == 0 ? x : fa[x] = find(fa[x]); 
}

void un(int x, int y) {
	if ((x = find(x)) == (y = find(y))) return ;
	fa[x] = y; 
}

void dfs(int x, int num) {
	vis[x] = 1;
	inq[x] = 1; 
	wh = x, mx = num;
	for (int i = hd[x]; i; i = E[i].nxt) {
		if (E[i].tok) continue ;
		int to = E[i].to;
		if (inq[to]) continue ;
		dfs(to, num + A[to]);
	}
	inq[x] = 0;
}

int main() {
	freopen("forest.in", "r", stdin);
	freopen("forest.out", "w", stdout);

	scanf("%d", &n);
	for (int i = 1; i <= n; i ++) scanf("%d", &A[i]); 
	for (int i = 1; i < n; i ++) {
		int a, b; scanf("%d%d", &a, &b);
		add(a, b);
	}
	for (int i = 1; i <= n; i ++) {
		int ans = 1; 
		if (i > 1) {
			int ne; scanf("%d", &ne);
			E[ne << 1].tok = E[(ne << 1) - 1].tok = 1;
		}
		for (int i = 1; i <= n; i ++) vis[i] = 0; 
		for (int i = 1; i <= n; i ++)
			if (!vis[i]) {
				wh = i, mx = 0;
				dfs(i, A[i]);
				dfs(wh, A[wh]); 
				ans = (ll) ans * mx % mod;
			}
		printf("%d\n", ans);
	}
	/*ass[n] = 1; 
	for (int i = 1; i < n; i ++) {len[i] = A[i]; ass[n] = (ll) ass[n] * len[i] % mod;}
	for (int i = n - 1; i; i --) {
		int nana = ass[i] << 1;
		E[ass[i] << 1].tok = E[(ass[i] << 1) - 1].tok = 0;
		ass[i] = (ll) ass[n] * pow(A[E[nana].to], mod - 2) % mod * pow(A[E[nana - 1].to], mod - 2) % mod;
		un
	}*/
	return 0;
}
