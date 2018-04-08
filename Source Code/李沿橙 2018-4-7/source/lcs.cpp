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
typedef long long INT_PUT;
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
	do buffer[length++] = -(x % 10) + '0';
	while (x /= 10);
	do putchar(buffer[--length]);
	while (length);
}

const int maxn = int(1e5) + 5;
int n, m;
char str[maxn];

int len;
struct RLE
{
	char ch;
	int length;
} codes[maxn];
void Code()
{
	for (int i = 0; i < n; i++)
	{
		if (!len || codes[len].ch != str[i])
		{
			len++;
			codes[len].ch = str[i];
			codes[len].length = 1;
		}
		else
			codes[len].length++;
	}
}

#define RunInstance(x) delete new x
struct brute
{
	brute()
	{
		LL ans = 0;
		for (int i = 1; i <= len; i++)
		{
			for (int j = 1; j <= len; j++)
			{
				if (i == j)
				{
					ans += (codes[j].length - 1) * (m - 1);
					if (j != len) ans--;
				}
				else
				{
					ans += codes[j].length * (m - 1);
				}
			}
			ans += m - 1;
		}
		printOut(ans);
	}
};

void run()
{
	n = readIn();
	m = readIn();
	scanf("%s", str);
	Code();

	if (n <= 1000)
		RunInstance(brute);
}

int main()
{
#ifndef LOCAL
	freopen("lcs.in", "r", stdin);
	freopen("lcs.out", "w", stdout);
#endif
	run();
	return 0;
}