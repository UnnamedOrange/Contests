#include <cstdio>
#include <algorithm>
#include <iostream>

using namespace std;

typedef long long ll;

const int N = 1e5 + 5;

int n, m;
ll X[N], Y[N], a, b; 

bool check(int cx) {
	ll r1 = Y[cx] * a, r2 = X[cx] * b, r3 = X[cx] * Y[cx];
	if (r1 >= r3 && r2 >= r3) return true;
	else if (r1 <= r3) {
		if (r3 - r1 <= r2) return true;
		else return false;
	} else return false ;
}

int main() {
	freopen("geometry.in", "r", stdin);
	freopen("geometry.out", "w", stdout);

	scanf("%d", &n);
	for (int i = 1; i <= n; i ++) 
		scanf("%lld", &X[i]); 
	for (int i = 1; i <= n; i ++) 
		scanf("%lld", &Y[i]);
	sort(X + 1, X + n + 1); sort(Y + 1, Y + n + 1);
	scanf("%d", &m);
	while (m --) {
		scanf("%lld%lld", &a, &b);
		int l = 0, r = n; 
		int mid = (l + r) >> 1;
		while (l < r) {
			if (check(mid + 1)) l = mid + 1; 
			else r = mid;
			mid = (l + r) >> 1;
		}
		printf("%d\n", mid);
	}
	return 0;
}
