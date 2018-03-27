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
	int positive = true;
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

const double PI = std::acos(double(-1));
const int maxn = 15;
int n;
int t1 = true;
int r[maxn];

#define RunInstance(x) delete new x
struct cheat
{
	cheat()
	{
		int R = r[1];
		double S = std::sin(2 * PI / n) * R * R / 2 * n;
		printf("%.7f", S);
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
	for (int i = 1; i <= n; i++)
		r[i] = readIn();
	for (int i = 2; i <= n; i++)
		t1 &= (r[i] == r[i - 1]);

	if (t1)
		RunInstance(cheat);
}

int main()
{
#ifndef LOCAL
	freopen("yja.in", "r", stdin);
	freopen("yja.out", "w", stdout);
#endif
	run();
	return 0;
}
