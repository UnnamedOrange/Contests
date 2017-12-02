#include <bits/stdc++.h>
using namespace std;
int n, m, P, u, v, to[200005], nxt[200005], p[100005], deep[100005], q[500005][2];
int son[100005], fa[100005], size[100005], top[100005], dfsx[100005], cnt, ans;
int lca[500005];
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
bool cmp(int x, int y) {return lca[x] < lca[y];}
FILE *fin, *fout, *fstd, *fscore, *freport;
int main(int argc, char *argv[])
{
    fin = fopen(argv[1], "r");
    fout = fopen(argv[2], "r");
    fstd = fopen(argv[3], "r");
    fscore = fopen(argv[5], "w");
    freport = fopen(argv[6], "w");
	fscanf(fin, "%d%d", &n, &m);
	for (int i = 0; i <= n; i++) p[i] = son[i] = -1, top[i] = size[i] = fa[i] = deep[i] = 0;
	for (int i = 1; i <= n * 4; i++) flag[i] = false;
	for (int i = 1; i <= m; i++)
	{
		fscanf(fin, "%d%d", &u, &v);
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
	fscanf(fin, "%d", &P);
	for (int i = 1; i <= P; i++)
	{
		fscanf(fin, "%d%d", &u, &v);
		u--, v--;
		q[i][0] = u, q[i][1] = v;
		lca[i] = findlca(u, v);
	}
	fscanf(fout, "%d", &ans);
	int ans1;
	fscanf(fstd, "%d", &ans1);
	if (ans != ans1)
	{
		fprintf(fscore, "0");
		fprintf(freport, "Wrong Answer!");
		return 0;
	}
	for (int i = 1; i <= ans; i++)
	{
		fscanf(fout, "%d", &u);
		u--;
		modify(1, 1, cnt, dfsx[u]);
	}
	for (int i = 1; i <= P; i++)
		if (!Query(q[i][0], q[i][1]))
		{
			fprintf(fscore, "0");
			fprintf(freport, "Wrong Answer!");
			return 0;
		}
	fprintf(fscore, "5");
	fprintf(freport, "Correct! orz");
	return 0;
}