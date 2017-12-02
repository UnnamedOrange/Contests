#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

LL f[61] = {0, 1};

LL a, b; int x, y;

void getf() {
	while (f[y] >= b) y--;
	b = b - f[y];
}

int main() {
	//freopen("fibonacci.in", "r", stdin);
	//freopen("fibonacci.out", "w", stdout);
	for (int i = 2; i <= 60; i++) f[i] = f[i - 1] + f[i - 2];
	int n;
	scanf("%d", &n);
	while (n--) {
		scanf("%lld%lld", &a, &b);
		x = 60, y = 60;
		while (a != b) {
			if (a > b) swap(a, b), swap(x, y);
			getf();
		}
		printf("%lld\n", a);
	}
	cerr << clock() << endl;
	return 0;
}

