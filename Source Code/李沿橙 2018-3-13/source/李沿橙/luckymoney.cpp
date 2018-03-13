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
}

const int maxn = 105;
int n, m;
int rect[maxn][maxn];

#define RunInstance(x) delete new x
struct brute
{
	brute()
	{
		int a[15];
		for (int i = 1; i <= n; i++)
			a[i] = i;
		do
		{
			int sum = 0;
			for (int i = 1; i <= n; i++)
			{
				if (rect[i][a[i]] == -1)
				{
					sum = -1;
					break;
				}
				else
					sum += rect[i][a[i]];
			}
			if (sum == -1 || sum % m) continue;
			puts("Yes");
			return;
		} while (std::next_permutation(a + 1, a + 1 + n));
		puts("No");
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
	m = readIn();
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			rect[i][j] = readIn();

	if (n <= 10)
		RunInstance(brute);
	else
		RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("luckymoney.in", "r", stdin);
	freopen("luckymoney.out", "w", stdout);
#endif
	run();
	return 0;
}
