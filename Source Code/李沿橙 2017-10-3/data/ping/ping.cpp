#include <bits/stdc++.h>
using namespace std;
int n, m, P, u, v, to[200005], nxt[200005], p[100005], deep[100005], q[500005][2];
int son[100005], fa[100005], size[100005], top[100005], dfsx[100005], cnt, ans;
int lca[500005], Q[500005], lr[100005][2];
int sta[100005];
bool flag[400005];
void dfs(int x)
{
	size[x] = 1;
	for (int i = p[x]; i != -1; i = nxt[i])
		if (to[i] != fa[x])
		{
			fa[to[i]] = x;
			deep[to[i]] = deep[x] + 1;
			dfs(to[i]);
			if (son[x] == -1 || size[to[i]] > size[son[x]]) son[x] = to[i];
			size[x] += size[to[i]];
		}
}
void dfs1(int x)
{
	dfsx[x] = ++cnt;
	if (son[x] != -1) top[son[x]] = top[x], dfs1(son[x]);
	for (int i = p[x]; i != -1; i = nxt[i])
		if (to[i] != fa[x] && to[i] != son[x])
			top[to[i]] = to[i], dfs1(to[i]);
}
int findlca(int x, int y)
{
	while (1)
	{
		if (top[x] == top[y]) return deep[x] > deep[y]? y : x;
		if (deep[top[x]] > deep[top[y]]) x = fa[top[x]];
		else y = fa[top[y]];
	}
}
bool query(int x, int l, int r, int ll, int rr)
{
	if (l == ll && r == rr) return flag[x];
	int mid = (l + r) >> 1, L = x << 1, R = L | 1;
	if (rr <= mid) return query(L, l, mid, ll, rr);
	else if (ll > mid) return query(R, mid + 1, r, ll, rr);
	else return query(L, l, mid, ll, mid) | query(R, mid + 1, r, mid + 1, rr);
}
void modify(int x, int l, int r, int to)
{
	flag[x] = true;
	if (l == r) return;
	int mid = (l + r) >> 1, L = x << 1, R = L | 1;
	if (to <= mid) modify(L, l, mid, to);
	else modify(R, mid + 1, r, to);
}
bool Query(int x, int y)
{
	while (1)
	{
		if (top[x] == top[y])
		{
			if (deep[x] < deep[y]) return query(1, 1, cnt, dfsx[x], dfsx[y]);
			else return query(1, 1, cnt, dfsx[y], dfsx[x]);
		}
		if (deep[top[x]] > deep[top[y]])
			if (query(1, 1, cnt, dfsx[top[x]], dfsx[x])) return true;
			else x = fa[top[x]];
		else
		{
			if (query(1, 1, cnt, dfsx[top[y]], dfsx[y])) return true;
			else y = fa[top[y]];
		}
	}
}
void work(int x)
{
	for (int i = p[x]; i != -1; i = nxt[i])
		if (to[i] != fa[x])
			work(to[i]);
	for (int i = lr[x][0]; i <= lr[x][1]; i++)
		if (!Query(q[Q[i]][0], q[Q[i]][1]))
		{
			modify(1, 1, cnt, dfsx[x]);
			sta[++ans] = x;
			return;
		}
}
bool cmp(int x, int y) {return lca[x] < lca[y];}
int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 0; i <= n; i++) p[i] = son[i] = -1, top[i] = size[i] = fa[i] = deep[i] = 0;
	for (int i = 1; i <= n * 4; i++) flag[i] = false;
	for (int i = 1; i <= m; i++)
	{
		scanf("%d%d", &u, &v);
		u--, v--;
		to[i * 2 - 1] = v;
		nxt[i * 2 - 1] = p[u];
		p[u] = i * 2 - 1;
		to[i * 2] = u;
		nxt[i * 2] = p[v];
		p[v] = i * 2;
	}
	deep[0] = 1;
	dfs(0);
	cnt = 0;
	dfs1(0);
	scanf("%d", &P);
	for (int i = 1; i <= P; i++)
	{
		scanf("%d%d", &u, &v);
		u--, v--;
		q[i][0] = u, q[i][1] = v;
		lca[i] = findlca(u, v);
		Q[i] = i;
	}
	sort(Q + 1, Q + P + 1, cmp);
	for (int i = 0; i <= n; i++) lr[i][0] = P + 1, lr[i][1] = 0;
	for (int i = 1; i <= P; i++)
	{
		lr[lca[Q[i]]][0] = min(lr[lca[Q[i]]][0], i);
		lr[lca[Q[i]]][1] = max(lr[lca[Q[i]]][1], i);
	}
	ans = 0;
	work(0);
	printf("%d\n", ans);
	for (int i = 1; i <= ans; i++) printf("%d ", sta[i] + 1);
	return 0;
}
