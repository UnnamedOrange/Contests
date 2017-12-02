#include <bits/stdc++.h>
using namespace std;

const int N  = 3e5 + 8;
int top[N], bot[N], dep[N];
int realBot(int x) {
	if (x == bot[x]) return x;
	int ob = bot[x];
	bot[x] = realBot(ob);
	dep[x] += dep[ob];
	return bot[x];
}
	
int main() {
	freopen("cube.in", "r", stdin);
	freopen("cube.out", "w", stdout);
	int p, n = 30000;
	for (int i = 1; i <= n; i++)
		top[i] = bot[i] = i;
	cin >> p;
	while (p--) {
		int x, y; char op[10];
		scanf("%s%d", op, &x);
		if (op[0] == 'M') {
			scanf("%d", &y);
			int bx = realBot(x), by = realBot(y), ty = top[by];
			bot[bx] = ty; 
			dep[bx] = 1;
			top[by] = top[bx];
		}
		else {
			realBot(x);
			printf("%d\n", dep[x]);
		}
	}
	fclose(stdin); fclose(stdout);
	return 0;
}