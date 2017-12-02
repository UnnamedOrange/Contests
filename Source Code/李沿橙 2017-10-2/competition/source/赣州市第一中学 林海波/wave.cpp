#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>

const int maxn = 2000010;
const int inf = 1000000000;

using namespace std;

int n, k;
int maxf = 0;
int maxg = 0;
int a[maxn];
int d[maxn];
int f[maxn];
int g[maxn];

int fBound(int beg, int end, int num);
int gBound(int beg, int end, int num);

int main()
{
	freopen("wave.in", "r", stdin);
	freopen("wave.out", "w", stdout);
	memset(f, 0x7f, sizeof f);
	memset(g, -1, sizeof g);
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++)
	{
		int F = fBound(0, maxf, a[i] - k) + 1;
		int G = gBound(0, maxg, a[i] + k) + 1;
		d[i] = 1;
		d[i] = max(d[i], F);
		d[i] = max(d[i], G);
		g[F] = max(g[F], a[i]);
		f[G] = min(f[G], a[i]);
		maxf = max(maxf, G);
		maxg = max(maxg, F);
	}
	/*for (int i = 1; i <= n; i++)
		printf("%d ", d[i]);
	printf("\n");
	for (int i = 1; i <= n; i++)
		printf("%d ", f[i]);
	printf("\n");
	for (int i = 1; i <= n; i++)
		printf("%d ", g[i]);
	printf("\n");*/
	printf("%d\n", d[n]);
	return 0;
}

int fBound(int beg, int end, int num)
{
	/*if (beg == end && num >= f[beg])
		return beg;
	else
		return -1;
	int mid = (beg + end) / 2;
	if (f[mid] == 0x7f7f7f7f || f[mid] < num)
		return fBound(beg, mid, num);
	if (f[mid] >= num)
		return fBound(mid, end, num);*/
	int minn = inf;
	int ans = -1;
	for (int i = end; i >= 1; i -= 2)
		if (num >= f[i])
			ans = max(ans, i);
	return ans;
}

int gBound(int beg, int end, int num)
{
	/*if (beg == end && num <= g[beg])
		return beg;
	else
		return 0;
	int mid = (beg + end) / 2;
	if (g[mid] == -1)
		return gBound(beg, mid, num);
	else
		return gBound(mid, end, num);*/
	int maxm = -1;
	int ans = 0;
	for (int i = end; i >= 2; i -= 2)
		if (num <= g[i])
			ans = max(ans, i);
	return ans;
}

