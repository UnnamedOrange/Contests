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
typedef int INT;
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

const INT maxn = 105;
INT n;
INT num[maxn];
INT f[maxn][maxn];

void run()
{
	INT T = readIn();
	while (T--)
	{
		n = readIn();
		memset(f, -1, sizeof(f));
		for (int i = 1; i <= n; i++)
		{
			num[i] = num[i - 1] + readIn();
			f[i][i] = 0;
		}

		for (int l = 2; l <= n; l++)
		{
			for (int i = 1; i <= n - l + 1; i++)
			{
				INT j = i + l - 1;
				for (int k = i; k < j; k++)
				{
					if (f[i][j] == -1 || f[i][j] > f[i][k] + f[k + 1][j] +
						((num[k] - num[i - 1]) % 100) * ((num[j] - num[k]) % 100))
						f[i][j] = f[i][k] + f[k + 1][j] + ((num[k] - num[i - 1]) % 100) * ((num[j] - num[k]) % 100);
				}
			}
		}
		cout << f[1][n] << endl;
	}
}

int main()
{
	run();
	return 0;
}
