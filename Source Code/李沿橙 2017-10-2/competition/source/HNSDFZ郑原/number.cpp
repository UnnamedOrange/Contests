#include <cstdio>
#include <algorithm>
#include <iostream>

using namespace std;

int t1[10], ans, t2[10];

int main() {
	freopen("number.in", "r", stdin);
	freopen("number.out", "w", stdout);

	int x; scanf("%d", &x); 
	for (int i = 1; i <= x; i ++) {
		for (int j = 0; j < i; j ++) {
			int m = i, n = j;
			//int c1 = 0, c2 = 0;
			for (int ij = 0; ij <= 9; ij ++) t1[ij] = t2[ij] = 0;
			while (m) {t1[m % 10] = 1; m /= 10;}
			while (n) {t2[n % 10] = 1; n /= 10;}
			int add = 1;
			for (int ij = 0; ij < 10; ij ++) 
				if (t1[ij] != t2[ij])
					add = 0;
			//if (add) printf("%d %d\n", j, i);
			ans += add;
		}
	}
	printf("%d\n", ans);
	return 0;
}
