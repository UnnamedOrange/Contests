#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#define N 111111
#define MOD 1000000007
#define LL long long
using namespace std;

int a[N], dep[N], sum[N], par[N][18], h[N], del[N];
int endpoint[N][2], ans[N], f[N], length[N];
int tote, n, product;

struct edge{
	int s, t, n;
}e[N * 2];

void adde(int u, int v) {
	e[++tote].t = v;
	e[tote].s = u;
	e[tote].n = h[u];
	h[u] = tote;
	return ;
}

void dfs(int u, int fa) {
	par[u][0] = fa;
	dep[u] = dep[fa] + 1;
	sum[u] = sum[fa] + a[u];
	for (int i = 1; i < 18; i++) par[u][i] = par[par[u][i - 1]][i - 1];
	for (int i = h[u]; i; i = e[i].n) {
		int v = e[i].t;
		if (v != fa) dfs(v, u);
	}
	return ;
}

int lca(int u, int v) {
	if (dep[u] < dep[v]) swap(u, v);
	for (int t = dep[u] - dep[v], i = 0; t > 0; t >>= 1, i++)
		if (t & 1) u = par[u][i];
	int t = 17;
	while (u != v) {
		while (t && par[u][t] == par[v][t]) t--;
		u = par[u][t]; v = par[v][t];
	}
	return u;
}

int getf(int u) {
	if (u == f[u]) return u;
	f[u] = getf(f[u]);
	return f[u];
}

int pw(int a, int b) {
	int ans = 1, t = a;
	for (int i = b; i; i >>= 1) {
		if (i & 1) ans = (LL) ans * t % MOD;
		t = (LL) t * t % MOD;
	}
	return ans;
}

int getlength(int u, int v) {
	int w = lca(u, v);
	return sum[u] + sum[v] - 2 * sum[w] + a[w];
}

int getint()
{
	char ch;
	do
	{
		ch=getchar();
	}while (ch!='-'&&(ch<'0'||ch>'9'));
	int ans=0,f=0;
	if (ch=='-') f=1; else ans=ch-'0';
	while (isdigit(ch=getchar())) ans=ans*10+ch-'0';
	if (f) ans*=-1;
	return ans;
}

int main() {
	freopen("forest.in", "r", stdin);
	freopen("forest.out", "w", stdout);
	n = getint();
	product = 1;
	for (int i = 1; i <= n; i++) {
		a[i] = getint();
		f[i] = i;
		product = (LL) product * a[i] % MOD;
		endpoint[i][0] = endpoint[i][1] = i;
		length[i] = a[i]; 
	}

	for (int i = 1; i < n; i++) {
		int u = getint(), v = getint();
		adde(u, v); adde(v, u);
	}

	dfs(1, 0);

	int t = n;
	ans[t] = product;

	for (int i = 1; i < n; i++) del[i] = getint();

	for (int i = n - 1; i; i --) {
		int id = del[i], u = e[id * 2 - 1].s, v = e[id * 2 - 1].t;
		u = getf(u); v = getf(v);
		if (length[u] < length[v]) swap(u, v);
		int tmax = length[u], end[2];
		for (int j = 0; j < 2; j++) end[j] = endpoint[u][j];
		for (int j = 0; j < 2; j++)
			for (int k = 0; k < 2; k++) {
				int l = getlength(endpoint[u][j], endpoint[v][k]);
				if (l > tmax) {
					tmax = l;
					end[0] = endpoint[u][j]; 
					end[1] = endpoint[v][k];
				}
			}
		product = (LL) product * pw(length[u], MOD - 2) % MOD;
		product = (LL) product * pw(length[v], MOD - 2) % MOD;
		f[v] = u;
		length[u] = tmax;
		for (int j = 0; j < 2; j++) endpoint[u][j] = end[j];
		product = (LL) product * length[u] % MOD;
		ans[--t] = product;
	}
	for (int i = 1; i <= n; i++) printf("%d\n", ans[i]);
	return 0;
}
