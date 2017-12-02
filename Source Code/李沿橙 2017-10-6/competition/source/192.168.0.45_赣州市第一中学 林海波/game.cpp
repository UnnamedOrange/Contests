#include <iostream>
#include <cstdio>
#include <cstring>

const int maxn = 50010;
const int maxk = 10;
const int mod = 1000000007;

using namespace std;

int n, m;
int o, a, b, c, k;
int sum;
int num[maxn];
int ball[maxk];

void dfs(int beg, int end, int bal);

int main()
{
	freopen("game.in", "r", stdin);
	freopen("game.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", &num[i]);
	for (int i = 0; i < m; i++)
	{
		scanf("%d%d%d", &o, &a, &b);
		if (o == 1)
		{
			scanf("%d", &c);
			for (int i = a; i <= b; i++)
				num[i] += c;
		}
		else if (o == 2)
		{
			for (int i = a; i <= b; i++)
				num[i] *= -1;
		}
		else
		{
			scanf("%d", &k);
			sum = 0;
			dfs(a, b, k);
			printf("%d\n", (sum + mod) % mod);
		}
	}
	return 0;
}

void dfs(int beg, int end, int bal)
{
	if (end - beg + 1 < bal)
		return;
	if (bal == 0)
	{
		long long ans = 1;
		for (int i = 1; i <= k; i++)
			ans = ans * ball[i] % mod;
		sum = (sum + ans) % mod;
	}
	for (int i = beg; i <= end; i++)
	{
		ball[bal] = num[i];
		dfs(i + 1, end, bal - 1);
	}
}

