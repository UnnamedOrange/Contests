#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;
#define fir first
#define sec second
#define INF 0x3f3f3f3f
#define MAXN 40005
#define TOP 18

int n, K, m, cnt = 0;
bool a[MAXN];
int dis[18][MAXN], b[70];
pii p[18];

queue <int> q;

void bfs(pii st) {
	for (int i = 0; i < MAXN; i++) dis[st.fir][i] = INF;
	q.push(st.sec);
	dis[st.fir][st.sec] = 0;
	while (!q.empty()) {
		int x = q.front(); q.pop();
		for (int i = 1; i <= m; i++) {
			if (x - b[i] >= 0 && dis[st.fir][x - b[i]] > dis[st.fir][x] + 1) {
				dis[st.fir][x - b[i]] = dis[st.fir][x] + 1;
				q.push(x - b[i]);
			}
			if (x + b[i] <= n && dis[st.fir][x + b[i]] > dis[st.fir][x] + 1) {
				dis[st.fir][x + b[i]] = dis[st.fir][x] + 1;
				q.push(x + b[i]);
			}
		}
	}
}

int dp[1 << 18];

int solve(int mask) {
	if (dp[mask] != -1) return dp[mask];
	if (mask == 0) return 0;
	int &ret = dp[mask]; ret = INF;
	int x = 0; while (!(mask & (1 << x))) x++;
	for (int i = x + 1; i < 2 * K; i++)
		if (mask & (1 << i)) ret = min(ret, solve(mask ^ (1 << x) ^ (1 << i)) + dis[x][p[i].sec]);
	return ret;
}

int main() {
//	freopen("starlit.in", "r", stdin);
//	freopen("starlit.out", "w", stdout);
	scanf("%d %d %d", &n, &K, &m);
	for (int i = 1, x; i <= K; i++) scanf("%d", &x), a[x] = true;
	for (int i = 1; i <= m; i++) scanf("%d", &b[i]);
	for (int i = 0; i <= n; i++) if (a[i] != a[i + 1]) p[cnt] = pii(cnt, i), cnt++;
	for (int i = 0; i < cnt; i++) bfs(p[i]);
	memset(dp, -1, sizeof dp);
	int ans = solve((1 << cnt) - 1);
	assert(ans != INF);
	printf("%d\n", ans);
	return 0;
}


