#include <bits/stdc++.h>
using namespace std;

int ch;
inline void read(int &a) {
	a = 0;
	while (ch < '0' || ch > '9') ch = getchar();
	while (ch >= '0' && ch <= '9') a = a * 10 + ch - '0', ch = getchar();
}

#define MAXN 300005

int n, m;
int a[MAXN];
vector <int> b[MAXN];

int main() {
//	freopen("color.in", "r", stdin);
//	freopen("color.out", "w", stdout);
	read(n); read(m);
	for (int i = 1; i <= n; i++) {
		read(a[i]);
		b[a[i]].push_back(i);
	}
	for (int i = 1; i <= n; i++) sort(b[i].begin(), b[i].end());
	for (int i = 1, x, l, r, c; i <= m; i++) {
		read(x);
		if (x == 1) {
			read(l); read(r); read(c);
			printf("%d\n", (int)(upper_bound(b[c].begin(), b[c].end(), r) - lower_bound(b[c].begin(), b[c].end(), l)));
		}
		else {
			read(x);
			if (a[x] != a[x + 1]) {
				(*lower_bound(b[a[x]].begin(), b[a[x]].end(), x))++;
				(*lower_bound(b[a[x + 1]].begin(), b[a[x + 1]].end(), x + 1))--;
				swap(a[x], a[x + 1]);
			}
		}
	}
	cerr << clock() << endl;
	return 0;
}

