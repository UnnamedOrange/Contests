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
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
	putchar('\n');
}

const int maxn = int(2e5) + 5;
int n, q;
int a[maxn];

#define RunInstance(x) delete new x
struct brute
{
	brute()
	{
		while (q--)
		{
			int type = readIn();
			int l = readIn();
			int r = readIn();
			if (type == 1)
			{
				int x = readIn();
				for (int i = l; i <= r; i++)
					a[i] &= x;
			}
			else if (type == 2)
			{
				int x = readIn();
				for (int i = l; i <= r; i++)
					a[i] |= x;
			}
			else if (type == 3)
			{
				int ans = 0;
				for (int i = l; i <= r; i++)
					ans = std::max(ans, a[i]);
				printOut(ans);
			}
		}
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
	q = readIn();
	for (int i = 1; i <= n; i++)
		a[i] = readIn();

	if (n <= 5000 && q <= 5000)
		RunInstance(brute);
	else
		RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("sequence.in", "r", stdin);
	freopen("sequence.out", "w", stdout);
#endif
	run();
	return 0;
}