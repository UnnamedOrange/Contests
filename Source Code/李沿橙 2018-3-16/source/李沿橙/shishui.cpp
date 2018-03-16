#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cassert>
#include <cctype>
#include <climits>
#include <ctime>
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
#include <list>
#include <functional>
typedef long long LL;
typedef unsigned long long ULL;
using std::cin;
using std::cout;
using std::endl;
typedef LL INT_PUT;
INT_PUT readIn()
{
	INT_PUT a = 0;
	bool positive = true;
	char ch = getchar();
	while (!(ch == '-' || std::isdigit(ch))) ch = getchar();
	if (ch == '-')
	{
		positive = false;
		ch = getchar();
	}
	while (std::isdigit(ch))
	{
		a = a * 10 - (ch - '0');
		ch = getchar();
	}
	if (positive) a = -a;
	return a;
}
void printOut(INT_PUT x)
{
	char buffer[20];
	int length = 0;
	if (x < 0) putchar('-');
	else x = -x;
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
	putchar('\n');
}

const int mod = int(1e9) + 7;
LL a, b, c;

#define RunInstance(x) delete new x
struct brute
{
	static const int maxN = 305;
	static int f[2][maxN][maxN];
	static int sum[2][maxN][maxN];
	brute()
	{
		memset(f, 0, sizeof(f));
		memset(sum, 0, sizeof(sum));
		f[0][1][1] = sum[0][1][1] = 1;
		for (int i = 1, toa = a + 1; i <= toa; i++)
		{
			for (int j = 1, tob = b + 1; j <= tob; j++)
			{
				if (i == 1 && j == 1) continue;
				f[0][i][j] = ((LL)f[0][i - 1][j] + f[0][i][j - 1]) % mod;
				sum[0][i][j] = ((LL)f[0][i][j] + sum[0][i - 1][j] + sum[0][i][j - 1] - sum[0][i - 1][j - 1]) % mod;
			}
		}
		for (int i = 1; i <= c; i++)
		{
			int cnt = i & 1;
			int pre = !cnt;
			memset(f[cnt], 0, sizeof(f[cnt]));
			memset(sum[cnt], 0, sizeof(sum[cnt]));
			for (int j = 1, toa = a + 1; j <= toa; j++)
			{
				for (int k = 1, tob = b + 1; k <= tob; k++)
				{
					f[cnt][j][k] = sum[pre][j - 1][k - 1];
					sum[cnt][j][k] = ((LL)f[cnt][j][k] + sum[pre][j][k] + sum[cnt][j - 1][k] + sum[cnt][j][k - 1] -
						((LL)sum[pre][j - 1][k] + sum[pre][j][k - 1] + sum[cnt][j - 1][k - 1]) + sum[pre][j - 1][k - 1]) % mod + mod;
					if (sum[cnt][j][k] >= mod) sum[cnt][j][k] -= mod;
				}
			}
		}
		printOut(f[c & 1][a + 1][b + 1]);
	}
};
int brute::f[2][maxN][maxN];
int brute::sum[2][maxN][maxN];
struct work
{
	work()
	{

	}
};

void run()
{
	int T = readIn();
	while (T--)
	{
		a = readIn();
		b = readIn();
		c = readIn();
		if (a <= 15 && b <= 15 && c <= 15)
			RunInstance(brute);
		else
			RunInstance(brute);
	}
}

int main()
{
#ifndef LOCAL
	freopen("shishui.in", "r", stdin);
	freopen("shishui.out", "w", stdout);
#endif
	run();
	return 0;
}