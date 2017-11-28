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
using std::cin;
using std::cout;
using std::endl;
typedef int INT;
inline INT readIn()
{
	INT a = 0;
	bool minus = false;
	char ch = getchar();
	while (!(ch == '-' || ch >= '0' && ch <= '9')) ch = getchar();
	if (ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		a *= 10;
		a += ch;
		a -= '0';
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
		while (x)
		{
			buffer[length++] = x % 10 + '0';
			x /= 10;
		}
		do
		{
			putchar(buffer[--length]);
		} while (length);
	}
}

const INT INF = (~(INT(1) << (sizeof(INT) * 8 - 1)));
const INT maxn = 5005;
INT n, m;
INT a[maxn];
INT b[maxn];

#define RunInstance(x) delete new x
struct work
{
	INT f[maxn];
	INT pre[maxn][maxn]; //previous j

	work() : f(), pre()
	{
		for (int i = 1; i <= n; i++)
		{
			INT maxPos = 0;
			for (int j = 1; j <= m; j++)
			{
				if (a[i] > b[j] && f[maxPos] < f[j])
				{
					maxPos = j;
				}
				else if (a[i] == b[j])
				{
					f[j] = f[maxPos] + 1;
					pre[i][j] = maxPos;
				}
			}
		}

		INT ansPos = 0;
		for (int i = 1; i <= m; i++)
		{
			if (f[ansPos] < f[i]) ansPos = i;
		}
		printOut(f[ansPos]);
		putchar('\n');

		std::stack<INT> s;
		INT i = n;
		while (ansPos)
		{
			s.push(b[ansPos]);
			while (i && !pre[i][ansPos]) i--;
			ansPos = pre[i][ansPos];
			i--;
		}

		while (!s.empty())
		{
			printOut(s.top());
			putchar(' ');
			s.pop();
		}
	}
};

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++) a[i] = readIn();
	m = readIn();
	for (int i = 1; i <= m; i++) b[i] = readIn();

	RunInstance(work);
}

int main()
{
#ifndef JUDGE
	freopen("okarin.in", "r", stdin);
	freopen("okarin.out", "w", stdout);
#endif
	run();
	return 0;
}
