#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;
const int N = 111111;
const int inf = 1 << 20;
int fa[N][20], n, m, maximum[N][20], leaf[N], weight[N];
int dist[N],dep[N];
pair<int, int> dp[N], down[N];
vector<int> adj[N];

void update(pair<int, int> &x, pair<int, int> y) {
	if (x.first != y.first) {
		x = min(x, y);
	} else {
		x = max(x, y);
	}
}

void build() {
	vector<int> queue;
	queue.push_back(1);
	fa[1][0] = 0;
	dep[1] = 1;
	dist[1] = weight[1];
	for (int head = 0; head < (int)queue.size(); head++) {
		int now = queue[head];
		for (int i = 0; i < (int)adj[now].size(); i++) {
			queue.push_back(adj[now][i]);
			dep[adj[now][i]] = dep[now] + 1;
			dist[adj[now][i]] = dist[now] + weight[adj[now][i]];
		}
	}

	for (int j = 1; j <= 18; j++) {
		for (int i = 1; i <= n; i++) {
			fa[i][j] = fa[fa[i][j - 1]][j - 1];
			maximum[i][j] = max(maximum[i][j - 1], maximum[fa[i][j - 1]][j - 1]);
		}
	}

	for (int i = (int)queue.size() - 1; i >= 0; i--) {
		int x = queue[i];
		update(down[fa[x][0]], make_pair(down[x].first + weight[fa[x][0]], max(down[x].second, weight[fa[x][0]])));
	}
}

void DP() {
	vector<int> queue;
	queue.push_back(1);	
	update(dp[1], down[1]);
	for (int head = 0; head < (int)queue.size(); head++) {
		int now = queue[head];
		for (int i = 0; i < (int)adj[now].size(); i++) {
			int to = adj[now][i];
			dp[to] = down[to];
			update(dp[to], make_pair(dp[now].first + weight[to], max(weight[to], dp[now].second)));
			queue.push_back(to);
		}
	}
}

pair<int, int> query(int x, int y) {
	if (dep[x] < dep[y]) swap(x, y);
	int fx = x, fy = y;
	int maxd;
	int ret1 = 0, ret2 = 0;
	for (maxd = 0; (1 << maxd) <= dep[x]; maxd++);
	maxd--;
	ret1 = max(maximum[x][0], maximum[y][0]);
	for (int i = maxd; i >= 0; i--) {
		if (dep[fa[x][i]] >= dep[y]) {
			ret1 = max(ret1, maximum[x][i]);
			x = fa[x][i];
		}
 	}
 	ret1 = max(ret1, maximum[x][0]);
 	ret1 = max(ret1, maximum[y][0]);
 	if (x == y) {
 		ret2 = dist[fx] - dist[fy] + weight[fy]; 
 		return make_pair(ret1, ret2);
 	}

 	for (int i = maxd; i >= 0; i--) {
 		if (fa[x][i] != 0 && fa[x][i] != fa[y][i]) {
 			ret1 = max(ret1, maximum[x][i + 1]);
 			ret1 = max(ret1, maximum[y][i + 1]);
 			x = fa[x][i];
 			y = fa[y][i];
 		}
 	}
 	ret1 = max(ret1, maximum[x][0]);
 	ret1 = max(ret1, maximum[y][0]);
 	ret1 = max(ret1, maximum[fa[x][0]][0]);
 	ret2 = dist[fx] + dist[fy] - dist[fa[x][0]] * 2 + weight[fa[x][0]];
 	return make_pair(ret1, ret2);
}
void add(int x, int y) {
	adj[x].push_back(y);
}
void solve() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) adj[i].clear();
	for (int i = 1; i <= n - 1; i++) {
		int x;
		scanf("%d", &x);
		add(x, i + 1);
		fa[i + 1][0] = x;
	}
	for (int i = 1; i <= n; i++) {
		if (adj[i].size() == 0) leaf[i] = 1;
		else leaf[i] = 0;
	}
	for (int i = 1; i <= n; i++) {
		scanf("%d", &weight[i]);
		maximum[i][0] = weight[i];
	}

	for (int i = 1; i <= n; i++) {
		dp[i] = make_pair(inf, 0);
		down[i] = make_pair(inf, 0);
	}

	for (int i = 1; i <= n; i++) {
		if (leaf[i]) {
			down[i] = make_pair(weight[i], weight[i]);
			update(dp[1], make_pair(weight[1] + weight[i], max(weight[1], weight[i])));
		}
	}
	build();	
	DP();
	for (int i = 1; i <= m; i++) {
		pair<int, int> tmp, ans;
		int u, v;
		scanf("%d%d", &u, &v);
		tmp = query(u, v);
		ans = make_pair(tmp.second, -tmp.first);
		tmp = make_pair(dp[u].first + dist[v], -max(dp[u].second, maximum[v][18]));
		ans = min(ans, tmp);
		tmp = make_pair(dp[v].first + dist[u], -max(dp[v].second, maximum[u][18]));
		ans = min(ans, tmp);
		tmp = make_pair(dp[u].first + dp[v].first + weight[1], -max(max(dp[u].second, dp[v].second), weight[1]));
		ans = min(ans, tmp);
		printf("%d %d\n", ans.first, -ans.second);
	} 

}

int main() {


	int tests = 1;
	for (int i = 1; i <= tests; i++) {
		solve();
	}
	return 0;
}
