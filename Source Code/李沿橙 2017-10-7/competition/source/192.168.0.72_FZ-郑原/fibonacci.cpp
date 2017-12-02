#include <cstdio>
#include <algorithm>
#include <iostream>

using namespace std;

typedef long long ll; 

const ll up = 1e12; 

//int fa[N][23]; 

ll f[105], tk[105];
int m, tot, ftot;  

ll find(ll st) {
	int l = 1, r = ftot; 
	int mid = (l + r) >> 1;
	while (l < r) {
		if (f[mid + 1] >= st) r = mid; 
		else l = mid + 1; 
		mid = (l + r) >> 1;
	} 
	return f[mid];
}

int main() {
	freopen("fibonacci.in", "r", stdin);
	freopen("fibonacci.out", "w", stdout);

	f[0] = f[1] = 1;
	for (int i = 2; f[i - 1] <= up; i ++)
		f[i] = f[i - 1] + f[i - 2], ftot = i; 
	scanf("%d", &m);
	while (m --) {
		ll a, b; scanf("%lld%lld", &a, &b); 
		tot = 0;
		while (a) {
			tk[++ tot] = a; 
			if (a == 1) break ;
			a = a - find(a);
		}
		while (b) {
			tk[++ tot] = b; 
			if (b == 1) break ;
			b = b - find(b); 
		}
		sort(tk + 1, tk + tot + 1);
		ll ans = 0; 
		for (int i = tot; i > 1; i --) 
			if (tk[i] == tk[i - 1]) {
				ans = tk[i]; break ;
			} 
		printf("%lld\n", ans);
	}
	return 0; 
}
