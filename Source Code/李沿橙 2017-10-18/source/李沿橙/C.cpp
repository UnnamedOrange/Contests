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

const INT INF = (~(INT(1) << (sizeof(INT) * 8 - 1))) >> 1;
const INT maxn = 55;
INT n, m;
INT rect[maxn][maxn];

INT f[maxn][maxn][2 * maxn * maxn];
INT maxStatus[maxn][maxn];
#define pow2(x) ((x) * (x))

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			rect[i][j] = readIn();
		}
	}
	memset(f, -1, sizeof(f));

	f[1][1][rect[1][1]] = 0;
	maxStatus[1][1] = rect[1][1];
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			INT step = i + j - 1;
			INT& s = maxStatus[i][j];
			if (i != 1)
			{
				INT preS = maxStatus[i - 1][j];
				for (int k = 0; k <= preS; k++)
				{
					INT newS = k + rect[i][j];
					INT& ans = f[i][j][newS];
					INT& pre = f[i - 1][j][k];
					if (pre != -1)
					{
						s = std::max(s, newS);
						INT t = pre + pow2(k);
						t /= step - 1;
						t += pow2(rect[i][j]);
						t *= step;
						t -= pow2(k + rect[i][j]);
						if (ans == -1 || ans > t) ans = t;
					}
				}
			}
			if (j != 1)
			{
				INT preS = maxStatus[i][j - 1];
				for (int k = 0; k <= preS; k++)
				{
					INT newS = k + rect[i][j];
					INT& ans = f[i][j][newS];
					INT& pre = f[i][j - 1][k];
					if (pre != -1)
					{
						s = std::max(s, newS);
						INT t = pre + pow2(k);
						t /= step - 1;
						t += pow2(rect[i][j]);
						t *= step;
						t -= pow2(k + rect[i][j]);
						if (ans == -1 || ans > t) ans = t;
					}
				}
			}
		}
	}
	INT ans = INF;
	for (int i = 0; i <= (n + m - 1) * 50; i++)
	{
		if (f[n][m][i] != -1) ans = std::min(ans, f[n][m][i]);
	}
	cout << ans << endl;
}

int main()
{
#ifndef JUDGE
	freopen("C.in", "r", stdin);
	freopen("C.out", "w", stdout);
#endif
	run();
	return 0;
}
