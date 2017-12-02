#include <cstdio>
#include <algorithm>
#include <iostream>

using namespace std;

const int N = 400 + 5;
const int ml = 1e6 + 5;

int A[N][N], tk[ml]; 
int n, m, k;
long long ans;

int inc(int a, int b) {
	return a + b - (a + b >= k ? k : 0);
}

int main() {
	freopen("rally.in", "r", stdin);
	freopen("rally.out", "w", stdout);

	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= n; i ++) 	
		for (int j = 1; j <= m; j ++) 
			scanf("%d", &A[i][j]);
	for (int i = 1; i <= n; i ++) 
		for (int j = 1; j <= m; j ++) 
			A[i][j] = inc(A[i - 1][j], A[i][j]);
	for (int i = 1; i <= n; i ++) 
		for (int j = 1; j <= m; j ++) 
			A[i][j] = inc(A[i][j - 1], A[i][j]);
	for (int len = 1; len <= m; len ++) {
		for (int j = len; j <= m; j ++) {
			tk[0] = 1;
			for (int i = 1; i <= n; i ++) {
				int key = inc(A[i][j], k - A[i][j - len]);
				ans += tk[key];
				tk[key] ++;
			}
			for (int i = 1; i <= n; i ++) {
				int key = inc(A[i][j], k - A[i][j - len]);
				tk[key] --;
			}
		}
	} 
	printf("%lld\n", ans);
	return 0;
}
