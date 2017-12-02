#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 40000 + 5;

int n, k, m, ans;
int A[N], cf[N], chs[N]; 

int main() {
	freopen("starlit.in", "r", stdin);
	freopen("starlit.out", "w", stdout);

	scanf("%d%d%d", &n, &k, &m); ans = n * m;
	for (int i = 1; i <= k; i ++) {
		int x; scanf("%d", &x);
		A[x] = 1;
	}
	for (int i = 1; i <= m; i ++)
		scanf("%d", &chs[i]);
	if (n == 2) {
		if (k == 0) printf("0\n");
		else if (k == 1 && (chs[1] | chs[2]) & 1) printf("1\n");
		else if (k == 2 && (chs[1] == 2 || chs[2] == 2)) printf("1\n");
		else printf("0\n");
		return 0;
	} 
	for (int j = 1; j <= m; j ++) {
		int cnt = 0, s = 0;
		for (int i = 1; i <= n; i ++) cf[i] = 0;
		for (int i = 1; i <= n - chs[j] + 1; i ++) {
			s ^= cf[i];
			if (s ^ A[i] == 1) {
				cf[i] ^= 1; s ^= 1; 
				cnt ++; cf[min(i + chs[j], 40000 + 1)] ^= 1;
			}
		}
		for (int i = n - chs[j] + 2; i <= n; i ++) {
			s ^= cf[i];
			if (s ^ A[i] == 1) cnt = n * m;
		}
		ans = min(ans, cnt);
	}
	printf("%d\n", ans);
	return 0;
}
