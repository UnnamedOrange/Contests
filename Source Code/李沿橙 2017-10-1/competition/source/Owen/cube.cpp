#include <cstdlib>
#include <queue>
#include <vector>
#include <ctime>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 30000
using namespace std;
int c[N + 5], size[N + 5], father[N + 5];
char s[N + 5];
int getfather(int x, int &dep) { dep += c[x]; return x == father[x] ? x : getfather(father[x], dep); }
int main() {
	freopen("cube.in", "r", stdin);
	freopen("cube.out", "w", stdout);
	int d, x, y, q;
	for (int i = 1; i <= N; i++) father[i] = i, size[i] = 1, c[i] = 0;
	scanf("%d", &q);
	while (q--) {
		scanf("%s", s);
		if (s[0] == 'C') { scanf("%d", &x); d = 0; getfather(x, d); printf("%d\n", d); }
		if (s[0] == 'M') { 
			scanf("%d%d", &x, &y); 
			x = getfather(x, d), y = getfather(y, d); 
			if (size[x] > size[y]) {
				father[y] = x;
				c[x] += size[y], c[y] -= size[y];
				size[x] += size[y];
			} else {
				father[x] = y;
				c[x] += size[y];
				size[y] += size[x];
			}
		}
	}
	return 0;
}
