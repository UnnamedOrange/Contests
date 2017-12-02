#include <iostream>
#include <cstdio>
#include <cstring>

const int maxn = 1010;
const int mod = 7;

using namespace std;

int n;
int ans[maxn][maxn];

int main()
{
	freopen("stack.in", "r", stdin);
	freopen("stack.out", "w", stdout);
	scanf("%d", &n);
	ans[1][0] = 1;
	ans[1][1] = 1;
	for (int i = 2; i <= n; i++)
	{
		ans[i][1] = ans[i][2] = ans[i - 1][0];
		for (int j = 3; j <= n; j++)
		{
			ans[i][j] = ans[i][j - 1] - ans[i - 1][j - 2] + mod;
			ans[i][j] %= mod;
		}
		for (int j = 1; j <= n; j++)
		{
			ans[i][0] += ans[i][j];
			ans[i][0] %= mod;
		}
	}
	printf("%d\n", ans[n][0]);
	return 0;
}

