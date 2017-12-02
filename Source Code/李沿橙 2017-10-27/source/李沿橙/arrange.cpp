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
inline INT readIn()
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
		a = a * 10 + ch - '0';
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}
inline void printOut(INT x)
{
	if (!x)
	{
		putchar('0');
	}
	else
	{
		char buffer[12];
		INT length = 0;
		bool minus = x < 0;
		if (minus) x = -x;
		while (x)
		{
			buffer[length++] = x % 10 + '0';
			x /= 10;
		}
		if (minus) buffer[length++] = '-';
		do
			putchar(buffer[--length]);
		while (length);
	}
	putchar('\n');
}

const INT mod = INT(1e9) + 7;
const INT maxn = 4005;
INT n, S;
INT a[maxn];
INT b[maxn];

#define RunInstance(x) delete new x
struct cheat1
{
	static const INT maxn = 15;
	bool vis1[maxn];
	bool vis2[maxn];
	INT ans;

	void search(INT x, INT s)
	{
		if (x == n + 1)
		{
			if (s == S) ans++;
			return;
		}

		if (a[x] && b[x]) search(x + 1, s + (a[x] > b[x]));
		else if (!a[x])
		{
			for (int i = 1; i <= n; i++) if (!vis1[i])
			{
				vis1[i] = true;
				search(x + 1, s + (i > b[x]));
				vis1[i] = false;
			}
		}
		else if (!b[x])
		{
			for (int i = 1; i <= n; i++) if (!vis2[i])
			{
				vis2[i] = true;
				search(x + 1, s + (a[x] > i));
				vis2[i] = false;
			}
		}
	}

	cheat1() : vis1(), vis2(), ans()
	{
		for (int i = 1; i <= n; i++)
			vis1[a[i]] = vis2[b[i]] = true;

		search(1, 0);
		printOut(ans);

	}
};
struct work
{
};

void run()
{
	n = readIn();
	S = readIn();
	for (int i = 1; i <= n; i++) a[i] = readIn();
	for (int i = 1; i <= n; i++) b[i] = readIn();
	if (n <= 10)
		RunInstance(cheat1);
	else
		RunInstance(work);
}

int main()
{
#ifndef JUDGE
	freopen("arrange.in", "r", stdin);
	freopen("arrange.out", "w", stdout);
#endif
	run();
	return 0;
}
