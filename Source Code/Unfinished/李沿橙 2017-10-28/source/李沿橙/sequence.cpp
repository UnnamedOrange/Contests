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
		{
			putchar(buffer[--length]);
		} while (length);
	}
	putchar('\n');
}

const INT maxn = 1000005;
INT n, m;
INT a[maxn];

#define RunInstance(x) delete new x
struct cheat
{
	static const INT maxN = 1005;
	std::priority_queue<INT> pq;
	INT t[maxN];

	cheat()
	{
		for (int i = 1; i <= n; i++) pq.push(a[i]);
		INT ans = 0;
		while (m--)
		{
			INT c = readIn();
			t[0] = 0;
			bool bOk = true;
			for (int i = 1; i <= c; i++)
			{
				if (pq.empty())
				{
					bOk = false;
					break;
				}

				t[++t[0]] = pq.top() - 1;
				pq.pop();
			}
			if (!bOk) break;
			for (int i = 1; i <= t[0]; i++)
			{
				if (t[i] <= 0) break;
				pq.push(t[i]);
			}
			ans++;
		}
		printOut(ans);
	}
};
struct work
{
	INT c[maxn];
	INT temp[maxn];

	bool check(INT x)
	{
		memset(temp, 0, sizeof(INT) * (n + 2));
		INT sum = 0;
		for (int i = 1; i <= x; i++)
		{
			temp[c[i]]++;
			sum += c[i];
			if (temp[c[i]] > n) return false;
		}
		for (int i = n; i >= 1; i--) temp[i] += temp[i + 1];

		for (int i = 1; i <= n; i++)
		{
			sum -= std::min(a[i], temp[i]);
			if (a[i] < temp[i]) temp[i + 1] += temp[i] - a[i];
		}
		return !sum;
	}

	work()
	{
		for (int i = 1; i <= m; i++)
			c[i] = readIn();
		std::sort(a + 1, a + 1 + n, std::greater<INT>());
		for (int i = 1; i <= n && a[i] > m; i++) a[i] = m;

		INT l = 0;
		INT r = m + 1;
		while (r - l > 1)
		{
			INT mid = l + ((r - l) >> 1);
			if (check(mid)) l = mid;
			else r = mid;
		}
		printOut(l);
	}
};

void run()
{
	n = readIn();
	m = readIn();
	a[0] = n;
	for (int i = 1; i <= n; i++) a[i] = readIn();

	if (n <= 1000 && m <= 1000)
		RunInstance(cheat);
	else
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
