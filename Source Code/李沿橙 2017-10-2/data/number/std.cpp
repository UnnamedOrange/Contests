#include <bits/stdc++.h>
using namespace std;

int n, f[1 << 10];
long long ans;

void count(int x) {
	int s = 0;
	while (x) {
		s |= 1 << x % 10;
		x /= 10;
	}
	f[s]++;
}

int main() {
	freopen("number", "r", stdin);
	int number; scanf("%d", &number);
	fclose(stdin);
	char input[20], output[20];
	sprintf(input, "marriage%d.in", number);
	sprintf(output, "marriage%d.out", number);
	freopen(input, "r", stdin);
	freopen(output, "w", stdout);

	cin >> n;
	for (int i = 1; i <= n; i++)
		count(i);
	for (int i = 1; i < (1 << 10); i++) 
		ans += (long long)f[i] * (f[i] - 1) / 2;
	cout << ans;

	fclose(stdin); fclose(stdout);
	return 0;
}
