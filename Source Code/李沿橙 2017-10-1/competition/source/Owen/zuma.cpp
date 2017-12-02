#include <cstdlib>
#include <queue>
#include <vector>
#include <ctime>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 200
using namespace std;
char s[N + 5];
bool a[N + 5][N + 5];
int cnt = 0, n, sum, len, ans;
clock_t beg = clock();
void dfs(int now) {
	if (clock() - beg > 900000) { printf("%d\n", ans); exit(0); }
	if (now >= ans) return ;
	if (!len) { ans = now; return ; }
	int tmp = len;
	for (int i = 1; i <= len; i++) 
		a[now + 1][i] = a[now][i];
	for (int i = 1; i <= tmp; i++) {
			int j = 0;
			while (i + j <= tmp && i > j && (a[now][i + j] || a[now][i - j])) j++;
			len = 0;
			for (int k = 1; k < i - j; k++) a[now + 1][++len] = a[now][k];
			if (i + j <= tmp && i > j) a[now + 1][++len] = 1;
			if (i + j > tmp && i > j) a[now + 1][++len] = a[now][i - j];
			if (i + j <= tmp && i <= j) a[now + 1][++len] = a[now][i + j];
			for (int k = i + j + 1; k <= tmp; k++) a[now + 1][++len] = a[now][k];
			dfs(now + 1);
			len = tmp;
			for (int k = 1; k <= tmp; k++) a[now + 1][k] = a[now][k];
		}
}
int main() {
	freopen("zuma.in", "r", stdin);
	freopen("zuma.out", "w", stdout);
	scanf("%s", s);
	n = strlen(s);
	for (int i = 0; i < n; i++)
		if (!i || s[i] != s[i - 1]) a[0][cnt++] = sum, sum = 0; else sum++;
	a[0][cnt] = sum;
	if (cnt & 1) ans = (cnt + 1 >> 1) + 1; else ans = (cnt >> 1) + 3;
	len = cnt;
	dfs(0);
	printf("%d\n", ans);
	return 0;
}
