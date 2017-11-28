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
typedef int INT;
using std::cin;
using std::cout;
using std::endl;
INT readIn()
{
	INT a = 0;
	bool minus = false;
	char ch = getchar();
	while (!(ch == '-' || (ch >= '0' && ch <= '9'))) ch = getchar();
	if (ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		a = a * 10 + (ch - '0');
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}
void printOut(INT x)
{
	char buffer[20];
	INT length = 0;
	bool minus = x < 0;
	if (minus) x = -x;
	do
	{
		buffer[length++] = x % 10 + '0';
		x /= 10;
	} while (x);
	if (minus) buffer[length++] = '-';
	do
	{
		putchar(buffer[--length]);
	} while (length);
	putchar('\n');
}

const INT maxn = 100005;
INT n, m;
INT a[maxn];
INT h[maxn];
INT idx[maxn];
INT ans[maxn];

bool comp(const INT& x, const INT& y)
{
	return a[x] < a[y];
}

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= n; i++)
		a[i] = readIn();
	for (int i = 1; i <= m; i++)
		h[i] = readIn();

	for (int i = 1; i <= n; i++)
		idx[i] = i;
	std::sort(idx + 1, idx + 1 + n, comp);
	std::sort(h + 1, h + 1 + m);

	INT cnt = 1;
	for (int i = 1; i <= n; i++)
	{
		while (cnt <= m && a[idx[i]] >= h[cnt])
		{
			ans[idx[i]]++;
			cnt++;
		}
	}
	for (int i = 1; i <= n; i++)
		printOut(ans[i]);
}

int main()
{
#ifndef LOCAL
	freopen("balloon.in", "r", stdin);
	freopen("balloon.out", "w", stdout);
#endif
	run();
	return 0;
}
