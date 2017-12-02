#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
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

const int maxn = 15;
int rect[maxn][maxn];
bool sX[maxn][maxn];
bool sY[maxn][maxn];
bool sArea[maxn][maxn];
int ans = -1;
int base;
int count_;

inline calcScore(int x, int y, int num)
{
	x = abs(x - 5);
	y = abs(y - 5);
	return (10 - std::max(x, y))*num;
}
inline area(int x, int y)
{
	x--;
	y--;
	return x / 3 * 3 + y / 3;
}

void sudoku(int x = 1, int y = 1, int score = base)
{
	if (count_ == 81)
	{
		ans = std::max(ans, score);
		return;
	}
	if (rect[x][y])
	{
		sudoku(x % 9 + 1, y + (x / 9), score);
		return;
	}
	int Area = area(x, y);
	for (int i = 1; i <= 9; i++)
	{
		if (!sX[x][i] && !sY[y][i] && !sArea[Area][i])
		{
			sX[x][i] = sY[y][i] = sArea[Area][i] = true;
			count_++;
			sudoku(x % 9 + 1, y + (x / 9), score + calcScore(x, y, i));
			count_--;
			sX[x][i] = sY[y][i] = sArea[Area][i] = false;
		}
	}
}

int main()
{
	for (int i = 1; i <= 9; i++)
	{
		for (int j = 1; j <= 9; j++)
		{
			rect[i][j] = readIn();
			int& t = rect[i][j];
			if (t)
			{
				sX[i][t] = true;
				sY[j][t] = true;
				sArea[area(i, j)][t] = true;
				base += calcScore(i, j, t);
				count_++;
			}
		}
	}
	sudoku();
	printf("%d\n", ans);
	return 0;
}