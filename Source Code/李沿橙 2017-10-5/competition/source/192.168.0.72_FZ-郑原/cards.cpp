#include <cstdio>
#include <algorithm>
#include <iostream>

using namespace std;

const int N = 300 + 5;

int gcd(int a, int b) {
	return b == 0 ? a : gcd(b, a % b);
}

int cds[N], vis[N], n; 

double qry_p(int now, int num) {
	if (num == 1 || now == n) {
		if (now & 1) return 0.0;
		else return 1.0;
	} 
	double ret = 0.0;
	for (int i = 1; i <= n; i ++) {
		if (vis[i]) continue ;
		vis[i] = 1; 
		ret += 1.0 / (double) (n - now) * qry_p(now + 1, gcd(num, cds[i])); 
		vis[i] = 0;
	}
	return ret; 
}

int qry_a(int now, int num) {
	if (num == 1) return 1;
	if (now == n) return 0;
	int ret = 0; 
	for (int i = 1; i <= n; i ++) {
		if (vis[i]) continue ;
		vis[i] = 1;
		if (qry_a(now + 1, gcd(num, cds[i])) == 0) ret = 1;
		vis[i] = 0;
	}
	return ret;
}

int main() {
	freopen("cards.in", "r", stdin);
	freopen("cards.out", "w", stdout);

	scanf("%d", &n);
	for (int i = 1; i <= n; i ++) 
		scanf("%d", &cds[i]);
	double r1 = qry_p(0, 0);
	int r2 = qry_a(0, 0);
	printf("%.8lf %d.00000000\n", r1, r2);
	return 0;
}
