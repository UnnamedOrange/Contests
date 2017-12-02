#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <deque>
#include <map>
#include <set>
using std::cin;
using std::cout;
using std::endl;
typedef int INT;
inline INT readIn()
{
	bool minus = false;
	INT a = 0;
	char ch = getchar();
	while (!(ch == '-' || ch >= '0' && ch <= '9')) ch = getchar();
	if (ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		a *= 10;
		a += ch;
		a -= '0';
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}

const int maxn = 10005;
const int maxm = 1005;
int n, m, k;
INT X[maxn];
INT Y[maxn];
INT L[maxn];
INT H[maxn];
int nPipe[maxn];
INT f[2][maxm];

void run()
{
	n = readIn();
	m = readIn();
	k = readIn();
	H[0] = m + 1;
	for (int i = 1; i <= n; i++)
	{
		X[i] = readIn();
		Y[i] = readIn();
		L[i] = 0;
		H[i] = m + 1;
	}
	for (int i = 0; i < k; i++)
	{
		INT P = readIn();
		nPipe[P] = true;
		L[P] = readIn();
		H[P] = readIn();
	}
	for (int i = 1; i <= n; i++)
	{
		if (nPipe[i]) nPipe[i] = nPipe[i - 1] + 1;
		else nPipe[i] = nPipe[i - 1];
	}

	const INT INF = 0x3f3f3f3f; //往往极大值策略比-1策略还要有效
	INT farthest = 0;
	for (int i = 1; i <= n; i++)
	{
		int cnt = i & 1;
		int last = (i + 1) & 1;
		memset(f[cnt], 0x3f, sizeof(f[cnt]));
		for (int j = X[i]; j <= m; j++) //不碰顶的
		{
			f[cnt][j] = std::min(f[cnt][j], f[last][j - X[i]] + 1);
			f[cnt][j] = std::min(f[cnt][j], f[cnt][j - X[i]] + 1);
			if (j > L[i] && j < H[i] && f[cnt][j] != INF) farthest = i;
		}
		for (int j = m - X[i]; j <= m; j++) //碰顶的
		{
			f[cnt][m] = std::min(f[cnt][m], f[last][j] + 1);
			f[cnt][m] = std::min(f[cnt][m], f[cnt][j] + 1);
			if (j > L[i] && j < H[i] && f[cnt][j] != INF) farthest = i;
		}
		for (int j = L[i] + 1; j < H[i]; j++) //下落
		{
			if (j + Y[i] <= m)
			{
				f[cnt][j] = std::min(f[cnt][j], f[last][j + Y[i]]);
				if (j > L[i] && j < H[i] && f[cnt][j] != INF) farthest = i;
			}
		}

		//处理不能到的地方
		for (int j = 0; j <= L[i]; j++)
		{
			f[cnt][j] = INF;
		}
		for (int j = H[i]; j <= m; j++)
		{
			f[cnt][j] = INF;
		}
	}
	INT ans = INF;
	for (int i = 1; i <= m; i++)
	{
		if (f[n & 1][i] < ans)
		{
			ans = f[n & 1][i];
		}
	}
	if (ans == INF)
	{
		cout << 0 << endl << nPipe[farthest] << endl;
	}
	else
	{
		cout << 1 << endl << ans << endl;
	}
}

int main()
{
	run();
	return 0;
}