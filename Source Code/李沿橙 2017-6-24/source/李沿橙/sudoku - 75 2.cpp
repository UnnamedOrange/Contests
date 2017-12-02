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
struct Empty
{
	int x;
	int y;

	Empty(int x = 0, int y = 0) :x(x), y(y)
	{
	}
	bool operator< (const Empty& b) const
	{
		int areaA = area_(x, y);
		int areaB = area_(b.x, b.y);
		int ansA = 0;
		int ansB = 0;
		for (int i = 1; i <= 9; i++)
		{
			if (!sX[x][i] && !sY[y][i] && !sArea[areaA][i]) ansA++;
			if (!sX[b.x][i] && !sY[b.y][i] && !sArea[areaB][i]) ansB++;
		}
		return ansA < ansB;
	}
};
std::vector<Empty> empties;

void sudoku(int step = 0, int score = base)
{
	if (90 * (81 - filled) + score <= ans) return; //×îÓÅÐÔ¼ôÖ¦ 
	if (filled == 81)
	{
		ans = std::max(ans, score);
		return;
	}

	int x = empties[step].x, y = empties[step].y;
	int area = area_(x, y);

	for (int i = 1; i <= 9; i++)
	{
		if (!sX[x][i] && !sY[y][i] && !sArea[area][i])
		{
			rect[x][y] = i;
			sX[x][i] = sY[y][i] = sArea[area][i] = true;
			filled++;
			sudoku(step + 1, score + calcScore(x, y, i));
			rect[x][y] = 0;
			filled--;
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
					filled++;
					base += calcScore(x, y, t);
				}
				else
				{
					bOk = false;
					break;
				}
			}
		}
		if (!bOk) break;
	}
	if (!bOk)
	{
		printf("%d\n", ans);
		return 0;
	}

	for (int i = 1; i <= 9; i++)
	{
		for (int j = 1; j <= 9; j++)
		{
			if (!rect[i][j])
			{
				empties.push_back(Empty(i, j));
			}
		}
	}
	std::sort(empties.begin(), empties.end());
	sudoku();
	printf("%d\n", ans);
	return 0;
}