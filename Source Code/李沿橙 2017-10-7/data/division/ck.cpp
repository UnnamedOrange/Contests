#include <bits/stdc++.h>
using namespace std;

int n;
bool in[200000];
int vis[200000];

void dfs(int x) {
	if (!vis[x]) vis[x] = 2;
	for (int i = 1, y; i * i < 200000; i++) {
		if (i * i > x && in[(y = i * i - x)]) {
			if (vis[y]) {
				if (vis[y] ^ vis[x] ^ 1) {
					exit(1);
				}
			}
			else {
				vis[y] = vis[x] ^ 1;
				dfs(y);
			}
		}
	}
}


int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		in[x] = 1;
	}
	for (int i = 1; i < 200000; i++) {
		if (in[i] && !vis[i]) dfs(i);
	}
	puts("ok");
	return 0;
}
