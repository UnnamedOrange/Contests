#include <iostream>
#include <cstdio>
#include <cstring>

const int maxn = 300010;

using namespace std;

int n, m;
int a[maxn];
int o, l, r, c, x;

int main()
{
	freopen("color.in", "r", stdin);
	freopen("color.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for (int i = 0; i < m; i++)
	{
		scanf("%d", &o);
		if (o == 1)
		{
			scanf("%d%d%d", &l, &r, &c);
			int num = 0;
			for (int i = l; i <= r; i++)
				if (a[i] == c)
					num++;
			printf("%d\n", num);
		}
		else
		{
			scanf("%d", &x);
			swap(a[x], a[x + 1]);
		}
	}
	return 0;
}

