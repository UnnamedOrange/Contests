#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

LL f[61] = {0, 1};

int main() {
	freopen("fibonacci.in", "r", stdin);
	freopen("fibonacci.out", "w", stdout);
	for (int i = 2; i <= 60; i++) f[i] = f[i - 1] + f[i - 2];
	int n;
	scanf("%d", &n);
	while (n--) {
		LL a, b;
		scanf("%lld%lld", &a, &b);
		int x = 60, y = 60;
		while (a != b) {
			if (a > b) swap(a, b), swap(x, y);
			while (f[y] >= b) y--;
			b = b - f[y];
		}
		printf("%lld\n", a);
	}
}

