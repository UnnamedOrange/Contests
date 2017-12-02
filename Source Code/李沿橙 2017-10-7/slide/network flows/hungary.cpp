/* Never Say Die. */
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>
#include <ctime>
#include <cstdlib>
using namespace std;

#define MAXN 2012345

int n, dfn = 0, ans = 0;
int G[MAXN], fir[MAXN], ecnt = 0;
int vis[MAXN], mat[MAXN];

bool find(int x) {
	for (int i = fir[x]; G[i]; i++) if (vis[G[i]] != dfn) {
		vis[G[i]] = dfn;
		if (!mat[G[i]] || find(mat[G[i]])) return mat[G[i]] = x, 1;
	}
	return 0;
}

int main() {
	scanf("%d", &n);
	for (int i = 1, c, x; i <= n; i++) {
		scanf("%d", &c); 
		for (int j = 1; j <= c; j++) scanf("%d", &x), G[ecnt++] = x;
		fir[i + 1] = ++ecnt;
	}
	for (int i = 1; i <= n; i++) {
		dfn++;
		ans += find(i);
	}
	printf("%d\n", ans);
	return 0;
}
