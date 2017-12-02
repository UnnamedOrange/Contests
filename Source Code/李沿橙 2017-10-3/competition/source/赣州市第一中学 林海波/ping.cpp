#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>

const int maxn = 100010;
const int maxk = 300010;

using namespace std;

int n, m, k, u, v, sizes;
int dep[maxn];
int fa[maxn];
vector<int> G[maxn];
vector<int> B[maxk];

void dfs_tree(int uv, int dep, int fa);
void LCA(int u, int v);
void unions();

int main()
{
	freopen("ping.in", "r", stdin);
	freopen("ping.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++)
	{
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs_tree(1, 0, -1);
	sizes = 0;
	scanf("%d", &k);
	for (int i = 0; i < k; i++)
	{
		scanf("%d%d", &u, &v);
		B[sizes].push_back(u);
		if (u != v)
			B[sizes].push_back(v);
		LCA(u, v);
		unions();
		sizes++;
	}
	printf("%d\n", sizes);
	for (int i = 0; i < sizes; i++)
		printf("%d ", B[i][0]);
	return 0;
}

void dfs_tree(int uv, int d, int f)
{
	dep[uv] = d;
	fa[uv] = f;
	for (int i = 0; i < G[uv].size(); i++)
		if (G[uv][i] != f)
			dfs_tree(G[uv][i], d + 1, uv);
}

void LCA(int u, int v)
{
	while (dep[u] > dep[v])
	{
		u = fa[u];
		B[sizes].push_back(u);
	}
	while (dep[u] < dep[v])
	{
		v = fa[v];
		B[sizes].push_back(v);
	}
	while (u != v)
	{
		u = fa[u];
		v = fa[v];
		B[sizes].push_back(u);
		if (u != v)
			B[sizes].push_back(v);
	}
}

void unions()
{
	vector<int> T;
	for (int i = 0; i < sizes; i++)
	{
		T.clear();
		for (int j = 0; j < B[sizes].size(); j++)
			for (int k = 0; k < B[i].size(); k++)
				if (B[sizes][j] == B[i][k])
					T.push_back(B[sizes][j]);
		if (!T.empty())
		{
			B[i].clear();
			B[sizes].clear();
			for (int j = 0; j < T.size(); j++)
				B[i].push_back(T[j]);
			sizes--;
			break;
		}
	}
}

