#include<cstdio>
int n;
int ans;
void dfs(int x, int y) {
	if(y == 0 && x == 0) {
		ans++;
		return;
	}
	if(y) dfs(x + 1, y - 1);
	if(x) dfs(x - 1, y);
}
int main() {
	freopen("stack.in", "r", stdin);
	freopen("stack.out", "w", stdout);
	scanf("%d", &n);
	if(n < 16) dfs(0, n);
	printf("%d\n", ans % 7);
	return 0;
}
