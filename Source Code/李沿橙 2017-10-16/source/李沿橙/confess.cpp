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

const INT maxn = INT(6e3) + 5;
INT n;
INT length;
char origin[maxn][2 * maxn / 6 + 5];

#define RunInstance(x) delete new x
struct cheat
{
	static const INT maxN = 1005;
	static const INT width = 32;
	unsigned int sets[maxN][(2 * maxN + width - 1) / width];

	INT N;

	INT count(INT x, INT y)
	{
		static INT count1[1 << 16];
		if (!count1[1])
		{
			for (int i = 1; i < 1 << 16; i++)
			{
				count1[i] = count1[i ^ (i & -i)] + 1;
			}
		}

		INT ret = 0;
		for (int i = 0; i < N; i++)
		{
			unsigned int num = sets[x][i] & sets[y][i];
			ret += count1[num & ((1 << 16) - 1)] + count1[num >> 16];
		}
		return ret;
	}

	cheat() : sets(), N((length * 6 + width - 1) / width)
	{
		for (int i = 1; i <= n + 1; i++)
		{
			for (int j = 0; j < length; j++)
			{
				INT num = origin[i][j] - 33;
				for (int k = 0; k < 6; k++)
				{
					INT idx = j * 6 + k;
					INT major = idx / width;
					INT minor = idx % width;
					if (num & (1 << (5 - k))) sets[i][major] |= (1 << minor);
				}
			}
		}

		for (int i = 1; i <= n + 1; i++)
		{
			for (int j = i + 1; j <= n + 1; j++)
			{
				INT c = count(i, j);
				if (c >= n >> 1)
				{
					cout << i << " " << j << endl;
					return;
				}
			}
		}

		cout << "NO Solution" << endl;
	}
};
struct work
{
	static const INT maxN = 6005;
	static const INT width = 32;
	unsigned int sets[maxN][(2 * maxN + width - 1) / width];

	INT N;

	INT count(INT x, INT y)
	{
		static INT count1[1 << 16];
		if (!count1[1])
		{
			for (int i = 1; i < 1 << 16; i++)
			{
				count1[i] = count1[i ^ (i & -i)] + 1;
			}
		}

		INT ret = 0;
		for (int i = 0; i < N; i++)
		{
			unsigned int num = sets[x][i] & sets[y][i];
			ret += count1[num & ((1 << 16) - 1)] + count1[num >> 16];
		}
		return ret;
	}

	work() : sets(), N((length * 6 + width - 1) / width)
	{
		for (int i = 1; i <= n + 1; i++)
		{
			for (int j = 0; j < length; j++)
			{
				INT num = origin[i][j] - 33;
				for (int k = 0; k < 6; k++)
				{
					INT idx = j * 6 + k;
					INT major = idx / width;
					INT minor = idx % width;
					if (num & (1 << (5 - k))) sets[i][major] |= (1 << minor);
				}
			}
		}

		for (int i = 1; i <= 200000; i++)
		{
			INT x = rand() % (n + 1) + 1;
			INT y = rand() % (n + 1) + 1;
			if (x == y) continue;
			if (count(x, y) >= n >> 1)
			{
				cout << x << " " << y << endl;
				return;
			}
		}
		cout << "NO Solution" << endl;
	}
};

void run()
{
	n = readIn();
	for (int i = 1; i <= n + 1; i++)
	{
		scanf("%s", origin[i]);
	}
	length = strlen(origin[1]);
	if (n <= 1005) RunInstance(cheat);
	else
		RunInstance(work);
}

int main()
{
#ifndef JUDGE
	freopen("confess.in", "r", stdin);
	freopen("confess.out", "w", stdout);
#endif
	run();
	return 0;
}
