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
#include <functional>
typedef int INT;
using std::cin;
using std::cout;
using std::endl;
inline INT readIn()
{
	INT a = 0;
	bool minus = false;
	char ch = getchar();
	while (!(ch == '-' || (ch >= '0' && ch <= '9'))) ch = getchar();
	if (ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		a = a * 10 + ch - '0';
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
		bool minus = x < 0;
		if (minus) x = -x;
		char buffer[12];
		INT length = 0;
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
	putchar('\n');
}

const INT INF = (~(INT(1) << (sizeof(INT) * 8 - 1))) >> 1;
INT T;
INT n;
INT A, B;

#define RunInstance(x) delete new x
struct cheat
{
	INT calc(INT a, INT b, INT x)
	{
		if (!a && !b) return -x;
		if (!a && b) return -x - b;
		if (a && !b) return x + a;

		if (x)
		{
			return std::max(-x - calc(b, a, 0), -calc(b, a - 1, x + 1));
		}
		else
		{
			return -calc(b, a - 1, 1);
		}
	}

	cheat()
	{
		while (T--)
		{
			A = readIn();
			B = readIn();
			printOut(calc(A, B, 0));
		}
	}
};
struct work
{
	INT calc(INT a, INT b)
	{
		if (!a && !b) return 0;
		if (!a && b) return -b;
		if (a && !b) return a;

		return a - b - 2;
	}

	work()
	{
		while (T--)
		{
			A = readIn();
			B = readIn();
			printOut(calc(A, B));
		}
	}
};

void run()
{
	T = readIn();
	if (T <= 1)
		RunInstance(cheat);
	else
		RunInstance(work);
}

int main()
{
#ifndef JUDGE
	freopen("deep.in", "r", stdin);
	freopen("deep.out", "w", stdout);
#endif
	run();
	return 0;
}
