#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cassert>
#include <climits>
#include <cctype>
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
typedef LL INT_PUT;
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
	if (x < 0) putchar('-');
	else x = -x;
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
}

const int maxn = 200005;
int n, l;
struct Event
{
	LL time;
	LL x;
	LL y;
	void read()
	{
		time = readIn();
		x = readIn();
		y = readIn();
	}
} events[maxn];

#define RunInstance(x) delete new x
struct brute
{
	brute()
	{
		int U = (1 << (n << 1));
		for (int S = 0; S < U; S++)
		{
			int vecx[] = { 1, -1, 0, 0 };
			int vecy[] = { 0, 0, 1, -1 };
			char name[] = "RLUD";
			int ins[20];
			ins[0] = 0;
			int t = S;
			for (int i = 1; i <= l; i++)
			{
				ins[++ins[0]] = t & 3;
				t >>= 2;
			}
			LL accumx = 0;
			LL accumy = 0;
			for (int i = 1; i <= l; i++)
			{
				accumx += vecx[ins[i]];
				accumy += vecy[ins[i]];
			}

			bool bOk = true;
			for (int i = 1; i <= n; i++)
			{
				LL div = events[i].time / l;
				LL tx = div * accumx;
				LL ty = div * accumy;
				LL mod = events[i].time - l * div;
				for (int j = 1; j <= mod; j++)
				{
					tx += vecx[ins[j]];
					ty += vecy[ins[j]];
				}
				if (tx != events[i].x || ty != events[i].y)
				{
					bOk = false;
					break;
				}
			}
			if (bOk)
			{
				for (int i = 1; i <= l; i++)
					putchar(name[ins[i]]);
				return;
			}
		}
		puts("NO");
	}
};
struct work
{
	work()
	{

	}
};

void run()
{
	n = readIn();
	l = readIn();
	for (int i = 1; i <= n; i++)
		events[i].read();

	if (l <= 10)
		RunInstance(brute);
	else
		RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("dasuan.in", "r", stdin);
	freopen("dasuan.out", "w", stdout);
#endif
	run();
	return 0;
}