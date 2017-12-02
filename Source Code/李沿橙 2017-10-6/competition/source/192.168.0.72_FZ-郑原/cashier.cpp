#include <cstdio>
#include <algorithm>
#include <iostream>

using namespace std;

int A[24], B[24], C[24];
int T; 

int main() {
	freopen("cashier.in", "r", stdin);
	freopen("cashier.out", "w", stdout);
	
	scanf("%d", &T);
	while (T --) {
		int tok = 1; 
		for (int i = 0; i < 24; i ++) scanf("%d", A + i);
		for (int i = 0; i < 24; i ++) {
			scanf("%d", B + i);
			C[i] = 0;
		}
		for (int i = 0; i < 24; i ++) 
			for (int j = 0; j <= 8; j ++) 
				C[(i + j) % 24] += B[i];
		for (int i = 0; i < 24; i ++) {
			C[i] -= A[i]; 
			if (C[i] < 0) tok = 0;
		}
		if (!tok) {printf("-1\n"); break ;}
		int ans = 0;
		for (int i = 0; i < 24; i ++) C[i] = 0;
		for (int i = 0; i < 24; i ++) {
			A[i] -= C[i];
			for (int j = i; j >= i - 7 && A[i] > 0; j --) {
				int p = (j + 24) % 24;
				if (A[i] >= B[p]) {
					for (int g = p; g <= p + 7; g ++) C[g % 24] += B[p];
					A[i] -= B[p], ans += B[p], B[p] = 0;
				} else {
					for (int g = p; g <= p + 7; g ++) C[g % 24] += A[i]; 
					B[p] -= A[i], ans += A[i], A[i] = 0;
				}
			}
		}
		printf("%d\n", ans);
	}
	return 0; 
}
