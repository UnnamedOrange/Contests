#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>

using namespace std;

const int N = 200 + 5;

int dp[N][N];
int n; 
char s[N];
int num[N], col[N], tot;

int main() {
	freopen("zuma.in", "r", stdin);
	freopen("zuma.out", "w", stdout);

	scanf("%s", s + 1);
	n = strlen(s + 1);
	int now = s[1] - '0', cnt = 1;
	for (int i = 2; i <= n; i ++) {
		if (s[i] - '0' == now) {
			cnt ++;
		} else {
			num[++ tot] = cnt;
			col[tot] = now;
			cnt = 1;
			now = s[i] - '0';
		}
	}
	num[++ tot] = cnt;
	col[tot] = now;
	
	for (int i = 1; i <= tot; i ++) dp[i][i] = 3 - num[i];
	
	for (int len = 2; len <= tot; len ++) {
		for (int i = 1, j = i + len - 1; j <= tot; i ++, j ++) {
			dp[i][j] = 10000;
			if (col[i] == col[j]) {
				dp[i][j] = min(dp[i][j], dp[i + 1][j - 1] + (num[i] + num[j] < 3 ? 1 : 0));
				for (int k = i + 1; k < j; k ++) 
					if (col[k] == col[i]) {
						dp[i][j] = min(dp[i][j], dp[i + 1][k - 1] + dp[k + 1][j - 1]);
					}
			}
			for (int k = i; k < j; k ++) {
				dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
			}
		}
	}
	
	//for (int i = 1; i < tot; i ++) printf("%d %d \n", dp[1][i], dp[i + 1][tot]);
	/*for (int i = 1; i <= tot; i ++) {
		for (int j = 1; j <= tot; j ++) printf("%d ", dp[i][j]);
		printf("\n");
	} */
	printf("%d\n", dp[1][tot]);
	
	return 0;
}
