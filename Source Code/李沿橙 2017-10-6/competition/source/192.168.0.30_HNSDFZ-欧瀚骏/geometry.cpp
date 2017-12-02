#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 100000
using namespace std;
bool check(int px, int py, int ax, int ay) { return ax * 1ll * ay <= py * 1ll * ax + ay * 1ll * px; }
int x[N + 5], y[N + 5], n, m;
int main() {
	freopen("geometry.in", "r", stdin);
	freopen("geometry.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", x + i);
	for (int i = 1; i <= n; i++) scanf("%d", y + i);
	sort(x + 1, x + 1 + n), sort(y + 1, y + 1 + n);
	scanf("%d", &m);
	while (m--) {
		int l = 1, r = n, px, py;
		scanf("%d%d", &px, &py);
		if (!check(px, py, x[1], y[1])) { puts("0"); continue; }
		while (l < r) {
			int mid = l + r + 1 >> 1;
			if (check(px, py, x[mid], y[mid])) l = mid; else r = mid - 1;
		}
		printf("%d\n", l);
	}
	return 0;
}
