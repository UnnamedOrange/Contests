#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <climits>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <deque>
#include <map>
#include <set>
#include <bitset>
using std::cin;
using std::cout;
using std::endl;
typedef long long INT;
inline INT readIn()
{
	INT a = 0;
	bool minus = false;
	char ch = getchar();
	while(!(ch == '-' || ch >= '0' && ch <= '9')) ch = getchar();
	if(ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9')
	{
		a *= 10;
		a += ch;
		a -= '0';
		ch = getchar();
	}
	if(minus) a = -a;
	return a;
}

const INT maxn = 2005;
const INT maxv = 305;
INT n, m, v, e;
INT c[maxn];
INT d[maxn];
double posibility[maxn];
INT rect[maxv][maxv];

void initFloyd()
{
	memset(rect, 0x3f, sizeof(rect));
	for(int i = 1; i <= v; i++)
	{
		rect[i][i] = 0;
	}
	for(int i = 1; i <= e; i++)
	{
		INT from = readIn();
		INT to = readIn();
		INT weight = readIn();
		rect[from][to] = std::min(rect[from][to], weight);
		rect[to][from] = std::min(rect[to][from], weight);
	}
	for(int k = 1; k <= v; k++)
	{
		for(int i = 1; i <= v; i++)
		{
			for(int j = 1; j <= v; j++)
			{
				if(i != k && i != j && j != k)
					rect[i][j] = std::min(rect[i][j], rect[i][k] + rect[k][j]);
			}
		}
	}
}

void initRoom()
{
	for(int i = 1; i <= n; i++)
	{
		c[i] = readIn();
	}
	for(int i = 1; i <= n; i++)
	{
		d[i] = readIn();
	}
	for(int i = 1; i <= n; i++)
	{
		scanf("%lf", &posibility[i]);
	}
}

double f[maxn][maxn];
double g[maxn][maxn];

void run()
{
	n = readIn();
	m = readIn();
	v = readIn();
	e = readIn();
	initRoom();
	initFloyd();

	for(int i = 1; i <= n; i++)
	{
		for(int j = 0; j <= m; j++)
		{
			f[i][j] = g[i][j] = 1e100;
		}
	}
	f[1][1] = 0;
	g[1][0] = 0;

	for(int i = 2; i <= n; i++)
	{
		for(int j = 0; j <= m; j++)
		{
			g[i][j] = std::min(
			              g[i - 1][j] + rect[c[i - 1]][c[i]],
			              f[i - 1][j] + (rect[d[i - 1]][c[i]] * posibility[i - 1] + rect[c[i - 1]][c[i]] * (1 - posibility[i - 1]))
			          );
			if(j)
				f[i][j] = std::min(
				              g[i - 1][j - 1] + rect[c[i - 1]][d[i]] * posibility[i] + rect[c[i - 1]][c[i]] * (1 - posibility[i]),
				              f[i - 1][j - 1] + (
				                  rect[c[i - 1]][c[i]] * (1 - posibility[i - 1]) * (1 - posibility[i]) +
				                  rect[c[i - 1]][d[i]] * (1 - posibility[i - 1]) * posibility[i] +
				                  rect[d[i - 1]][c[i]] * posibility[i - 1] * (1 - posibility[i]) +
				                  rect[d[i - 1]][d[i]] * posibility[i - 1] * posibility[i]
				              )
				          );
		}
	}
	double ans = 1e100;
	for(int i = 0; i <= m; i++)
	{
		ans = std::min(ans, std::min(f[n][i], g[n][i]));
	}
	printf("%.2f", ans);
}

int main()
{
	run();
}
