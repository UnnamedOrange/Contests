#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 300000
using namespace std;
typedef long long LL;
int m, n, ans[N + 5], father[N + 5], tp, a[N + 5], mx = 0, tmp, cnt = 0, vis[N + 5];
bool color[N + 5], pf[N + 5];
void solve1() {
	for (int i = n - 1; i; i--) {
		bool flag = 1;
		int x = a[i];
		if (vis[x]) {
			if (pf[x + x]) {
				for (int j = i + 1; j <= tmp; j++) vis[a[j]] = 0;
				vis[x] = 1;
				ans[++cnt] = i;
				tmp = i;
				continue;
			}
			continue;
		}
		for (int j = 1; j <= tp && flag; j++)
			if (j * j >= x && vis[j * j - x])
				flag = 0;
		if (flag) vis[x] = 1; else {
			for (int j = i + 1; j <= tmp; j++) vis[a[j]] = 0;
			ans[++cnt] = i;
			tmp = i;
			vis[x] = 1;
		}
	}
	for (int i = 1; i <= (cnt >> 1); i++) swap(ans[i], ans[cnt - i + 1]);
	printf("%d\n", cnt);
	for (int i = 1; i <= cnt; i++) printf("%d ", ans[i]); puts("");
}
int getfather(int u) { 
	if (u == father[u]) return u;
	int tmp = father[u]; 
	father[u] = getfather(tmp);
	if (tmp != father[u]) color[u] ^= color[tmp];
	return father[u];
}
bool merge(int u, int v) {
	int fu = getfather(u), fv = getfather(v),
		 cu = (color[u] ^ color[fu]), cv = (color[v] ^ color[fv]);
	if (fu != fv) {
		if (cu != cv) {
			father[fu] = fv;
			color[fu] ^= color[fv];
			return 1;
		}
		color[fu] ^= 1 ^ color[fv];
		father[fu] = fv;
		return 1;
	}
	if (cu != cv) return 1;
	return 0;
}
void solve2() {
	for (int i = n - 1; i; i--) {
		int x = a[i];
		if (vis[x]) {
			if (pf[x + x]) {
				if (vis[x] == 1) { vis[x]++; continue; }
				for (int j = i + 1; j <= tmp; j++) vis[a[j]] = 0, father[a[j]] = a[j], color[a[j]] = 0;
				vis[x] = 1;
				ans[++cnt] = i;
				tmp = i;
				continue;
			}
			continue;
		}
		bool flag = 1;
		father[x] = x, color[x] = 0;
		for (int j = 1; j <= tp && flag; j++)
			if (j * j >= x && vis[j * j - x]) 
				flag = merge(x, j * j - x);
		if (flag) vis[x] = 1; else {
			for (int j = i + 1; j <= tmp; j++) vis[a[j]] = 0, father[a[j]] = a[j], color[a[j]] = 0;
			ans[++cnt] = i;
			tmp = i;
			vis[x] = 1;
		}
	}
	for (int i = 1; i <= (cnt >> 1); i++) swap(ans[i], ans[cnt - i + 1]);
	printf("%d\n", cnt + 1);
	for (int i = 1; i <= cnt; i++) printf("%d ", ans[i]); puts("");
}
int main() {
	freopen("division.in", "r", stdin);
	freopen("division.out", "w", stdout);
	int k;
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++) {
		scanf("%d", a + i);
		mx = max(mx, a[i]);
	}
	while (tp * tp <= 2 * mx) pf[tp * tp] = 1, tp++;
	vis[a[n]] = 1;
	father[a[n]] = a[n];
	tmp = n;
	if (k == 1) solve1(); else solve2();
	return 0;
}
