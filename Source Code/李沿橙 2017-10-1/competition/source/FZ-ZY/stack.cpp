#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1000 + 5;

int f[N << 1][N];
int n;

void work() {
	f[1][1] = 1;
	int tot = n << 1;
	for (int i = 2; i <= tot; i ++) {
		int s = (i >> 1) + (i & 1); 
		for (int j = s; j <= i && j <= n; j ++) {
			f[i][j] = f[i - 1][j - 1] + f[i - 1][j];
			f[i][j] -= (f[i][j] >= 7 ? 7 : 0);
		}
	}
	printf("%d\n", f[tot][n]);
}

int main() {
	freopen("stack.in", "r", stdin);
	freopen("stack.out", "w", stdout);
	scanf("%d", &n);
	work();
	return 0;
}
