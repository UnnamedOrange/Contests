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
#define FOR(i, f, t) for(int i = (f); i <= (t); i++)
inline int readIn()
{
	int a;
	scanf("%d", &a);
	return a;
}

const int maxn = 1005;
int n, m;
int origin[maxn][maxn];
int rect[maxn][maxn];

void run()
{
	n = readIn();
	m = readIn();
	FOR(i, 1, n)
	{
		FOR(j, 1, m)
		{
			origin[i][j] = readIn();
		}
	}

	FOR(i, 1, n)
	{
		rect[i][1] = origin[i][1];
		rect[i][m] = origin[i][m];
	}
	FOR(i, 1, m)
	{
		rect[1][i] = origin[1][i];
		rect[n][i] = origin[n][i];
	}

	FOR(i, 2, n - 1)
	{
		FOR(j, 2, m - 1)
		{
			int sum = origin[i][j] + origin[i-1][j] + origin[i+1][j] + origin[i][j-1] + origin[i][j+1];
			//ËÄÉáÎåÈë£¡
			rect[i][j] = double(sum) / 5 + 0.5;
		}
	}

	FOR(i, 1, n)
	{
		bool bPrinted = false;
		FOR(j, 1, m)
		{
			printf("%s%d", bPrinted ? " " : "", rect[i][j]);
			bPrinted = true;
		}
		puts("");
	}
}

int main()
{
	run();
	return 0;
}
