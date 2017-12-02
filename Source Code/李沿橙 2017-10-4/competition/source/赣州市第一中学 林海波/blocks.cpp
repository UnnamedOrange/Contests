#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>

const int maxn = 1000010;

using namespace std;

int n, m, k;
int ans;
int a[maxn];
int s[maxn];

int main()
{
	freopen("blocks.in", "r", stdin);
	freopen("blocks.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for (int i = 0; i < m; i++)
	{
		scanf("%d", &k);
		s[0] = 0;
		for (int j = 1; j <= n; j++)
			s[j] = s[j - 1] + a[j] - k;
		/*ans = 0;
		for (int j = 1; j <= n; j++)
			for (int k = j - ans - 1; k >= 0; k--)
				if (s[j] - s[k] >= 0)
					ans = max(ans, j - k);
		printf("%d ", ans);*/
		
		int l = 0;
		int r = n;
		bool flag = false;
		while (r - l > 1)
		{
			int mid = (l + r) / 2;
			for (int j = mid; j <= n; j++)
				if (s[j] - s[j - mid] >= 0)
				{
					flag = true;
					break;
				}
			if (flag)
				l = mid;
			else
				r = mid;
			flag = false;
		}
		for (int j = r; j <= n; j++)
			if (s[j] - s[j - r] >= 0)
			{
				flag = true;
				break;
			}
		if (flag)
			printf("%d ", r);
		else
			printf("%d ", l);
	}
	return 0;
}

