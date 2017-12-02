#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#define N 100000
#define B 1024
using namespace std;
typedef long long LL;
int n, cnt = 0;
char a[N + 5];
LL dp[2][B][2], ans = 0;
void add(LL &a, LL b) { a += b; }
int main() {
	freopen("number.in", "r", stdin);
	freopen("number.out", "w", stdout);
	scanf("%s", a);
	cnt = strlen(a);
	for (int i = cnt; i; i--) a[i] = a[i - 1] - 48;
	bool now = 0, pre = 1;
	dp[now][0][0] = 1;
	for (int i = 1; i <= cnt; i++) {
		now ^= 1, pre ^= 1;
//		printf("a[%d] = %d\n", i, a[i]);
		for (int s = 0; s < B; s++)
			for (int flag = 0; flag < 2; flag++)
					if (dp[pre][s][flag]) {
						LL t = dp[pre][s][flag];
						dp[pre][s][flag] = 0;
//						printf("%d %d %d = %lld\n", i - 1, s, flag, dp[pre][s][flag]);
						for (int nxt = 0; nxt < 10 && (flag || nxt <= a[i]); nxt++) {
							int ns = (nxt || s) ? (s | (1 << nxt)) : 0;
							add(dp[now][ns][flag || nxt < a[i]], t);
						}
					}
	}
	for (int s = 1; s < B; s++)
		for (int flag = 0; flag < 2; flag++) 
//			if (dp[now][s][flag]) printf("%d %d %d = %lld\n", cnt, s, flag, dp[now][s][flag]);
			add(ans, dp[now][s][flag] * (dp[now][s][flag] - 1) / 2);
	printf("%lld\n", ans);
	return 0;
}
