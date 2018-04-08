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
typedef int INT_PUT;
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
		(a *= 10) -= ch - '0';
		ch = getchar();
	}
	return positive ? -a : a;
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

const int maxn = 11;
int n, m;
int a[maxn][maxn];
int b[maxn][maxn];

#define RunInstance(x) delete new x
struct cheat1
{
	cheat1()
	{
		int scoreA = a[1][1];
		int scoreB = b[2][2];
		int ans = std::max((scoreB + b[1][2]) - (scoreA + a[2][1]), (scoreB + b[2][1]) - (scoreA + a[1][2]));
		printOut(-ans);
	}
};
struct cheat2
{
	cheat2()
	{
		int scoreA = 0;
		int scoreB = 0;
		for (int i = 1; i <= n; i += 2)
			scoreA += a[i][1];
		for (int i = 2; i <= n; i += 2)
			scoreB += b[i][1];
		printOut(scoreA - scoreB);
	}
};
struct brute1
{
	int f[43046721 + 5];

	int makeStatus(int bit[maxn])
	{
		int ret = 0;
		for (int i = n; i; i--)
			(ret *= (m + 1)) += bit[i];
		return ret;
	}
	int DP(int S)
	{
		if (f[S] != -1) return f[S];
		int& ans = f[S];
		if (!S)
			return ans = 0;
		int bit[maxn];
		int t = S;
		int sum = 0;
		for (int i = 1; i <= n; i++)
		{
			bit[i] = t % (m + 1);
			t /= (m + 1);
			sum += bit[i];
		}
		if (sum & 1)
		{
			ans = INT_MAX;
			for (int i = 1; i <= n; i++)
			{
				if (bit[i] && (i == n || bit[i] > bit[i + 1]))
				{
					bit[i]--;
					int status = makeStatus(bit);
					bit[i]++;
					ans = std::min(ans, DP(status) + a[i][bit[i]]);
				}
			}
		}
		else
		{
			ans = INT_MIN;
			for (int i = 1; i <= n; i++)
			{
				if (bit[i] && (i == n || bit[i] > bit[i + 1]))
				{
					bit[i]--;
					int status = makeStatus(bit);
					bit[i]++;
					ans = std::max(ans, DP(status) - b[i][bit[i]]);
				}
			}
		}
		return ans;
	}

	brute1()
	{
		int U = std::pow(m + 1, n);
		memset(f, -1, sizeof(int) * U);
		printOut(DP(U - 1));
	}
};

void run()
{
	n = readIn();
	m = readIn();
	for (register int i = 1; i <= n; i++)
		for (register int j = 1; j <= m; j++)
			a[i][j] = readIn();
	for (register int i = 1; i <= n; i++)
		for (register int j = 1; j <= m; j++)
			b[i][j] = readIn();

	if (n == 2 && m == 2)
		RunInstance(cheat1);
	else if (m == 1)
		RunInstance(cheat2);
	else if (std::pow(m + 1, n) <= double(1e8))
		RunInstance(brute1);
}

int main()
{
#ifndef LOCAL
	freopen("chess.in", "r", stdin);
	freopen("chess.out", "w", stdout);
#endif
	run();
	return 0;
}