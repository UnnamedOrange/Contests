#include <bits/stdc++.h>
using namespace std;

#define MAXN 300005

int n, m;
int a[MAXN];
vector <int> b[MAXN];

int main() {
	freopen("color.in", "r", stdin);
	freopen("color.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", a + i);
		b[a[i]].push_back(i);
	}
	for (int i = 1; i <= n; i++) sort(b[i].begin(), b[i].end());
	for (int i = 1, x, l, r, c; i <= m; i++) {
		scanf("%d", &x);
		if (x == 1) {
			scanf("%d%d%d", &l, &r, &c);
			printf("%d\n", (int)(upper_bound(b[c].begin(), b[c].end(), r) - lower_bound(b[c].begin(), b[c].end(), l)));
		}
		else {
			scanf("%d", &x);
			if (a[x] != a[x + 1]) {
				(*lower_bound(b[a[x]].begin(), b[a[x]].end(), x))++;
				(*lower_bound(b[a[x + 1]].begin(), b[a[x + 1]].end(), x + 1))--;
				swap(a[x], a[x + 1]);
			}
		}
	}
	return 0;
}

