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
inline void printOut(INT x)
{
	if (!x)
	{
		putchar('0');
		return;
	}
	static char buffer[12];
	INT length = 0;
	bool minus = false;
	if (x < 0)
	{
		minus = true;
		x = -x;
	}
	while (x)
	{
		buffer[length++] = x % 10 + '0';
		x /= 10;
	}
	if (minus) buffer[length++] = '-';
	do
	{
		putchar(buffer[--length]);
	} while (length);
}

const INT maxn = 1005;
INT n, m, q;
INT rect[maxn][maxn];
struct RLIST
{
	INT x;
	INT y;
	INT right;
	INT bottom;
} pool[maxn * maxn];
#define Code(x, y) ((x) * (m + 1) + (y))

void init()
{
	for (int i = 0; i <= n; i++)
	{
		for (int j = 0; j <= m; j++)
		{
			static INT code = 0;
			pool[code].x = i;
			pool[code].y = j;
			if (i != n) pool[code].bottom = code + m + 1;
			if (j != m) pool[code].right = code + 1;
			code++;
		}
	}
}

INT X1, Y1, X2, Y2, width, height;
void toRight(INT& x, INT range)
{
	while (range--)
	{
		x = pool[x].right;
	}
}
void toBottom(INT& x, INT range)
{
	while (range--)
	{
		x = pool[x].bottom;
	}
}
void swapRight(INT pos1, INT pos2)
{
	for (int i = 1; i <= height; i++)
	{
		std::swap(pool[pos1].right, pool[pos2].right);
		pos1 = pool[pos1].bottom;
		pos2 = pool[pos2].bottom;
	}
}
void swapBottom(INT pos1, INT pos2)
{
	for (int i = 1; i <= width; i++)
	{
		std::swap(pool[pos1].bottom, pool[pos2].bottom);
		pos1 = pool[pos1].right;
		pos2 = pool[pos2].right;
	}
}
void work()
{
	INT pos1 = Code(0, Y1 + width - 1);
	INT pos2 = Code(0, Y2 + width - 1);
	INT pos3 = Code(X1 + height - 1, 0);
	INT pos4 = Code(X2 + height - 1, 0);
	INT pos5 = Code(0, Y1 - 1);
	INT pos6 = Code(0, Y2 - 1);
	INT pos7 = Code(X1 - 1, 0);
	INT pos8 = Code(X2 - 1, 0);
	toBottom(pos1, X1);
	toBottom(pos2, X2);
	toRight(pos3, Y1);
	toRight(pos4, Y2);
	toBottom(pos5, X1);
	toBottom(pos6, X2);
	toRight(pos7, Y1);
	toRight(pos8, Y2);

	swapRight(pos1, pos2);
	swapBottom(pos3, pos4);
	swapRight(pos5, pos6);
	swapBottom(pos7, pos8);
}

void run()
{
	n = readIn();
	m = readIn();
	q = readIn();
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			rect[i][j] = readIn();
		}
	}
	init();
	while (q--)
	{
		X1 = readIn();
		Y1 = readIn();
		X2 = readIn();
		Y2 = readIn();
		height = readIn();
		width = readIn();
		work();
	}

	for (int i = 1; i <= n; i++)
	{
		INT pos = Code(i, 0);
		for (int j = 1; j <= m; j++)
		{
			pos = pool[pos].right;
			printOut(rect[pool[pos].x][pool[pos].y]);
			putchar(' ');
		}
		putchar('\n');
	}
}

int main()
{
	run();
	return 0;
}
