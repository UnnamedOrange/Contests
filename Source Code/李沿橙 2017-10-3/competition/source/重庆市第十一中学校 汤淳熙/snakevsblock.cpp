#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <climits>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <stack>
#include <ctime>
#include <cmath>
#include <cstring>
#include <string>
using namespace std;
const int MAXN = 205;

/*
	n 行 5 列的格子
		有砖块、豆豆，或啥都没有，对应了一个数值
		相邻格子之间可能有挡板


                    /^\/^\
                  _|__|  O|
         \/     /~     \_/ \
          \____|__________/  \
                 \_______      \
                         `\     \                 \
                           |     |                  \
                          /      /                    \
                         /     /                       \\
                       /      /                         \ \
                      /     /                            \  \
                    /     /             _----_            \   \
                   /     /           _-~      ~-_         |   |
                  (      (        _-~    _--_    ~-_     _/   |
                   \      ~-____-~    _-~    ~-_    ~-_-~    /
                     ~-_           _-~          ~-_       _-~
                        ~--______-~                ~-___-~
		蛇的初始长度为 4，


			吃豆豆增加长度
			撞墙减少长度
			得到相同分数


 */

const int DRT[][2] = {
	{ 1, 0 },
	{ -1, 0 },
	{ 0, 1 },
	{ 0, -1 }
};

int Map[MAXN][10], n, m;

struct Brute_1 {
	bool Through[MAXN][10];

	Brute_1(void)
	{


	}
};

inline bool IsLegal(int x, int y)
{
	if (x >= 1 && x <= n + 1 &&
		y >= 1 && y <= 5) return true;
	return false;
}

int Cost(int x)
{
	if (x > 0) return 1;
	else if (x == 0) return 0;
	else if (x < 0) return -1;
}

struct Brute_2 {
	int Left, Score, MaxScore;

	void End(int x)
	{
		if (x > MaxScore)
			MaxScore = x;
	}

    bool IsVis[MAXN][10];
    void Search(int x, int y)
    {
		for (int i = 0; i < 4; ++i) {
			if (IsLegal(x + DRT[i][0], y + DRT[i][1]) &&
				!IsVis[x + DRT[i][0]][y + DRT[i][1]]) {
				x += DRT[i][0];
                y += DRT[i][1];

                IsVis[x][y] = true;

                Left += Cost(Map[x][y]);
                Score += abs(Map[x][y]);

                if (Left < 0) {
                	if (Cost(Map[x][y]) == -1)
						End(Score - abs(Map[x][y]));
					else
						End(Score);
				} else if (x == n + 1)  {
					End(Score);
				} else Search(x, y);

				Score -= abs(Map[x][y]);
				Left -= Cost(Map[x][y]);

				x -= DRT[i][0];
                y -= DRT[i][1];
			}
		}
		IsVis[x][y] = false;
    }

	Brute_2(void) :
		Left(4), Score(0), MaxScore(INT_MIN), IsVis()
	{
		IsVis[1][3] = true;

        Search(1, 3);

        printf("%d\n",
			MaxScore);
	}
};

int main(void)
{
#ifndef LOCAL
	freopen("snakevsblock.in", "r", stdin);
	freopen("snakevsblock.out", "w", stdout);
#endif // LOCAL

	scanf("%d", &n);

    for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= 5; ++j)
			scanf("%d", &Map[i][j]);

	scanf("%d", &m);

	if (m == 0) delete new Brute_2();
	else if (n <= 5) delete new Brute_1();

	return 0;
}
