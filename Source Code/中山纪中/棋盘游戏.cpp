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

INT t;
#define p(ch) putchar(ch)
#define a() { p('A'); p('m'); p('p'); p('h'); p('e'); p('t'); p('a'); p('m'); p('i'); p('n'); p('e'); p('\n'); }
#define b() { p('A'); p('l'); p('p'); p('h'); p('a'); p('g'); p('o'); p('\n'); }
#define swap(x, y) { t = x; x = y; y = t; }
INT x, y;

void run()
{
	double temp = (1 + sqrt(5)) / 2;
	INT T = readIn();
	while (T--)
	{
		x = readIn();
		y = readIn();
		if (y < x) swap(x, y);
		INT z = temp * (y - x);
		if (z == x) b()
		else a()
	}
}

int main()
{
	run();
	return 0;
}
