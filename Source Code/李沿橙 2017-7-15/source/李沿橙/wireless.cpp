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
typedef long long INT;
int readIn()
{
	bool minus = false;
	int a = 0;
	int ch = getchar();
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
	if(minus) a = -a;
	return a;
}

const int maxn = 135;
const int width = 129; //recode, from 1
int d, n;
INT rect[maxn][maxn];

void run()
{
	d = readIn();
	n = readIn();
	for (int i = 1; i <= n; i++)
	{
		int x = readIn() + 1;
		int y = readIn() + 1;
		rect[x][y] = readIn();
	}

	for (int x = 1; x <= width; x++)
	{
		for (int y = 1; y <= width; y++)
		{
			rect[x][y] += rect[x - 1][y] + rect[x][y - 1] - rect[x - 1][y - 1];
		}
	}

	int count_ = 0;
	INT maxi = 0;
	for (int x = 1; x <= width; x++)
	{
		for (int y = 1; y <= width; y++)
		{
			int left = std::max(x - d, 1);
			int right = std::min(x + d, width);
			int top = std::max(y - d, 1);
			int bottom = std::min(y + d, width);
			INT temp = rect[right][bottom] - rect[left - 1][bottom] - rect[right][top - 1] + rect[left - 1][top - 1];
			if (temp > maxi)
			{
				count_ = 1;
				maxi = temp;
			}
			else if (temp == maxi)
			{
				count_++;
			}
		}
	}
	cout << count_ << " " << maxi << endl;
}

int main()
{
	run();
	return 0;
}
