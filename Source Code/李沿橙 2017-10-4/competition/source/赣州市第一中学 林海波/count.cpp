#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>

const int mod = 998244353;
const int maxn = 100000010;

using namespace std;

int L, R, k;
int ans = 0;
/*int p_num = 0;
long long g[maxn] = { 0 };
int phi[maxn] = { 0 };
bool is_not_prime[maxn] = { 0 };
int p[maxn];*/

long long pow_mod(int a, int n);

int main()
{
	freopen("count.in", "r", stdin);
	freopen("count.out", "w", stdout);
	scanf("%d%d%d", &L, &R, &k);
	if (L == 1)
	{
		ans += pow_mod(2, k);
		ans %= mod;
		L++;
	}
	for (int i = L; i <= R; i++)
	{
		ans += pow_mod(i, k);
		ans %= mod;
	}
	/*for (int i = 2; i <= R; i++)
	{
		if (!is_not_prime[i])
		{
			p[p_num++] = i;
			g[i] += i;
			phi[i] += 1;
		}
		for (int j = 0; j < p_num && i * p[j] <= R; j++)
		{
			g[i * p[j]] += i;
			phi[i * p[j]] += 1;
			is_not_prime[i * p[j]] = true;
			if (i % p[j] == 0)
				break;
		}
	}
	for (long long i = L; i <= R; i++)
	{
		ans += pow_mod((((1 + i) * i - g[i] * 2) / (i - phi[i])) % mod, k);
	}*/
	printf("%d\n", ans);
	return 0;
}

long long pow_mod(int a, int n)
{
	if (n == 0)
		return 1;
	long long pow_ans = pow_mod(a, n / 2);
	pow_ans = pow_ans * pow_ans % mod;
	if (pow_ans % 2 == 1)
		pow_ans = pow_ans * a % mod;
	return pow_ans;
}

