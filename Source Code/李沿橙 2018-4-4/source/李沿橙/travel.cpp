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

const int mod = int(1e4) + 7;
const int maxn = int(1e5) + 5;
int n, c;
int a[maxn];
int b[maxn];
int p;

#define RunInstance(x) delete new x
struct brute
{
	brute()
	{
		while (p--)
		{
			int pos = readIn();
			int x = readIn();
			int y = readIn();
			a[pos] = x;
			b[pos] = y;


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
	c = readIn();
	for (int i = 1; i <= n; i++)
		a[i] = readIn();
	for (int i = 1; i <= n; i++)
		b[i] = readIn();
	p = readIn();

	if (n <= 1000)
		RunInstance(brute);
	else
		RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("travel.in", "r", stdin);
	freopen("travel.out", "w", stdout);
#endif
	run();
	return 0;
}