
#include <bits/stdc++.h>
using namespace std;

const int maxn = 2000008;
int n, m, a[maxn]; 

int getInt() {
	int res = 0; char c;
	do c = getchar();
	while (!isdigit(c));

	while (isdigit(c))
		res = (res << 1) + (res << 3) + c - '0', c = getchar();

	return res;
}

int main() {
	freopen("wave.in", "r", stdin);
	freopen("wave.out", "w", stdout);

	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++)
		scanf("%d", a + i);
	int ans = 1, k = 0, cur = a[0];
	for (int i = 1; i < n; i++)
		if (k) 
			if (cur - m >= a[i])
				k = 0, cur = a[i], ans++;
			else cur = max(cur, a[i]);
		else 
			if (a[i] - m >= cur)
				k = 1, cur = a[i], ans++;
			else cur = min(cur, a[i]);
	printf("%d\n", ans);

	fclose(stdin); fclose(stdout);
	return 0;
}
