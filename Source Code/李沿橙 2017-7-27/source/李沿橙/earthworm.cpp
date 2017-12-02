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
typedef long long INT;
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
		return;
	}
	char buffer[23] = "";
	bool minus = x < 0;
	if (minus) x = -x;
	INT len = 0;
	while (x)
	{
		buffer[len++] = x % 10 + '0';
		x /= 10;
	}
	if (minus)
	{
		buffer[len++] = '-';
	}
	while (true)
	{
		putchar(buffer[--len]);
		if (!len) break;
	}
}

const INT maxn = 1e5 + 5;
const INT size = 8 * 1e6;
INT n, m, q, u, v, t;
INT* Q[3];
INT front[3], back[3];

void work_q()
{
	INT delta = 0;
	Q[0] = (INT*)calloc(n + 5, sizeof(INT));
	Q[1] = (INT*)calloc(n + m + 5, sizeof(INT));
	Q[2] = (INT*)calloc(n + m + 5, sizeof(INT));
	for (int i = 1; i <= n; i++)
	{
		Q[0][back[0]++] = readIn();
	}
	std::sort(Q[0] + front[0], Q[0] + back[0], std::greater<INT>());

	bool printed = false;
	for (int i = 1; i <= m; i++)
	{
		INT maxVal = -0x7fffffffffffffffll;
		INT maxIndex = 0;
		for (int j = 0; j < 3; j++)
		{
			if (!(front[j] == back[j]) && Q[j][front[j]] > maxVal)
			{
				maxVal = Q[j][front[j]];
				maxIndex = j;
			}
		}

		INT cut = Q[maxIndex][front[maxIndex]] + delta;
		if (!(i % t))
		{
			if (printed) putchar(' ');
			printOut(cut);
			printed = true;
		}

		front[maxIndex]++;
		INT len1 = cut * u / v;
		INT len2 = cut - len1;
		delta += q;
		len1 -= delta;
		len2 -= delta;

		Q[1][back[1]++] = len1;
		Q[2][back[2]++] = len2;
	}

	putchar('\n');
	printed = false;

	INT count_ = 0;
	while (!(front[0] == back[0]) || !(front[1] == back[1]) || !(front[2] == back[2]))
	{
		count_++;
		INT maxVal = 0x8000000000000000ll;
		INT maxIndex = 0;
		for (int i = 0; i < 3; i++)
		{
			if (!(front[i] == back[i]) && Q[i][front[i]] > maxVal)
			{
				maxVal = Q[i][front[i]];
				maxIndex = i;
			}
		}

		if (!(count_ % t))
		{
			if (printed) putchar(' ');
			printOut(Q[maxIndex][front[maxIndex]] + delta);
			printed = true;
		}
		front[maxIndex]++;
	}
	for (int i = 0; i < 3; i++) free(Q[i]);
}

void run()
{
	n = readIn();
	m = readIn();
	q = readIn();
	u = readIn();
	v = readIn();
	t = readIn();

	work_q();
}

int main()
{
	run();
	return 0;
}
