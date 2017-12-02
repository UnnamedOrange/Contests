#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>

using namespace std;

const int N = 1e5 + 5;

char s[N];
int n, tot, ans = N;
int num[N], kd[N];
int sh[N], ni[N];

int main() {
	freopen("reverse.in", "r", stdin);
	freopen("reverse.out", "w", stdout);

	scanf("%s", s + 1);
	n = strlen(s + 1);
	int now = s[1] - '0', cnt = 1;
	for (int i = 2; i <= n; i ++) {
		if (now == s[i] - '0')
			cnt ++;
		else {
			num[++ tot] = cnt; kd[tot] = now;
			now = s[i] - '0'; cnt = 1;
		}
	}
	num[++ tot] = cnt; kd[tot] = now;
	
	for (int i = 1; i <= tot; i ++) 
		sh[i] = sh[i - 1] + (kd[i] == 1 ? num[i] : 0);
	for (int i = tot; i; i --) 
		ni[i] = ni[i + 1] + (kd[i] == 0 ? num[i] : 0);
		
	for (int i = 1; i <= tot; i ++)
		ans = min(ans, sh[i] + ni[i + 1]);
	ans = min(ans, ni[1]);
	
	printf("%d\n", ans);
	
	return 0;
}
