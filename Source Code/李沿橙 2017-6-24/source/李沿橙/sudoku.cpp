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
int countX[maxn];
int filled;
int base;
int ans = -1;

inline int calcScore(int x, int y, int num)
{
	x = abs(x - 5);
	y = abs(y - 5);
	return (10 - std::max(x, y))*num;
}
inline int area_(int x, int y)
{
	x--;
	y--;
	return x / 3 * 3 + y / 3;
}

void sudoku(int score = base)
{
	if (90 * (81 - filled) + score <= ans) return; //最优性剪枝 
	if (filled == 81)
	{
		ans = std::max(ans, score);
		return;
	}

	int x = 0, y = 0;
	int area = 0;
	int maxVal = 0; //找到能填的数最少的那一个格子
	for (int i = 1; i <= 9; i++)
	{
		if (countX[i] == 9) continue; //这一行都已经填满了，不用在这一行里找
		for (int j = 1; j <= 9; j++)
		{
			if (rect[i][j]) continue;
			int tempCount = 0;
			int tempArea = area_(i, j);
			for (int k = 1; k <= 9; k++)
			{
				if (!(!sX[i][k] && !sY[j][k] && !sArea[tempArea][k]))
				{
					tempCount++;
				}
			}
			if (tempCount == 9) return;
			if (tempCount > maxVal)
			{
				x = i;
				y = j;
				area = tempArea;
				maxVal = tempCount;
			}
		}
	}
	for (int i = 1; i <= 9; i++)
	{
		if (!sX[x][i] && !sY[y][i] && !sArea[area][i])
		{
			rect[x][y] = i;
			sX[x][i] = sY[y][i] = sArea[area][i] = true;
			filled++;
			countX[x]++;
			sudoku(score + calcScore(x, y, i));
			rect[x][y] = 0;
			filled--;
			countX[x]--;
			sX[x][i] = sY[y][i] = sArea[area][i] = false;
		}
	}
}

int main()
{
	bool bOk = true;
	for (int i = 1; i <= 9; i++)
	{
		for (int j = 1; j <= 9; j++)
		{
			int x = i;
			int y = j;
			int area = area_(x, y);
			rect[x][y] = readIn();
			int& t = rect[x][y];
			if (t)
			{
				if (!sX[x][t] && !sY[y][t] && !sArea[area][t])
				{
					sX[x][t] = true;
					sY[y][t] = true;
					sArea[area][t] = true;
					countX[x]++;
					filled++;
					base += calcScore(x, y, t);
				}
				else
				{
					bOk = false;
					//进行预判，如果给定的数据都已经非法，则不要填数了
					break;
				}
			}
		}
		if (!bOk) break;
	}
	if (bOk) sudoku();
	printf("%d\n", ans);
	return 0;
}