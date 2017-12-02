#include <iostream>
#include <cstdio>
#include <cstring>

const int maxn = 30010;

using namespace std;

int p;
char orderS;
int p1, p2;
int fa[maxn];
int son[maxn];
int num[maxn];

int main()
{
	freopen("cube.in", "r", stdin);
	freopen("cube.out", "w", stdout);
	scanf("%d", &p);
	memset(fa, -1, sizeof fa);
	memset(son, -1, sizeof son);
	memset(num, 0, sizeof num);
	for (int i = 0; i < p; i++)
	{
		cin >> orderS;
		if (orderS == 'M')
		{
			scanf("%d%d", &p1, &p2);
			while (son[p1] != -1)
				p1 = son[p1];
			while (fa[p2] != -1)
				p2 = fa[p2];
			son[p1] = p2;
			fa[p2] = p1;
			while (p1 != -1)
			{
				num[p1] += num[p2] + 1;
				p1 = fa[p1];
			}
		}
		else if (orderS == 'C')
		{
			scanf("%d", &p1);
			printf("%d\n", num[p1]);
		}
	}
	return 0;
}

