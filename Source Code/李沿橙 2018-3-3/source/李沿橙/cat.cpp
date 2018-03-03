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
#include <list>
#include <cassert>
#include <cctype>
#include <climits>
typedef long long LL;
typedef int INT_PUT;
INT_PUT readIn()
{
	INT_PUT a = 0;
	bool minus = false;
	char ch = getchar();
	if (!(ch == '-' || std::isdigit(ch))) ch = getchar();
	if (ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while (std::isdigit(ch))
	{
		a = a * 10 + (ch - '0');
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}
void printOut(INT_PUT x)
{
	char buffer[20];
	int length = 0;
	if (x < 0)
	{
		putchar('-');
		x = -x;
	}
	do
	{
		buffer[length++] = x % 10 + '0';
		x /= 10;
	} while (x);
	do
	{
		putchar(buffer[--length]);
	} while (length);
	putchar('\n');
}

const int maxn = int(2e5) + 5;
int n;
char str[maxn];

void initFailure(int* f, const char* t)
{
	f[0] = f[1] = 0;
	int cnt = 0;
	for (int i = 1; t[i] != '\0'; i++)
	{
		while (cnt && t[cnt] != t[i]) cnt = f[cnt];
		if (t[cnt] == t[i]) cnt++;
		f[i + 1] = cnt;
	}
}

#define RunInstance(x) delete new x
struct brute1
{
	static const int maxN = 55;

	int preMax[maxN][maxN];

	int f[maxN][maxN];
	int dp(int l, int r)
	{
		if (~f[l][r]) return f[l][r];
		int& ans = f[l][r];
		ans = 1;
		if (l == r) return ans;
		for (int i = l; i <= r; i++)
		{
			for (int j = 1; i + j - 1 <= r; j++)
			{
				if (preMax[l][j])
					ans = std::max(ans, dp(i, i + preMax[l][j] - 1) + 1);
			}
		}
		return ans;
	}

	brute1()
	{
		for (int i = 0; i < n; i++)
			initFailure(preMax[i], str + i);

		memset(f, -1, sizeof(f));
		int ans = 0;
		for (int i = 0; i < n; i++)
			for (int j = i; j < n; j++)
				ans = std::max(ans, dp(i, j));
		printOut(ans);
	}
};
struct brute2
{
	static const int maxN = 4005;
	int preMax[maxN][maxN];
	int f[maxN][maxN];

	brute2()
	{
		for (int i = 0; i < n; i++)
			initFailure(preMax[i], str + i);

		int ans = 0;
		for (int i = 0; i < n; i++)
		{
			f[i][0] = 0;
			for (int j = i; j < n; j++)
				ans = std::max(ans, f[i][j - i + 1] = f[i][preMax[i][j - i + 1]] + 1);
		}
		printOut(ans);
	}
};
struct cheat
{
	int preMax[maxn];

	int f[maxn];

	cheat()
	{
		initFailure(preMax, str);

		f[0] = 0;
		int ans = f[1] = 1;
		for (int i = 2; i <= n; i++)
		{
			f[i] = f[preMax[i]] + 1;
			ans = std::max(ans, f[i]);
		}
		printOut(ans);
	}
};

void run()
{
	scanf("%s", str);
	n = strlen(str);

	if (n <= 4000)
		RunInstance(brute2);
	else
		RunInstance(cheat);
}

int main()
{
#ifndef LOCAL
	freopen("cat.in", "r", stdin);
	freopen("cat.out", "w", stdout);
#endif
	run();
	return 0;
}