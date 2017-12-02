#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 8;
char s[N];

int main() {
	freopen("reverse.in", "r", stdin);
	freopen("reverse.out", "w", stdout);

	cin >> s; int ans = N, sum = 0, tmp = 0, n = strlen(s);

	for (int i = 0; i < n; i++)
		sum += s[i] - '0';

	if (sum == n) ans = 0;
	for (int i = 0; i < n; i++) {
		tmp += s[i] - '0';
		ans = min(ans, tmp + (n - i - 1) - (sum - tmp));
	}

	cout << ans << endl;

	return 0;

}