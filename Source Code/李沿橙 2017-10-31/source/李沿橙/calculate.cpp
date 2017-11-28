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
typedef long long INT;
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

const INT maxn = 100005;
INT n, m;
INT a[maxn], b[maxn];

const INT maxa = 500;
INT t[maxa + 5][maxa + 5];
INT sum[maxa + 5];

INT s(INT x)
{
	INT ret = 0;
	for (int i = 1; i <= maxa; i++)
	{
		ret += x / i * t[i][i - 1];
		ret -= t[i][i - 1] - t[i][x % i];
		ret -= sum[i];
	}
	return ret;
}
void work()
{
	for (int i = 1; i <= n; i++)
	{
		sum[a[i]] += b[i] / a[i];
		t[a[i]][b[i] % a[i]]++;
	}
	for (int i = 1; i <= maxa; i++)
		for (int j = 1; j < i; j++)
			t[i][j] += t[i][j - 1];

	while (m--)
	{
		INT ins = readIn();
		if (ins == 1)
		{
			INT pos = readIn();
			INT val = readIn();

			sum[a[pos]] -= b[pos] / a[pos];
			sum[val] += b[pos] / val;

			for (int i = b[pos] % a[pos]; i < a[pos]; i++) t[a[pos]][i]--;
			for (int i = b[pos] % val; i < val; i++) t[val][i]++;

			a[pos] = val;
		}
		else if (ins == 2)
		{
			INT pos = readIn();
			INT val = readIn();

			sum[a[pos]] += val / a[pos] - b[pos] / a[pos];

			INT bm = b[pos] % a[pos];
			INT vm = val % a[pos];

			if (bm <= vm)
				for (int i = bm; i < vm; i++)
					t[a[pos]][i]--;
			else
				for (int i = vm; i < bm; i++)
					t[a[pos]][i]++;

			b[pos] = val;
		}
		else if (ins == 3)
		{
			INT k = readIn();
			INT l = 0, r = INT(1e9);
			while (r - l > 0)
			{
				INT mid = l + ((r - l) >> 1);
				if (s(mid) < k) l = mid + 1;
				else r = mid;
			}
			printOut(l);
		}
	}
}

void run()
{
	INT T = readIn();
	while (T--)
	{
		n = readIn();
		m = readIn();
		for (int i = 1; i <= n; i++)
			a[i] = readIn();
		for (int i = 1; i <= n; i++)
			b[i] = readIn();

		memset(t, 0, sizeof(t));
		memset(sum, 0, sizeof(sum));
		work();
	}
}

int main()
{
#ifndef JUDGE
	freopen("calculate.in", "r", stdin);
	freopen("calculate.out", "w", stdout);
#endif
	run();
	return 0;
}
