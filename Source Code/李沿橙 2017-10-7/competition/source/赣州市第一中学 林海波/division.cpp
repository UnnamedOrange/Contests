#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>

const int maxn = 131100;

using namespace std;

int n, K;
int a[maxn];
int f[maxn];
int num[maxn];
int col[maxn];
vector<int> G[maxn];

bool color(int p, int c);

int main()
{
	freopen("division.in", "r", stdin);
	freopen("division.out", "w", stdout);
	memset(f, 0x7f, sizeof f);
	scanf("%d%d", &n, &K);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	if (K == 1)
	{
		f[0] = 0;
		for (int i = 0; i <= n; i++)
		{	
			for (int j = i + 1; j <= n; j++)
			{
				for (int k = i + 1; k < j; k++)
				{
					int sq = sqrt(a[k] + a[j]);
					if (sq * sq == (a[k] + a[j]))
						goto a;
				}
				f[j] = min(f[j], f[i] + 1);
			}
			a:;
		}
		printf("%d\n", f[n]);
		for (int i = 1; i < n; i++)
			if (f[i + 1] != f[i])
				printf("%d ", i);
		printf(" \n");
	}
	else
	{
		f[n + 1] = 0;
		for (int i = n + 1; i > 0; i--)
		{
			for (int j = i - 1; j > 0; j--)
			{
				G[j].clear();
				for (int k = i - 1; k > j; k--)
				{
					int sq = sqrt(a[k] + a[j]);
					if (sq * sq == (a[k] + a[j]))
					{
						G[k].push_back(j);
						G[j].push_back(k);
					}
				}
				memset(col, 0, sizeof col);
				for (int l = i - 1; l >= j; l--)
					if (col[l] == 0)
						if (!color(l, 1))
							goto b;
				f[j] = min(f[j], f[i] + 1);
			}
			b:;
		}
		printf("%d\n", f[1]);
		for (int i = 1; i < n; i++)
			if (f[i + 1] != f[i])
				printf("%d ", i);
		printf(" \n");
	}
	return 0;
}

bool color(int p, int c)
{
	if (col[p] != 0)
		if (col[p] != c)
			return false;
		else
			return true;
	col[p] = c;
	for (int i = 0; i < G[p].size(); i++)
		if (!color(G[p][i], 3 - c))
			return false;
	return true;
}

