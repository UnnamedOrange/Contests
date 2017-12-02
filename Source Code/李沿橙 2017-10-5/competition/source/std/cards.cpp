#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;
#define rep(i, l, r) for (int i = l; i <= r; i++)
#define drep(i, r, l) for (int i = r; i >= l; i--)
typedef long long ll;
const int N = 1008;
int n, T, a[N], g[N][N], sg[N][N], m, cnt[N], mex[N];
double f[N][N];
int gcd(int x, int y)
{
	return !y ? x : gcd(y, x % y);
}
void init(int n)
{
	rep(i, 0, n)
		rep(j, 0, n) g[i][j] = gcd(i, j);
}
bool check()
{
	int gg=0;
	for (int i=1;i<=n;i++) gg=g[gg][a[i]];
	if (gg==1) return false;
	if (n&1) printf("%.9lf 1\n",1);
	else printf("%.9lf 0\n",0);
	return true;
} 
void solve()
{
	if (check()) return ;
	memset(sg, 0, sizeof(sg));
	memset(f, 0, sizeof(f));
	memset(mex, 0, sizeof(mex));
	rep(j, 0, m) sg[n][j] = 0, f[n][j] = 0; 
	sg[n][1] = 1; f[n][1] = 1;
	int p = 0;
	drep(i, n - 1, 0)
		rep(x, 0, m)
		{
			if (x == 1) {sg[i][x] = 1; f[i][x] = 1; continue;}
			memset(cnt, 0, sizeof(cnt));
			rep(j, 1, n) cnt[g[x][a[j]]]++;
			if (x && i && cnt[x] < i) continue;
			if (x) cnt[x] -= i; ++p;
			rep(y, 0, m) 
			{
				if (cnt[y]) mex[sg[i + 1][y]] = p, f[i][x] += (double)cnt[y] / (n - i) * (1 - f[i + 1][y]);
			}
			for (sg[i][x] = 0; mex[sg[i][x]] == p; sg[i][x]++);
		}
	if (sg[0][0])
		printf("%.9lf 1\n", f[0][0]);
	else
		printf("%.9lf 0\n", f[0][0]);
}
int main()
{
	freopen("cards.in", "r", stdin);
	freopen("cards.out", "w", stdout);
	init(1000);
	scanf("%d", &n); m = 0;
	rep(i, 1, n) scanf("%d", &a[i]), m = max(m, a[i]);
	solve();
	fclose(stdin); fclose(stdout);
	return 0;
}
