#include <cstdio>
#include <cstdlib>
#include <queue>
using namespace std;

#define N 33

struct edge{
	int t, n, l;
}e[N * N];

int h[N];
int tote;

void adde(int u, int v, int l) {
	e[++tote].t = v;
	e[tote].l = l;
	e[tote].n = h[u];
	h[u] = tote;
	return ;
}

int d[N];
bool inq[N];

bool spfa() {
	queue<int> Q;
	for (int i = 0; i <= 24; i++) d[i] = -1e9, inq[i] = false;
	d[0] = 0; inq[0] = true; Q.push(0);
	while (!Q.empty()) {
		int u = Q.front(); Q.pop(); inq[u] = false;
		if (d[u] > 1000) return false;
		for (int i = h[u]; i; i = e[i].n) {
			int v = e[i].t, l = e[i].l;
			if (d[v] < d[u] + l) {
				d[v] = d[u] + l;
				if (!inq[v]) {
					inq[v] = true;
					Q.push(v);
				}
			}
		}
	}
	return true;
}

int a[30], b[30];

bool solve(int ans) {
	for (int i = 0; i <= 24; i++) h[i] = 0;
	tote = 0;
	for (int i = 9; i <= 24; i++) adde(i - 8, i, a[i]);
	for (int i = 1; i <= 8; i++) adde(i + 16, i, a[i] - ans);
	for (int i = 1; i <= 24; i++) adde(i - 1, i, 0);
	for (int i = 1; i <= 24; i++) adde(i, i - 1, -b[i]);
	adde(0, 24, ans); adde(24, 0, -ans);
	return spfa();
}

int main(int argc, char ** argv) {
	freopen("cashier.in", "r", stdin);
	freopen("cashier.out", "w", stdout);
	int test;
	scanf("%d", &test);
	for (int i = 1; i <= test; i++) {
		for (int i = 1; i <= 24; i++) scanf("%d", &a[i]);
		for (int i = 1; i <= 24; i++) scanf("%d", &b[i]);
		int ans = 0;
		while (true) {
			if (++ans > 1000) {
				ans = -1; break;
			}
			if (solve(ans)) break;
		}
		printf("%d\n", ans);
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
