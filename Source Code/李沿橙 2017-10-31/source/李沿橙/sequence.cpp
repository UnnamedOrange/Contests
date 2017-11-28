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
		a = a * 10 + (ch - '0');
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}
inline void printOut(INT x)
{
	char buffer[15];
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

const INT INF = (~(INT(1) << (sizeof(INT) * 8 - 1)));
const INT maxn = INT(1e6) + 5;
INT n, m;
INT a[maxn], b[maxn];

#define RunInstance(x) delete new x
struct work
{
	INT ans;
	INT f[maxn];
	void initFailure()
	{
		f[0] = f[1] = 0;
		for (int i = 1; i < m - 1; i++)
		{
			INT pre = f[i];
			while (pre && b[pre] != b[i]) pre = f[pre];
			f[i + 1] = (b[pre] == b[i]) ? pre + 1 : 0;
		}
	}
	void KMP()
	{
		INT matched = 0;
		for (int i = 0; i < n; i++)
		{
			while (matched && a[i] != b[matched])
				matched = f[matched];
			if (a[i] == b[matched])
				matched++;
			if (matched == m - 1)
				ans++;
		}
	}

	work() : ans(0), f()
	{
		for (int i = 1; i < n; i++)
			a[i - 1] = a[i] - a[i - 1];
		for (int i = 1; i < m; i++)
			b[i - 1] = b[i] - b[i - 1];

		initFailure();
		KMP();
		printOut(ans);
	}
};

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 0; i < n; i++)
		a[i] = readIn();
	for (int i = 0; i < m; i++)
		b[i] = readIn();

	RunInstance(work);
}

int main()
{
#ifndef JUDGE
	freopen("sequence.in", "r", stdin);
	freopen("sequence.out", "w", stdout);
#endif
	run();
	return 0;
}
