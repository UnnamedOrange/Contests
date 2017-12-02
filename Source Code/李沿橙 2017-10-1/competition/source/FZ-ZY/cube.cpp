#include <cstdio>
#include <algorithm>
#include <iostream>

using namespace std;

const int N = 30000 + 5;

int nxt[N], lst[N], fa[N];

int find(int x) {
	return fa[x] == 0 ? x : fa[x] = find(fa[x]);
}

int main() {
	freopen("cube.in", "r", stdin);
	freopen("cube.out", "w", stdout);

	int q; 
	while (q --) {
		string c; cin >> c; 
		//while (c != 'M' && c != 'C') c = getchar();
		if (c == "M") {
			int a, b; scanf("%d%d", &a, &b);
			if (find(a) == find(b)) continue ;
			while (nxt[a]) a = nxt[a];
			while (lst[b]) b = lst[b];
			nxt[a] = b; lst[b] = a;
		} else {
			int x; scanf("%d", &x);
			int cnt = 0; 
			while (nxt[x]) {
				x = nxt[x];
				cnt ++;
			}
			printf("%d\n", cnt);
		}
		//printf("%d\n", cnt);
	}
	return 0; 
}
