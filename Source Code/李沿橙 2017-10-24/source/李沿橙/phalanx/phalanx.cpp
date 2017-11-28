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
struct cheat1
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

	cheat1() : size(), Max(), Min()
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
struct cheat2
{
	INT sizeX, sizeY;
	INT Max[9][505][9][505];
	INT Min[9][505][9][505];

	void runRMQ()
	{
		while (1 << (sizeX + 1) < n) sizeX++;
		while (1 << (sizeY + 1) < n) sizeY++;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				Max[0][i][0][j] = Min[0][i][0][j] = rect[i][j];

		for (int i = 0; i <= sizeX; i++)
			for (int j = 0; j <= sizeY; j++)
			{
				if (!i && !j) continue;
				for (int x = 1; x + (1 << i) - 1 <= n; x++)
					for (int y = 1; y + (1 << j) - 1 <= m; y++)
					{
						if (!i)
						{
							Min[i][x][j][y] = std::min(Min[i][x][j - 1][y], Min[i][x][j - 1][y + (1 << (j - 1))]);
							Max[i][x][j][y] = std::max(Max[i][x][j - 1][y], Max[i][x][j - 1][y + (1 << (j - 1))]);
						}
						else
						{
							Min[i][x][j][y] = std::min(Min[i - 1][x][j][y], Min[i - 1][x + (1 << (i - 1))][j][y]);
							Max[i][x][j][y] = std::max(Max[i - 1][x][j][y], Max[i - 1][x + (1 << (i - 1))][j][y]);
						}
					}
			}

	}
	INT max(INT x1, INT y1, INT x2, INT y2)
	{
		INT x = x2 - x1 + 1;
		INT y = y2 - y1 + 1;
		INT kx = 0;
		INT ky = 0;
		while (1 << (kx + 1) < x) kx++;
		while (1 << (ky + 1) < y) ky++;
		return std::max(std::max(Max[kx][x1][ky][y1], Max[kx][x1][ky][y2 - (1 << ky) + 1]),
			std::max(Max[kx][x2 - (1 << kx) + 1][ky][y1], Max[kx][x2 - (1 << kx) + 1][ky][y2 - (1 << ky) + 1]));
	}
	INT min(INT x1, INT y1, INT x2, INT y2)
	{
		INT x = x2 - x1 + 1;
		INT y = y2 - y1 + 1;
		INT kx = 0;
		INT ky = 0;
		while (1 << (kx + 1) < x) kx++;
		while (1 << (ky + 1) < y) ky++;
		return std::min(std::min(Min[kx][x1][ky][y1], Min[kx][x1][ky][y2 - (1 << ky) + 1]),
			std::min(Min[kx][x2 - (1 << kx) + 1][ky][y1], Min[kx][x2 - (1 << kx) + 1][ky][y2 - (1 << ky) + 1]));
	}

	cheat2() : sizeX(), sizeY()
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

			if (buffer[2] == 'M') //sum
				printOut((long long)Sum[x2][y2] - Sum[x1 - 1][y2] - Sum[x2][y1 - 1] + Sum[x1 - 1][y1 - 1]);
			else if (buffer[2] == 'X') //max
				printOut(max(x1, y1, x2, y2));
			else if (buffer[2] == 'N') //min
				printOut(min(x1, y1, x2, y2));
		}
	}
};
struct cheat3
{
	INT sizeX, sizeY;
	short rmq[10][maxn][10][maxn];

	void runRMQ(bool bMax)
	{
		while (1 << (sizeX + 1) < n) sizeX++;
		while (1 << (sizeY + 1) < n) sizeY++;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				rmq[0][i][0][j] = rect[i][j];

		for (int i = 0; i <= sizeX; i++)
			for (int j = 0; j <= sizeY; j++)
			{
				if (!i && !j) continue;
				for (int x = 1; x + (1 << i) - 1 <= n; x++)
					for (int y = 1; y + (1 << j) - 1 <= m; y++)
					{
						if (!i)
						{
							if (bMax) rmq[i][x][j][y] = std::max(rmq[i][x][j - 1][y], rmq[i][x][j - 1][y + (1 << (j - 1))]);
							else rmq[i][x][j][y] = std::min(rmq[i][x][j - 1][y], rmq[i][x][j - 1][y + (1 << (j - 1))]);
						}
						else
						{
							if (bMax) rmq[i][x][j][y] = std::max(rmq[i - 1][x][j][y], rmq[i - 1][x + (1 << (i - 1))][j][y]);
							else rmq[i][x][j][y] = std::min(rmq[i - 1][x][j][y], rmq[i - 1][x + (1 << (i - 1))][j][y]);
						}
					}
			}

	}
	INT max(INT x1, INT y1, INT x2, INT y2)
	{
		INT x = x2 - x1 + 1;
		INT y = y2 - y1 + 1;
		INT kx = 0;
		INT ky = 0;
		while (1 << (kx + 1) < x) kx++;
		while (1 << (ky + 1) < y) ky++;
		return std::max(std::max(rmq[kx][x1][ky][y1], rmq[kx][x1][ky][y2 - (1 << ky) + 1]),
			std::max(rmq[kx][x2 - (1 << kx) + 1][ky][y1], rmq[kx][x2 - (1 << kx) + 1][ky][y2 - (1 << ky) + 1]));
	}
	INT min(INT x1, INT y1, INT x2, INT y2)
	{
		INT x = x2 - x1 + 1;
		INT y = y2 - y1 + 1;
		INT kx = 0;
		INT ky = 0;
		while (1 << (kx + 1) < x) kx++;
		while (1 << (ky + 1) < y) ky++;
		return std::min(std::min(rmq[kx][x1][ky][y1], rmq[kx][x1][ky][y2 - (1 << ky) + 1]),
			std::min(rmq[kx][x2 - (1 << kx) + 1][ky][y1], rmq[kx][x2 - (1 << kx) + 1][ky][y2 - (1 << ky) + 1]));
	}

	INT ans[500005];
	INT param[500005][5];

	cheat3() : sizeX(), sizeY()
	{
		for (int i = 1; i <= q; i++)
		{
			char buffer[5];
			scanf("%s", buffer);
			if (buffer[2] == 'M') //sum
				param[i][0] = 1;
			else if (buffer[2] == 'X') //max
				param[i][0] = 2;
			else if (buffer[2] == 'N') //min
				param[i][0] = 3;

			for (int j = 1; j <= 4; j++) param[i][j] = readIn() + 1;
		}
		runRMQ(true);
		for (int i = 1; i <= q; i++)
		{
			INT x1 = param[i][1];
			INT y1 = param[i][2];
			INT x2 = param[i][3];
			INT y2 = param[i][4];
			if (param[i][0] == 1) ans[i] = (long long)Sum[x2][y2] - Sum[x1 - 1][y2] - Sum[x2][y1 - 1] + Sum[x1 - 1][y1 - 1];
			else if (param[i][0] == 2) ans[i] = max(x1, y1, x2, y2);
		}
		runRMQ(false);
		for (int i = 1; i <= q; i++)
		{
			INT x1 = param[i][1];
			INT y1 = param[i][2];
			INT x2 = param[i][3];
			INT y2 = param[i][4];
			if (param[i][0] == 3) ans[i] = min(x1, y1, x2, y2);
		}

		for (int i = 1; i <= q; i++) printOut(ans[i]);
	}
};
struct work
{
	INT size;
	INT Max[10][maxn][maxn];
	INT Min[10][maxn][maxn];

	void runRMQ()
	{
		while (1 << (size + 1) < std::min(n, m)) size++;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				Max[0][i][j] = Min[0][i][j] = rect[i][j];

		for (int i = 1; i <= size; i++)
		{
			for (int x = 1; x + (1 << i) - 1 <= n; x++)
				for (int y = 1; y + (1 << i) - 1 <= m; y++)
				{
					Min[i][x][y] = std::min(std::min(Min[i - 1][x][y], Min[i - 1][x + (1 << (i - 1))][y]),
						std::min(Min[i - 1][x][y + (1 << (i - 1))], Min[i - 1][x + (1 << (i - 1))][y + (1 << (i - 1))]));


					Max[i][x][y] = std::max(std::max(Max[i - 1][x][y], Max[i - 1][x + (1 << (i - 1))][y]),
						std::max(Max[i - 1][x][y + (1 << (i - 1))], Max[i - 1][x + (1 << (i - 1))][y + (1 << (i - 1))]));
				}
		}

	}
	INT max(INT x1, INT y1, INT x2, INT y2)
	{
		INT x = x2 - x1 + 1;
		INT y = y2 - y1 + 1;
		INT k = 0;
		while (1 << (k + 1) < std::min(x, y)) k++;
		INT ret = 0;
		if (x > y)
		{
			INT base = x1;
			while (base + (1 << k) - 1 <= x2)
			{
				ret = std::max(ret, Max[k][base][y1]);
				base += 1 << k;
			}
			ret = std::max(ret, Max[k][x2 - (1 << k) + 1][y1]);

			base = x1;
			while (base + (1 << k) - 1 <= x2)
			{
				ret = std::max(ret, Max[k][base][y2 - (1 << k) + 1]);
				base += 1 << k;
			}
			ret = std::max(ret, Max[k][x2 - (1 << k) + 1][y2 - (1 << k) + 1]);
		}
		else
		{
			INT base = y1;
			while (base + (1 << k) - 1 <= y2)
			{
				ret = std::max(ret, Max[k][x1][base]);
				base += 1 << k;
			}
			ret = std::max(ret, Max[k][x1][y2 - (1 << k) + 1]);

			base = y1;
			while (base + (1 << k) - 1 <= y2)
			{
				ret = std::max(ret, Max[k][x2 - (1 << k) + 1][base]);
				base += 1 << k;
			}
			ret = std::max(ret, Max[k][x2 - (1 << k) + 1][y2 - (1 << k) + 1]);
		}
		return ret;
	}
	INT min(INT x1, INT y1, INT x2, INT y2)
	{
		INT x = x2 - x1 + 1;
		INT y = y2 - y1 + 1;
		INT k = 0;
		while (1 << (k + 1) < std::min(x, y)) k++;
		INT ret = INF;
		if (x > y)
		{
			INT base = x1;
			while (base + (1 << k) - 1 <= x2)
			{
				ret = std::min(ret, Min[k][base][y1]);
				base += 1 << k;
			}
			ret = std::min(ret, Min[k][x2 - (1 << k) + 1][y1]);

			base = x1;
			while (base + (1 << k) - 1 <= x2)
			{
				ret = std::min(ret, Min[k][base][y2 - (1 << k) + 1]);
				base += 1 << k;
			}
			ret = std::min(ret, Min[k][x2 - (1 << k) + 1][y2 - (1 << k) + 1]);
		}
		else
		{
			INT base = y1;
			while (base + (1 << k) - 1 <= y2)
			{
				ret = std::min(ret, Min[k][x1][base]);
				base += 1 << k;
			}
			ret = std::min(ret, Min[k][x1][y2 - (1 << k) + 1]);

			base = y1;
			while (base + (1 << k) - 1 <= y2)
			{
				ret = std::min(ret, Min[k][x2 - (1 << k) + 1][base]);
				base += 1 << k;
			}
			ret = std::min(ret, Min[k][x2 - (1 << k) + 1][y2 - (1 << k) + 1]);
		}
		return ret;
	}

	work() : size()
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

			if (buffer[2] == 'M') //sum
				printOut((long long)Sum[x2][y2] - Sum[x1 - 1][y2] - Sum[x2][y1 - 1] + Sum[x1 - 1][y1 - 1]);
			else if (buffer[2] == 'X') //max
				printOut(max(x1, y1, x2, y2));
			else if (buffer[2] == 'N') //min
				printOut(min(x1, y1, x2, y2));
		}
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

	//	if (q <= 100000)
	//		RunInstance(cheat1);
	//	else if(n <= 500 && m <= 500)
	//		RunInstance(cheat2);
	//	else
	//		RunInstance(cheat3);

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
