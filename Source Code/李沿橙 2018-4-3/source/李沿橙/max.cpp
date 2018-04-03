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
const int maxn = 45;
const int maxm = 15;
const int maxc = 5;
int n, m, c;
int p[maxm][maxn][maxc];

#define RunInstance(x) delete new x
struct brute
{
	int num[maxn];
	LL ans;
	void search(int depth, LL posib)
	{
		if (depth == m + 1)
		{
			ans = (ans + *std::max_element(num + 1, num + 1 + n) * posib) % mod;
			return;
		}
		for (int i = 1; i <= n; i++)
		{
			for (int j = 0; j <= c; j++)
			{
				num[i] += j;
				search(depth + 1, posib * p[depth][i][j] % mod);
				num[i] -= j;
			}
		}
	}

	brute() : ans(), num()
	{
		search(1, 1);
		printOut(ans);
	}
};
struct cheat
{
	cheat()
	{

	}
};

void run()
{
	n = readIn();
	m = readIn();
	c = readIn();
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++)
			for (int k = 0; k <= c; k++)
				p[i][j][k] = readIn();

	if (std::pow(n * (c + 1), m) <= 3e8)
		RunInstance(brute);
	else
		RunInstance(cheat);
}

int main()
{
#ifndef LOCAL
	freopen("max.in", "r", stdin);
	freopen("max.out", "w", stdout);
#endif
	run();
	return 0;
}