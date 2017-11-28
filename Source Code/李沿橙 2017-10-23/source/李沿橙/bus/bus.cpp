#pragma G++ optimize("O3")
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
	putchar(' ');
}

const INT maxn = INT(1e6) + 5;
INT n, maxc;
INT c[maxn];
INT v[maxn];

struct stack : public std::vector<INT>
{
	INT back2()
	{
		return std::vector<INT>::operator[](std::vector<INT>::size() - 2);
	}
};

#define RunInstance(x) delete new x
struct cheat1
{
	static const INT maxN = 5005;
	INT f[maxN];

	cheat1() : f()
	{
		f[0] = 0;
		for (int i = 1; i <= n; i++)
		{
			f[i] = -1;
			for (int j = 0; j < i; j++)
			{
				if ((i - j) % c[j] || f[j] == -1) continue;
				INT t = f[j] + (i - j) / c[j] * v[j];
				if (f[i] == -1 || f[i] > t) f[i] = t;
			}
			printOut(f[i]);
		}
		putchar('\n');
	}
};
struct cheat2
{
	cheat2()
	{
		INT cnt = v[0];
		INT sum = 0;
		for (int i = 1; i <= n; i++)
		{
			printOut(sum += cnt);
			cnt = std::min(cnt, v[i]);
		}
	}
};
struct work
{
	INT f[maxn];
	stack q[11][10];

	INT y(INT s)
	{
		return c[s] * f[s] - s * v[s];
	}
	INT x(INT s)
	{
		return v[s];
	}
	INT y(INT i, INT j)
	{
		return y(i) - y(j);
	}
	INT x(INT i, INT j)
	{
		return x(j) - x(i);
	}
	double slope(INT i, INT j)
	{
		INT x2 = x(i, j);
		if (!x2) return 1e100;
		return double(y(i, j)) / x2;
	}
	INT dp(INT i, INT j)
	{
		return f[j] + (i - j) / c[j] * v[j];
	}

	work() : f()
	{
		f[0] = 0;
		q[c[0]][0].push_back(0);

		for (int i = 1; i <= n; i++)
		{
			INT& ans = f[i];
			ans = -1;
			for (int j = 1; j <= maxc; j++)
			{
				stack& s = q[j][i % j];
				if (s.empty()) continue;

				while (s.size() > 1 &&
					dp(i, s.back()) >= dp(i, s.back2()))
					s.pop_back();

				INT k = s.back();
				INT t = dp(i, k);
				if (ans == -1 || ans > t)
					ans = t;
			}
			printOut(ans);

			if (i != n && f[i] != -1)
			{
				stack& s = q[c[i]][i % c[i]];
				while (s.size() && v[s.back()] >= v[i]) s.pop_back();

				while (s.size() > 1 && slope(i, s.back()) >= slope(s.back(), s.back2()))
					s.pop_back();
				s.push_back(i);
			}
		}
	}
};

void run()
{
	n = readIn();
	maxc = readIn();
	for (int i = 0; i < n; i++)
	{
		c[i] = readIn();
		v[i] = readIn();
	}

	//if (n <= 5000)
	//	RunInstance(cheat1);
	//else if (maxc == 1)
	//	RunInstance(cheat2);
	//else
	RunInstance(work);
}

int main()
{
#ifndef JUDGE
	freopen("bus.in", "r", stdin);
	freopen("bus.out", "w", stdout);
#endif
	run();
	return 0;
}
