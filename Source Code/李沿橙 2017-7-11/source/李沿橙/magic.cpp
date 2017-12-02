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
inline int readIn()
{
	int a;
	scanf("%d", &a);
	return a;
}

const int maxn = 45;
int n;
int rect[maxn][maxn];
int x, y;

void run()
{
	n = readIn();
	x = 0;
	y = n / 2;
	int to = n * n;
	for(int i = 1; i <= to; i++)
	{
		rect[x][y] = i;

		if(x == 0 && y < n - 1)
		{
			x = n - 1;
			y++;
		}
		else if(x > 0 && y == n - 1)
		{
			x--;
			y = 0;
		}
		else if(x == 0 && y == n - 1)
		{
			x++;
		}
		else if(!rect[x - 1][y + 1])
		{
			x--;
			y++;
		}
		else
		{
			x++;
		}
	}

	for(int i = 0; i < n; i++)
	{
		printf("%d", rect[i][0]);
		for(int j = 1; j < n; j++)
		{
			printf(" %d", rect[i][j]);
		}
		puts("");
	}
}

int main()
{
	run();
	return 0;
}
