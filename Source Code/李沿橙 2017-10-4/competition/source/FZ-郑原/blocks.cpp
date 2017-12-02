#include <cstdio>
#include <algorithm>
#include <iostream>

using namespace std;

typedef long long ll;

const int N = 1e6 + 5;

ll sum[N], k; 
int n, m, p[N];
int ans;

bool cmp(int a, int b) {
	ll v1 = sum[a - 1] - (ll) (a - 1) * k; 
	ll v2 = sum[b - 1] - (ll) (b - 1) * k;
	if (v1 == v2) return a < b; 
	else return v1 < v2;
}

bool check(int a, int b) {
	ll v1 = sum[a - 1] - (ll) (a - 1) * k;
	ll v2 = sum[b] - (ll) b * k;
	return v1 <= v2; 
}

int main() {
	freopen("blocks.in", "r", stdin);
	freopen("blocks.out", "w", stdout);

	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i ++) {
		scanf("%lld", &sum[i]); 
		sum[i] += sum[i - 1];
	}
	for (int i = 1; i <= m; i ++) {
		scanf("%lld", &k);
		for (int j = 1; j <= n; j ++) p[j] = j;
		sort(p + 1, p + n + 1, cmp);
		int mi = n + 1; ans = 0;
		for (int j = 1; j <= n; j ++) {
			mi = min(mi, p[j]);
			//q[++ r] = p[j]; 
			if (p[j] >= mi && check(mi, p[j])) ans = max(ans, p[j] - mi + 1);
		}
		printf("%d ", ans);
	}
	return 0;
}
