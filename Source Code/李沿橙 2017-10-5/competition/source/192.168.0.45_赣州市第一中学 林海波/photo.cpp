#include <iostream>
#include <cstdio>
#include <cstring>

/*const int maxn = 2010;*/
const int mod = 1000000007;

using namespace std;

int n, m, k;
/*int C[maxn][maxn] = { 0 };

long long dfs(int a, int b);
long long pow_mod(int a, int n);*/

int main()
{
	freopen("photo.in", "r", stdin);
	freopen("photo.out", "w", stdout);
	scanf("%d%d%d", &n, &m, &k);
	/*C[0][0] = C[1][0] = C[1][1] = 1;
	for (int i = 2; i <= n; i++)
		for (int j = 0; j <= i; j++)
			C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
	long long ans = dfs(n, k);
	ans = (ans * pow_mod(k, n * (m - 2))) % mod;*/
	long long ans = n * m * k % mod;
	printf("%lld\n", ans);
	return 0;
}

/*long long dfs(int a, int b)
{
	long long ans = 0;
	if (a == 0)
		return 1;
	if (b == 1)
		return 1;
	for (int i = 0; i <= a; i++)
		ans = (C[a][a - i] * dfs(a - i, b - 1)) % mod;
	return ans;
}

long long pow_mod(int a, int n)
{
	if (n == 0)
		return 1;
	long long pow_ans = pow_mod(a, n / 2);
	pow_ans = (pow_ans * pow_ans) % mod;
	if (n % 2 == 1)
		pow_ans = (pow_ans * a) % mod;
	return pow_ans;
}*/

