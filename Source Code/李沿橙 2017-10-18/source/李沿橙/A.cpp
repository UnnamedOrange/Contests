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
		char buffer[8];
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
	putchar(' ');
}

const INT maxn = INT(1e6) + 10000;
INT n, m;

INT sign[maxn + 5];
INT good[maxn + 5];

void init()
{
	for (int i = 0; i <= maxn; i++)
	{
		if (i * 3 <= maxn) sign[i * 3] = sign[i];
		else break;
		if (i * 3 + 1 <= maxn) sign[i * 3 + 1] = sign[i] - 1;
		if (i * 3 + 2 <= maxn) sign[i * 3 + 2] = sign[i] + 1;
	}
	for (int i = 0; i <= maxn; i++)
	{
		if (!sign[i]) good[++good[0]] = i;
	}
}

void run()
{
	init();
	INT T = readIn();
	while (T--)
	{
		n = readIn();
		m = readIn();

		INT idx = std::lower_bound(good + 1, good + 1 + good[0], n) - good;
		while (m--)
		{
			printOut(good[idx++]);
		}
		putchar('\n');
	}
}

int main()
{
#ifndef JUDGE
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	run();
	return 0;
}
