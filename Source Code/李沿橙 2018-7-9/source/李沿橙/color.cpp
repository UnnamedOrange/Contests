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
	while (!(std::isdigit(ch) || ch == '-')) ch = getchar();
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
}

const int maxn = 35;
int n;
char rect[maxn][maxn];

#define RunInstance(x) delete new x
struct brute
{
	int fill[maxn][maxn];
	bool check(int x, int y)
	{
		if (fill[x - 1][y - 1] == 0 &&
			fill[x - 1][y] == 0 &&
			fill[x][y - 1] == 0 &&
			fill[x][y] == 0)
			return false;
		if (fill[x - 1][y - 1] == 0 &&
			fill[x - 1][y] == 1 &&
			fill[x][y - 1] == 1 &&
			fill[x][y] == 0)
			return false;
		if (fill[x - 1][y - 1] == 1 &&
			fill[x - 1][y] == 0 &&
			fill[x][y - 1] == 0 &&
			fill[x][y] == 1)
			return false;
		if (fill[x - 1][y - 1] == 1 &&
			fill[x - 1][y] == 1 &&
			fill[x][y - 1] == 1 &&
			fill[x][y] == 1)
			return false;
		return true;
	}
	bool bFound;
	void search(int x, int y)
	{
		if (x == n)
		{
			if (check(n, n))
				bFound = true;
			return;
		}
		int newx = x;
		int newy = y + 1;
		if (newy == n)
		{
			newx++;
			newy = 2;
		}

		if (rect[x][y] == rect[x - 1][y] &&
			rect[x][y] == rect[x][y - 1])
		{
			if (fill[x - 1][y] != fill[x][y - 1])
				return;
			fill[x][y] = fill[x - 1][y];
			if (check(x, y) && (y != n - 1 || check(x, n)) && (x != n - 1 || check(n, y)))
				search(newx, newy);
		}
		else if (rect[x][y] == rect[x - 1][y])
		{
			fill[x][y] = fill[x - 1][y];
			if (check(x, y) && (y != n - 1 || check(x, n)) && (x != n - 1 || check(n, y)))
				search(newx, newy);
		}
		else if (rect[x][y] == rect[x][y - 1])
		{
			fill[x][y] = fill[x][y - 1];
			if (check(x, y) && (y != n - 1 || check(x, n)) && (x != n - 1 || check(n, y)))
				search(newx, newy);
		}
		else
		{
			fill[x][y] = 0;
			if (check(x, y) && (y != n - 1 || check(x, n)) && (x != n - 1 || check(n, y)))
				search(newx, newy);
			if (bFound) return;
			fill[x][y] = 1;
			if (check(x, y) && (y != n - 1 || check(x, n)) && (x != n - 1 || check(n, y)))
				search(newx, newy);
		}
	}

	brute() : fill(), bFound()
	{
		for (int i = 1; i <= n; i++)
		{
			fill[1][i] = rect[1][i] - '0';
			fill[i][1] = rect[i][1] - '0';
			fill[n][i] = rect[n][i] - '0';
			fill[i][n] = rect[i][n] - '0';
		}
		search(2, 2);
		puts(bFound ? "YES" : "NO");
	}
};

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			char ch = getchar();
			while (!(std::isdigit(ch) || std::isalpha(ch))) ch = getchar();
			rect[i][j] = ch;
		}
	}

	RunInstance(brute);
}

int main()
{
#ifndef LOCAL
	freopen("color.in", "r", stdin);
	freopen("color.out", "w", stdout);
#endif
	run();
	return 0;
}