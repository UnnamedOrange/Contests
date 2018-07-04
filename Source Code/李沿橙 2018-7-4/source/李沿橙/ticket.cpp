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
	while (!(std::isdigit(ch) || ch == '-')) ch = getchar();
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
	putchar('\n');
}

const int maxn = int(2e5) + 5;
const int maxm = int(1e5) + 5;
int n, m;
struct People
{
	int a, b, c;
	void read()
	{
		a = readIn();
		b = readIn();
		c = readIn();
		if (a > b) std::swap(a, b);
	}
} peoples[maxm];

#define RunInstance(x) delete new x
struct brute1
{
	static const int maxN = 25;
	int times[maxN];

	brute1()
	{
		int U = 1 << m;
		int ans = m;
		for (int S = 0; S < U; S++)
		{
			std::memset(times, 0, sizeof(times));
			for (int i = 1; i <= m; i++)
			{
				const People& p = peoples[i];
				if (S & (1 << (i - 1)))
				{
					for (int j = p.a; j < p.b; j++)
						times[j]++;
				}
				else
				{
					for (int j = p.b; j <= n; j++)
						times[j]++;
					for (int j = 1; j < p.a; j++)
						times[j]++;
				}
			}
			ans = std::min(ans, *std::max_element(times + 1, times + 1 + n));
		}
		printOut(ans);
	}
};
struct brute2
{
	brute2()
	{

	}
};

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= m; i++)
		peoples[i].read();

	if (n <= 20 && m <= 20)
		RunInstance(brute1);
	else
		RunInstance(brute2);
}

int main()
{
#ifndef LOCAL
	freopen("ticket.in", "r", stdin);
	freopen("ticket.out", "w", stdout);
#endif
	run();
	return 0;
}