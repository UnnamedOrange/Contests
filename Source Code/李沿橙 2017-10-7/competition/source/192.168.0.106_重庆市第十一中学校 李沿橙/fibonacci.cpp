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
typedef long long INT;
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
	if(!x)
	{
		putchar('0');
	}
	else
	{
		char buffer[15];
		INT length = 0;
		while(x)
		{
			buffer[length++] = x % 10 + '0';
			x /= 10;
		}
		do
		{
			putchar(buffer[--length]);
		}
		while(length);
	}
	putchar('\n');
}

INT m;
#define RunInstance(x) delete new x
struct cheat1
{
	INT next[16];
	INT depth[16];

	INT LCA(INT x, INT y)
	{
		if(depth[x] < depth[y]) std::swap(x, y);
		while(depth[x] != depth[y]) x = next[x];
		while(x != y)
		{
			x = next[x];
			y = next[y];
		}
		return x;
	}

	cheat1() : next(), depth()
	{
		next[1] = 0;
		next[2] = 1;
		next[3] = 1;
		next[4] = 1;
		next[5] = 2;
		next[6] = 1;
		next[7] = 2;
		next[8] = 3;
		next[9] = 1;
		next[10] = 2;
		next[11] = 3;
		next[12] = 4;
		next[13] = 5;
		next[14] = 1;
		next[15] = 2;

		depth[1] = 1;
		depth[2] = 2;
		depth[3] = 2;
		depth[4] = 2;
		depth[5] = 3;
		depth[6] = 2;
		depth[7] = 3;
		depth[8] = 3;
		depth[9] = 2;
		depth[10] = 3;
		depth[11] = 3;
		depth[12] = 3;
		depth[13] = 4;
		depth[14] = 2;
		depth[15] = 3;

		while(m--)
		{
			printOut(LCA(readIn(), readIn()));
		}
	}
};
struct cheat2
{
	static const INT maxk = 20;
	static const INT maxn = 1000000;
	INT next[maxk + 1][maxn + 5];
	INT depth[maxn + 5];

	INT LCA(INT x, INT y)
	{
		if(depth[x] < depth[y]) std::swap(x, y);
		for(int i = maxk; ~i; i--)
		{
			if(depth[next[i][x]] >= depth[y]) x = next[i][x];
		}
		if(x != y)
		{
			for(int i = maxk; ~i; i--)
			{
				if(next[i][x] != next[i][y])
				{
					x = next[i][x];
					y = next[i][y];
				}
			}
			x = next[0][x];
		}
		return x;
	}

	cheat2() : next(), depth()
	{
		INT pre = 1;
		INT cnt = 1;
		INT count_ = 1;
		depth[1] = 1;
		while(count_ < maxn)
		{
			std::swap(cnt, pre);
			for(int i = 1; i <= cnt && count_ < maxn; i++)
			{
				next[0][++count_] = i;
				depth[count_] = depth[i] + 1;
			}
			cnt = count_;
		}

		for(int i = 1; i <= maxk; i++)
		{
			for(int j = 1; j <= maxn; j++)
			{
				next[i][j] = next[i - 1][next[i - 1][j]];
			}
		}

		while(m--)
		{
			printOut(LCA(readIn(), readIn()));
		}
	}
};
struct cheat3
{
	cheat3()
	{
		while(m--)
		{
			INT x = readIn();
			INT y = readIn();
			if(x == y) printOut(x);
			else printOut(1);
		}
	}
};
struct work
{

};

void run()
{
	m = readIn();
	if(m <= 12)
		RunInstance(cheat1);
	else if(m <= 1007)
		RunInstance(cheat2);
	else if(m % 10 == 9)
		RunInstance(cheat3);
	else
		RunInstance(work);
}

int main()
{
#ifndef JUDGE
	freopen("fibonacci.in", "r", stdin);
	freopen("fibonacci.out", "w", stdout);
#endif
	run();
	return 0;
}
