#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 1000000
using namespace std;
char s[N + 5];
int n, k;
int main() {
	freopen("trans.in", "r", stdin);
	freopen("trans.out", "w", stdout);
	while (scanf("%d%d", &n, &k) == 2) {
		scanf("%s", s);
		if (k == 0) { printf("%s\n", s); continue; }
		if (n <= 2) {
			if (s[0] == '2' && s[1] == '3') s[1] = '2';
			printf("%s\n", s);
			continue;
		}
		for (int i = 0; i < n - 1 && k; i++)
			if (s[i] == '2' && s[i + 1] == '3') {
				if (i & 1) {
					if (s[i - 1] == '2') {
						if (k & 1) s[i] = '3';
						k = 0;
						break;
					}
					s[i] = '3', k--;
				} else s[i + 1] = '2', k--;
			}
		printf("%s\n", s);
	}
	return 0;
}
