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
INT readIn()
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
		a = a * 10 + (ch - '0');
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}
void printOut(INT x)
{
	char buffer[20];
	INT length = 0;
	bool minus = x < 0;
	if (minus) x = -x;
	do
	{
		buffer[length++] = x % 10 + '0';
		x /= 10;
	} while (x);
	if (minus) buffer[length++] = '-';
	do
	{
		putchar(buffer[--length]);
	} while (length);
	putchar('\n');
}

const INT maxn = 100005;
INT n;
INT a[maxn];

void run()
{
	INT T = readIn();
	while (T--)
	{
		n = readIn();
		for (int i = 1; i <= n; i++)
			a[i] = readIn();

		INT cnt = n;
		for (int i = n; i >= 1; i--)
			if (a[i] == cnt)
				cnt--;

		printOut(cnt);
	}
}

int main()
{
#ifndef LOCAL
	freopen("book.in", "r", stdin);
	freopen("book.out", "w", stdout);
#endif
	run();
	return 0;
}
