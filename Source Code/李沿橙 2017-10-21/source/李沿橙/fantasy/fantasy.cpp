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
#include <functional>
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
		bool minus = x < 0;
		if (minus) x = -x;
		char buffer[18];
		INT length = 0;
		while (x)
		{
			buffer[length++] = x % 10 + '0';
			x /= 10;
		}
		if (minus) buffer[length++] = '-';
		do
		{
			putchar(buffer[--length]);
		} while (length);
	}
	putchar('\n');
}

const INT INF = (~(INT(1) << (sizeof(INT) * 8 - 1)));
const INT maxn = INT(1e5) + 5;
INT n, k, l, r;
INT origin[maxn];
inline void goSum()
{
	for (int i = 1; i <= n; i++) origin[i] += origin[i - 1];
}

#define RunInstance(x) delete new x
struct cheat1
{
	INT ans[INT(1e6) + 5];

	cheat1()
	{
		goSum();
		ans[0] = 0;
		for (int i = 1; i <= n; i++)
		{
			for (int j = l; j <= r && i + j - 1 <= n; j++)
			{
				ans[++ans[0]] = origin[i + j - 1] - origin[i - 1];
			}
		}
		std::partial_sort(ans + 1, ans + 1 + k, ans + 1 + ans[0], std::greater<INT>());

		INT out = 0;
		for (int i = 1; i <= k; i++) out += ans[i];
		printOut(out);
	}
};
struct cheat2
{
	INT ans[maxn];

	cheat2()
	{
		goSum();
		ans[0] = 0;
		for (int i = 0; i + l <= n; i++)
		{
			ans[++ans[0]] = origin[i + l] - origin[i];
		}
		std::partial_sort(ans + 1, ans + 1 + k, ans + 1 + ans[0], std::greater<INT>());

		INT out = 0;
		for (int i = 1; i <= k; i++) out += ans[i];
		printOut(out);
	}
};
struct cheat3
{
	INT q[maxn];
	INT head, tail;

	cheat3() : head(), tail()
	{
		goSum();
		INT ans = -INF;
		for (int i = 0; i <= n; i++)
		{
			while (head < tail && origin[q[tail - 1]] > origin[i]) tail--;
			q[tail++] = i;

			if (i + l > n) break;

			while (head < tail && q[head] < i + l - r) head++;
			ans = std::max(ans, origin[i + l] - origin[q[head]]);
		}
		printOut(ans);
	}
};

INT size;
INT rmq[17][maxn];

void goRMQ()
{
	while (1 << (size + 1) < n + 1) size++;
	for (int i = 0; i <= n; i++) rmq[0][i] = i;
	for (int i = 1; i <= size; i++)
	{
		for (int j = 0; j + (1 << i) - 1 <= n; j++)
		{
			if (origin[rmq[i - 1][j]] < origin[rmq[i - 1][j + (1 << (i - 1))]])
				rmq[i][j] = rmq[i - 1][j];
			else
				rmq[i][j] = rmq[i - 1][j + (1 << (i - 1))];
		}
	}
}
INT minIdx(INT l, INT r)
{
	INT length = r - l + 1;
	INT k = 0;
	while (1 << (k + 1) < length) k++;
	if (origin[rmq[k][l]] < origin[rmq[k][r - (1 << k) + 1]])
		return rmq[k][l];
	else
		return rmq[k][r - (1 << k) + 1];
}

struct LeftArea
{
	INT rVal;
	INT L;
	INT R;
	INT minPos;

	LeftArea(INT rPos) : rVal(origin[rPos])
	{
		L = std::max(INT(0), rPos - r);
		R = std::max(INT(0), rPos - l);
		minPos = minIdx(L, R);
	}
	LeftArea(INT rVal, INT L, INT R) : rVal(rVal), L(L), R(R)
	{
		minPos = minIdx(L, R);
	}

	bool operator< (const LeftArea& b) const
	{
		return rVal - origin[minPos] < b.rVal - origin[b.minPos];
	}
};

void work()
{
	goSum();
	goRMQ();

	std::priority_queue<LeftArea> pq;

	for (int i = l; i <= n; i++)
	{
		pq.push(LeftArea(i));
	}

	INT ans = 0;
	while (k--)
	{
		LeftArea t = pq.top();
		pq.pop();

		ans += t.rVal - origin[t.minPos];

		if (t.minPos - 1 >= t.L)
		{
			pq.push(LeftArea(t.rVal, t.L, t.minPos - 1));
		}
		if (t.minPos + 1 <= t.R)
		{
			pq.push(LeftArea(t.rVal, t.minPos + 1, t.R));
		}
	}
	printOut(ans);
}

void run()
{
	n = readIn();
	k = readIn();
	l = readIn();
	r = readIn();
	for (int i = 1; i <= n; i++)
		origin[i] = readIn();

	//	if (n <= 1000)
	//		RunInstance(cheat1);
	//	else if (l == r)
	//		RunInstance(cheat2);
	//	else if (k == 1)
	//		RunInstance(cheat3);
	//	else
	work();
}

int main()
{
#ifndef JUDGE
	freopen("fantasy.in", "r", stdin);
	freopen("fantasy.out", "w", stdout);
#endif
	run();
	return 0;
}
