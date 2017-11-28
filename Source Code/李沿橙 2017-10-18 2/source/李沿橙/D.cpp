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

const INT maxp = 5005;
const INT maxn = INT(1e6) + 5;
INT p, q;
INT n, A, B, C;
INT m, D, E, F;
INT a1, a2;
INT b1, b2;
void input()
{
	p = readIn();
	q = readIn();

	n = readIn();
	a1 = readIn();
	a2 = readIn();
	A = readIn();
	B = readIn();
	C = readIn();

	m = readIn();
	b1 = readIn();
	b2 = readIn();
	D = readIn();
	E = readIn();
	F = readIn();
}
#define f(u, mod) (((u) % (mod) + (mod)) % (mod))
INT power(INT x, INT y)
{
	INT ret = 1;
	while (y)
	{
		if (y & 1) ret = ret * x % p;
		x = x * x % p;
		y >>= 1;
	}
	return ret;
}

#define RunInstance(x) delete new x
struct cheat
{
	static const INT maxN = 1005;
	INT a[maxN];
	INT b[maxN];

	void init()
	{
		a[1] = f(a1, p);
		a[2] = f(a2, p);
		for (int i = 3; i <= n; i++)
		{
			a[i] = f(A * a[i - 1] - B * a[i - 2] - C, p);
		}

		b[1] = f(b1, p - 1);
		b[2] = f(b2, p - 1);
		for (int i = 3; i <= m; i++)
		{
			b[i] = f(D * b[i - 1] + E * b[i - 2] + F, p - 1);
		}
	}

	cheat()
	{
		init();
		INT ans = 0;
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= m; j++)
			{
				if (power(a[i], b[j]) <= q)
				{
					ans++;
				}
			}
		}
		cout << ans << endl;
	}
};
struct work
{
	INT a[maxn];
	INT b[maxn];

	void init()
	{
		a[1] = f(a1, p);
		a[2] = f(a2, p);
		for (int i = 3; i <= n; i++)
		{
			a[i] = f(A * a[i - 1] - B * a[i - 2] - C, p);
		}

		b[1] = f(b1, p - 1);
		b[2] = f(b2, p - 1);
		for (int i = 3; i <= m; i++)
		{
			b[i] = f(D * b[i - 1] + E * b[i - 2] + F, p - 1);
		}
	}

	INT aTimes[maxp];
	INT bTimes[maxp];

	work() : aTimes(), bTimes()
	{
		init();
		for (int i = 1; i <= n; i++) aTimes[a[i]]++;
		for (int i = 1; i <= m; i++) bTimes[b[i]]++;

		INT ans = 0;
		for (int i = 0; i < p; i++) ans += aTimes[0] * bTimes[i];

		for (int i = 1; i < p; i++)
		{
			INT res = 1;
			if (res <= q) ans += aTimes[i] * bTimes[0];
			for (int j = 1; j < p - 1; j++)
			{
				res = res * i % p;
				if (res <= q) ans += aTimes[i] * bTimes[j];
			}
		}
		cout << ans << endl;
	}
};

void run()
{
	input();

	if (n <= 1000 && m <= 1000)
		RunInstance(cheat);
	else
		RunInstance(work);
}

int main()
{
#ifndef JUDGE
	freopen("D.in", "r", stdin);
	freopen("D.out", "w", stdout);
#endif
	run();
	return 0;
}
