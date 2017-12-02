#include <cstdlib>
#include <queue>
#include <vector>
#include <ctime>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 1000
using namespace std;
int n, dp[N + 5];
int solve(int n) {
	if (dp[n] != -1) return dp[n];
	dp[n] = 0;
	for (int i = 1; i < n; i++)
		dp[n] += solve(i) * solve(n - i - 1) % 7, dp[n] %= 7;
	dp[n] += solve(n - 1), dp[n] %= 7;
	return dp[n];
}
int main() {
	freopen("stack.in", "r", stdin);
	freopen("stack.out", "w", stdout);
	scanf("%d", &n);
	memset(dp, -1, sizeof(dp));
	dp[0] = dp[1] = 1;
	printf("%d\n", solve(n));
	return 0;
}
