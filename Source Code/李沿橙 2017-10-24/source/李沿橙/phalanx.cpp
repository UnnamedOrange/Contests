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
	}
	else
	{
		char buffer[12];
		INT length = 0;
		while (x)
		{
			buffer[length++] = x % 10 + '0';
			x /= 10;
		}
		do
		{
			putchar(buffer[--length]);
		} while (length);
	}
	putchar('\n');
}

const INT INF = (~(INT(1) << (sizeof(INT) * 8 - 1)));
const INT maxn = 805;
INT n, m, q;
INT rect[maxn][maxn];

INT Sum[maxn][maxn];
void init()
{
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			Sum[i][j] = (long long)rect[i][j] + Sum[i - 1][j] + Sum[i][j - 1] - Sum[i - 1][j - 1];
		}
	}
}

#define RunInstance(x) delete new x
struct cheat
{
	INT size;
	INT Max[maxn][10][maxn];
	INT Min[maxn][10][maxn];

	void runRMQ()
	{
		while (1 << (size + 1) < m) size++;
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= m; j++)
				Max[i][0][j] = Min[i][0][j] = rect[i][j];

			for (int j = 1; j <= size; j++)
			{
				for (int k = 1; k + (1 << j) - 1 <= m; k++)
				{
					Max[i][j][k] = std::max(Max[i][j - 1][k], Max[i][j - 1][k + (1 << (j - 1))]);
					Min[i][j][k] = std::min(Min[i][j - 1][k], Min[i][j - 1][k + (1 << (j - 1))]);
				}
			}
		}
	}
	INT max(INT i, INT l, INT r, INT k)
	{
		return std::max(Max[i][k][l], Max[i][k][r - (1 << k) + 1]);
	}
	INT min(INT i, INT l, INT r, INT k)
	{
		return std::min(Min[i][k][l], Min[i][k][r - (1 << k) + 1]);
	}

	cheat() : size(), Max(), Min()
	{
		runRMQ();
		while (q--)
		{
			char buffer[5];
			scanf("%s", buffer);
			INT x1 = readIn() + 1;
			INT y1 = readIn() + 1;
			INT x2 = readIn() + 1;
			INT y2 = readIn() + 1;
			INT length;
			INT k;

			if (buffer[2] == 'M') //sum
			{
				printOut((long long)Sum[x2][y2] - Sum[x1 - 1][y2] - Sum[x2][y1 - 1] + Sum[x1 - 1][y1 - 1]);
			}
			else if (buffer[2] == 'X') //max
			{
				length = y2 - y1 + 1;
				k = 0;
				while (1 << (k + 1) < length) k++;
				INT ans = 0;
				for (int i = x1; i <= x2; i++) ans = std::max(ans, max(i, y1, y2, k));
				printOut(ans);
			}
			else if (buffer[2] == 'N') //min
			{
				length = y2 - y1 + 1;
				k = 0;
				while (1 << (k + 1) < length) k++;
				INT ans = INF;
				for (int i = x1; i <= x2; i++) ans = std::min(ans, min(i, y1, y2, k));
				printOut(ans);
			}
		}
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
	m = readIn();
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			rect[i][j] = readIn();
		}
	}
	q = readIn();
	init();

	if (q <= 100000)
		RunInstance(cheat);
	else
		RunInstance(work);
}

int main()
{
#ifndef JUDGE
	freopen("phalanx.in", "r", stdin);
	freopen("phalanx.out", "w", stdout);
#endif
	run();
	return 0;
}
