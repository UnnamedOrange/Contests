#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cassert>
#include <cctype>
#include <climits>
#include <ctime>
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
#include <list>
#include <functional>
typedef long long LL;
typedef unsigned long long ULL;
using std::cin;
using std::cout;
using std::endl;
typedef int INT_PUT;
INT_PUT readIn()
{
	INT_PUT a = 0;
	bool positive = true;
	char ch = getchar();
	while (!(ch == '-' || std::isdigit(ch))) ch = getchar();
	if (ch == '-')
	{
		positive = false;
		ch = getchar();
	}
	while (std::isdigit(ch))
	{
		a = a * 10 - (ch - '0');
		ch = getchar();
	}
	if (positive) a = -a;
	return a;
}
void printOut(INT_PUT x)
{
	char buffer[20];
	int length = 0;
	if (x < 0)
		putchar('-');
	else
		x = -x;
	do buffer[length++] = -(x % 10) + '0';
	while (x /= 10);
	do putchar(buffer[--length]);
	while (length);
}

int T;
int t;

int m[5005];
int num[305][5005];
inline int gcd(int x, int y)
{
	return !y ? x : gcd(y, x % y);
}

void run()
{
	T = readIn();
	t = readIn();
	for(register int i = 1; i <= t; i++)
	{
		num[i][0] = readIn();
		m[i] = readIn();
		for(register int j = 1, to = num[i][0]; j <= to; j++)
			num[i][j] = readIn();
	}

	int t = num[1][1];
	for(register int i = 1; i <= t; i++)
		for(register int j = 1, to = num[i][0]; j <= to; j++)
			t = gcd(t, num[i][j]);
	if (T == 1)
		printOut(t);
}

int main()
{
#ifndef LOCAL
	freopen("number.in", "r", stdin);
	freopen("number.out", "w", stdout);
#endif
	run();
	return 0;
}
