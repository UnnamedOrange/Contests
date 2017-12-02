#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>

const int maxn = 100010;
const int maxlen = 10010;
const int maxt = 20;
const int inf = 1000000000;

using namespace std;

int n, m;
char genes[maxn][maxlen];
int lens[maxn];
int o, t;
int a[maxt];

int main()
{
	freopen("biology.in", "r", stdin);
	freopen("biology.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		scanf("%s", genes[i]);
		lens[i] = strlen(genes[i]);
	}
	for (int i = 0; i < m; i++)
	{
		scanf("%d", &o);
		if (o == 1)
		{
			scanf("%s", genes[++n]);
			lens[n] = strlen(genes[n]);
		}
		else
		{
			int len = 0;
			int shortest = inf;
			int flag = true;
			scanf("%d", &t);
			for (int j = 0; j < t; j++)
			{
				scanf("%d", &a[j]);
				shortest = min(shortest, lens[a[j]]);
			}
			while (flag && len < shortest)
			{
				for (int j = 0; j < t; j++)
				{
					if (genes[a[j]][lens[a[j]] - 1 - len]
					 != genes[a[0]][lens[a[0]] - 1 - len])
					{
						flag = false;
						break;
					}
				}
				if (flag)
					len++;
			}
			printf("%d\n", len);
		}
	}
	return 0;
}

