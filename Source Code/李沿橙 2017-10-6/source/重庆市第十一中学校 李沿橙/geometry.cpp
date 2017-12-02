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
	if(!x)
	{
		putchar('0');
	}
	else
	{
		char buffer[8];
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

double EPS = 1e-10;
const INT maxn = INT(1e5) + 5;
INT n, m;
INT x[maxn];
INT y[maxn];
INT qx, qy;

INT dcmp(double x)
{
	if(std::abs(x) <= EPS) return 0;
	return x < 0 ? -1 : 1;
}

bool check(INT s)
{
	if(!s) return true;
	double stdY = (double)y[s] * (x[s] - qx) / x[s];
	return dcmp(qy - stdY) >= 0;
}

void run()
{
	n = readIn();
	for(int i = 1; i <= n; i++) x[i] = readIn();
	for(int i = 1; i <= n; i++) y[i] = readIn();
	std::sort(x + 1, x + 1 + n);
	std::sort(y + 1, y + 1 + n);
	m = readIn();
	while(m--)
	{
		qx = readIn();
		qy = readIn();

		INT l = 0, r = n + 1;
		while(r - l > 1)
		{
			INT mid = l + ((r - l) >> 1);
			if(check(mid))
				l = mid;
			else
				r = mid;
		}
		printOut(l);
	}
}

int main()
{
#ifndef JUDGE
	freopen("geometry.in", "r", stdin);
	freopen("geometry.out", "w", stdout);
#endif
	run();
	return 0;
}
