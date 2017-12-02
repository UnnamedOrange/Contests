#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 1000000
using namespace std;
typedef long long LL;
LL f[N + 5], a, b;
int m, n;
int main() {
	freopen("fibonacci.in", "r", stdin);
	freopen("fibonacci.out", "w", stdout);
	f[0] = f[1] = 1;
	n = 1;
	while (f[n] < 1e12) f[n + 1] = f[n] + f[n - 1], n++;
	scanf("%d", &m);
	while (m--) {
		scanf("%lld%lld", &a, &b);
		int fa = 0, fb = 0;
		for (int i = 1; i <= n; i++) {
			if (f[i - 1] < a) fa = i;
			if (f[i - 1] < b) fb = i;
		} 
		while (a != b) {
			if (a < b) swap(a, b), swap(fa, fb);
			a -= f[fa - 1];
			while (f[fa - 1] >= a) fa--;
		}
		printf("%lld\n", a);
	}
	return 0;
}
