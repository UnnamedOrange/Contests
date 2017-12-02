#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>

const int mod = 1000000007;
const int maxn = 100010;

using namespace std;

int n;
int depth[maxn];
vector<int> G[maxn];
int u[maxn];
int v[maxn];
int k[maxn];
int f[maxn];
int fa[maxn];
int bottom[maxn];
int length[maxn];
int ans[maxn];

void dfs(int ui, int fath);
int union_set(int ui, int vi);
int find(int ui);
long long ins(int a);
long long pow_mod(int a, int n);

int main()
{
	freopen("forest.in", "r", stdin);
	freopen("forest.out", "w", stdout);
	scanf("%d", &n);
	ans[n] = 1;
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &depth[i]);
		ans[n] *= depth[i];
		length[i] = depth[i];
		bottom[i] = i;
	}
	for (int i = 1; i < n; i++)
	{
		scanf("%d%d", &u[i], &v[i]);
		G[u[i]].push_back(v[i]);
		G[v[i]].push_back(u[i]);
	}
	for (int i = 1; i < n; i++)
		scanf("%d", &k[i]);
	dfs(1, -1);
	memset(fa, -1, sizeof fa);
	for (int i = n - 1; i >= 1; i--)
	{
		long long a = (ins(length[find(u[k[i]])]) * ans[i + 1]) % mod;
		a = (ins(length[find(v[k[i]])]) * a) % mod;
		union_set(u[k[i]], v[k[i]]);
		ans[i] = a * length[find(u[k[i]])];
	}
	for (int i = 1; i <= n; i++)
		printf("%d\n", ans[i]);
	return 0;
}

void dfs(int ui, int fath)
{
	int sz = G[ui].size();
	for (int i = 0; i < sz; i++)
		if (G[ui][i] != fath)
			dfs(G[ui][i], f[G[ui][i]] = ui);
}

int union_set(int ui, int vi)
{
	if (f[vi] != ui)
		swap(ui, vi);
	fa[vi] = ui;
	int len;
	if (bottom[find(ui)] != ui)
		len = depth[bottom[find(ui)]] + depth[find(ui)];
	else
		len = depth[find(ui)];
	find(bottom[vi]);
	len += depth[bottom[vi]];
	if (len > length[find(ui)])
		length[find(ui)] = len;
	if (depth[bottom[vi]] > depth[bottom[find(ui)]])
		bottom[find(ui)] = bottom[vi];
}

int find(int ui)
{
	if (fa[ui] == -1)
		return ui;
	int vi = find(fa[ui]);
	if (fa[ui] != vi)
		depth[ui] += depth[fa[ui]];
	return fa[ui] = vi;
}

long long ins(int a)
{
	return pow_mod(a, mod - 2);
}

long long pow_mod(int a, int n)
{
	if (n == 0)
		return 1;
	long long pow_ans = pow_mod(a, n / 2);
	pow_ans = (pow_ans * pow_ans) % mod;
	if (n % 2 == 1)
		pow_ans = (pow_ans * a) % mod;
	return pow_ans;
}

