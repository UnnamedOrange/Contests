#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>

const int maxn = 310;

using namespace std;

int n;
int a[maxn];
bool vis[maxn] = { false };

pair<double, bool> dfs(int g = 0);
int gcd(int a, int b);

int main()
{
	freopen("cards.in", "r", stdin);
	freopen("cards.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &a[i]);
	pair<double, bool> p = dfs();
	if (p.second)
		printf("%.9lf %.9lf\n", p.first, 1.000000000);
	else
		printf("%.9lf %.9lf\n", p.first, 0.000000000);
	return 0;
}

pair<double, bool> dfs(int g)
{
	int cnt = 0;
	double rand_num = 0;
	bool best_num = false;
	for (int i = 0; i < n; i++)
		if (!vis[i])
		{
			cnt++;
			int gcd_num = gcd(g, a[i]);
			if (gcd_num != 1)
			{
				vis[i] = true;
				pair<double, bool> p = dfs(gcd_num);
				rand_num += (1 - p.first);
				best_num |= !p.second;
				vis[i] = false;
			}
		}
	if (cnt == 0)
		return make_pair(0.0, false);
	else
		return make_pair(rand_num / cnt, best_num);
}

int gcd(int a, int b)
{
	return (b == 0 ? a : gcd(b, a % b));
}

