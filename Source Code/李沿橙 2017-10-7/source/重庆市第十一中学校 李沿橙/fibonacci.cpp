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
struct cheat
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

	cheat() : next(), depth()
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
struct work
{
	INT f[65];

	INT parent(INT x)
	{
		INT p = *(std::lower_bound(f + 1, f + 1 + 60, x) - 1);
		return x - p;
	}
	INT LCA(INT x, INT y)
	{
		while(x != y)
		{
			if(x > y) x = parent(x);
			else y = parent(y);
		}
		return x;
	}

	work()
	{
		f[1] = 1;
		f[2] = 1;
		for(int i = 3; i <= 60; i++)
		{
			f[i] = f[i - 1] + f[i - 2];
		}

		while(m--)
		{
			INT x = readIn();
			INT y = readIn();
			printOut(LCA(x, y));
		}
	}
};

void run()
{
	m = readIn();
//	if(m <= 1007)
//		RunInstance(cheat);
//	else
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
