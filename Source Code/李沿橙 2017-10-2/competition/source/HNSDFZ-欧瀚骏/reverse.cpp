#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#define N 100000
using namespace std;
char s[N + 5];
int a[N + 5], b[2], c[2], ans, n;
int main() {
	freopen("reverse.in", "r", stdin);
	freopen("reverse.out", "w", stdout);
	scanf("%s", s);
	n = strlen(s);
	for (int i = 0; i < n; i++) a[i + 1] = s[i] - 48, c[a[i + 1]]++;
	a[++n] = 1, c[1]++;
	ans = c[1] - 1;
	for (int i = 1; i <= n; i++) {
		if (a[i]) ans = min(ans, c[0] - b[0] + b[1]);
		b[a[i]]++;
	}
	printf("%d\n", ans);
	return 0;
}
