#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 1e6 + 5;

char s[N];
int n, k; 

int main() {
	freopen("trans.in", "r", stdin);
	freopen("trans.out", "w", stdout);

	while (cin >> n >> k) {
		scanf("%s", s + 1);
		for (int i = 1; i <= n && k; i ++) {
			if (s[i] == '2' && s[i + 1] == '3') {
				if (i & 1) s[i + 1] = '2', k --;
				else if (s[i - 1] == '2') s[i] = k & 1 ? '3' : '2', k = 0;
				else s[i] = '3', k --;
			}
		}
		printf("%s\n", s + 1);
	}
	return 0;
}
