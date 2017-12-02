#include <cstdio>
#include <algorithm>
#include <iostream>

using namespace std;

const int N = 2e6 + 5;

int A[N], n, k, ud;

bool check(int a, int b) {
	if (ud == 1) return b - k >= a;
	else return a - k >= b;
}

int main() {
	freopen("wave.in", "r", stdin);
	freopen("wave.out", "w", stdout);

	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i ++) 	
		scanf("%d", A + i);
	int now = A[1], cnt = 1; ud = 1;
	for (int i = 2; i <= n; i ++) 
		if (check(now, A[i])) {
			now = A[i], cnt ++;
			ud ^= 1;
		} else {
			if (ud == 1) now = min(now, A[i]);
			else now = max(now, A[i]);
		}
	printf("%d\n", cnt);
	return 0;
}

