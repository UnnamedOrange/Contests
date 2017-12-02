#include <cstring>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>

using namespace std;

#define ull long long

#define Max(a,b) ((a)>(b)?(a):(b))

#define debug(...) fprintf(stderr,__VA_ARGS__)

int read()
{
	int ret = 0;
	char c = getchar();

	while (c<'0' || c>'9') c = getchar();

	while (c >= '0' && c <= '9') {
		ret = ret * 10 + c - '0'; c = getchar();
	}

	return ret;
}

const int MAXN = 1000000;

int n, m;

int a[MAXN + 10];

ull sum[MAXN + 10];

int solve(int k)
{
	static int st[MAXN + 10];
	int top = 1, ret = 0;

	for (int i = 1; i <= n; i++) {
		sum[i] = sum[i - 1] + a[i] - k;
		if (!top || sum[i] < sum[st[top]]) st[++top] = i;
	}

	for (int i = n; i >= 1; i--) {
		while (top && sum[st[top]] <= sum[i]) top--;
		ret = Max(ret, i - st[top + 1]);
	}

	return ret;
}

void init()
{
	n = read(), m = read();

	for (int i = 1; i <= n; i++) a[i] = read();

	for (int i = 1; i <= m; i++)
		cout << solve(read()) << ' ';

	return;
}

int main()
{
	freopen("blocks.in", "r", stdin);
	freopen("blocks.out", "w", stdout);
	init();
	fclose(stdin);
	fclose(stdout);
	return 0;
}
