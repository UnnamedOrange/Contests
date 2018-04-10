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
		(a *= 10) -= ch - '0';
		ch = getchar();
	}
	return positive ? -a : a;
}
void printOut(INT_PUT x)
{
	char buffer[20];
	int length = 0;
	if (x < 0) putchar('-');
	else x = -x;
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
}

const int maxn = 1005;
int n;
struct Point
{
	int x, y;
	void read() { x = readIn(); y = readIn(); }
} up[maxn], down[maxn];

#define RunInstance(x) delete new x
struct cheat1
{
	cheat1()
	{
		long double ans = 0;
		ans = (LL)(up[1].x - down[1].x) * (up[1].x - down[1].x) + (LL)(up[1].y - down[1].y) * (up[1].y - down[1].y);
		ans = std::sqrt(ans);
		printf("%.11Lf", ans);
	}
};

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
		up[i].read();
	for (int i = 1; i <= n; i++)
		down[i].read();
	
	if(n == 1)
		RunInstance(cheat1);
	
}

int main()
{
#ifndef LOCAL
	freopen("geometry.in", "r", stdin);
	freopen("geometry.out", "w", stdout);
#endif
	run();
	return 0;
}
