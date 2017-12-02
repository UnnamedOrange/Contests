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
using std::cin;
using std::cout;
using std::endl;
typedef int INT;
inline INT readIn()
{
	INT a = 0;
	bool minus = false;
	char ch = getchar();
	while (!(ch == '-' || ch >= '0' && ch <= '9')) ch = getchar();
	if (ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		a *= 10;
		a += ch;
		a -= '0';
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}

const INT maxn = 205;
const INT maxk = 10010;
INT n, m;
INT rect[maxn][6];
INT block[maxn][6];

#define RunInstance(x) delete new x
struct cheat
{
	INT ans;
	INT vis[maxn][6];

	void DFS(INT x, INT y, INT HP, INT score)
	{
		vis[x][y]++;
		if(y != 1 && !block[x][y - 1] && vis[x][y - 1] < 2)
		{
			INT newX = x;
			INT newY = y - 1;
			INT newHP = HP + rect[newX][newY];
			INT newScore = score + (rect[newX][newY] < 0 ? -rect[newX][newY] : 0);

			if(newHP < 0)
			{
				ans = std::max(ans, score);
			}
			else
			{
				INT temp = rect[newX][newY];
				rect[newX][newY] = 0;
				if(!temp) vis[x][y]++;
				DFS(newX, newY, newHP, newScore);
				if(!temp) vis[x][y]--;
				rect[newX][newY] = temp;
			}
		}
		if(y != 5 && !block[x][y + 1] && vis[x][y + 1] < 2)
		{
			INT newX = x;
			INT newY = y + 1;
			INT newHP = HP + rect[newX][newY];
			INT newScore = score + (rect[newX][newY] < 0 ? -rect[newX][newY] : 0);

			if(newHP < 0)
			{
				ans = std::max(ans, score);
			}
			else
			{
				INT temp = rect[newX][newY];
				rect[newX][newY] = 0;
				if(!temp) vis[x][y]++;
				DFS(newX, newY, newHP, newScore);
				if(!temp) vis[x][y]--;
				rect[newX][newY] = temp;
			}
		}
		{
			if(x == n)
			{
				ans = std::max(ans, score);
			}
			else
			{
				INT newX = x + 1;
				INT newY = y;
				INT newHP = HP + rect[newX][newY];
				INT newScore = score + (rect[newX][newY] < 0 ? -rect[newX][newY] : 0);

				if(newHP < 0)
				{
					ans = std::max(ans, score);
				}
				else
				{
					INT temp = rect[newX][newY];
					rect[newX][newY] = 0;
					DFS(newX, newY, newHP, newScore);
					rect[newX][newY] = temp;
				}
			}
		}
		vis[x][y]--;
	}

	cheat() : ans(), vis()
	{
		DFS(1, 3, 4, 0);
		cout << ans << endl;
	}
};
struct work : cheat
{
	work()
	{

	}
};

void run()
{
	n = readIn();
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= 5; j++)
		{
			rect[i][j] = readIn();
		}
	}
	m = readIn();
	for(int i = 1; i <= m; i++)
	{
		INT x = readIn();
		INT y = readIn();
		block[x][y] = true;
	}
	if(n <= 5) RunInstance(cheat);
	else RunInstance(work);
}

int main()
{
#ifndef JUDGE
	freopen("snakevsblock.in", "r", stdin);
	freopen("snakevsblock.out", "w", stdout);
#endif
	run();
	return 0;
}
