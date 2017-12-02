#include <bits/stdc++.h>
using namespace std;

const int N = 1008, m = 7;
int c, d;
int fac(int n) {
	long long r = 1;
	for (int i = 1; i <= n; i++)
		if (i % m) r = r * i % m;
		else {
			int x = i;
			while (x % m == 0)
				x /= m, c += d;
			r = r * x % m;
		}
	return r;
}

int inv(int n) {
	for (int i = 1; i < m; i++)
		if (i * n % m == 1)
			return i;
}

int main() {
	freopen("stack.in", "r", stdin);
	freopen("stack.out", "w", stdout);

	int n; cin >> n;

	d = 1;
	int r = fac(2 * n);
	d = -1;
	int ans = r * inv(fac(n)) % m * inv(fac(n + 1)) % m;

	cout << (c ? 0 : ans) << endl;

	
	fclose(stdin); fclose(stdout);
	return 0;
}