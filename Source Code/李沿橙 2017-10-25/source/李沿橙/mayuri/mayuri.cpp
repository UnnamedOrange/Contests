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

INT n, m;

#define RunInstance(x) delete new x
struct cheat1
{
	static const INT maxn = INT(1e6) + 5;
	INT f[maxn];

	cheat1()
	{
		f[1] = 0;
		for (int i = 2; i <= n; i++)
		{
			f[i] = (f[i - 1] + m) % i;
		}

		cout << f[n] + 1 << endl;
	}
};
struct cheat2
{
	cheat2()
	{
		INT k = 1;
		while (1ll << (k + 1) <= n) k++;
		cout << (n - (1 << k)) * 2 + 1 << endl;
	}
};
struct work
{
	work()
	{
		INT f = 0;
		for (int i = 2; i <= n; )
		{
			f = (f + m) % i;
			i++;
			while (f + m < i && i <= n)
			{
				INT l = (i - f) / m;
				if (i + l > n + 1) l = n - i + 1;
				i += l;
				f += m * l;
			}
		}
		cout << f + 1 << endl;
	}
};

void run()
{
	INT T = readIn();
	while (T--)
	{
		n = readIn();
		m = readIn();

		//if (n <= INT(1e6))
		//	RunInstance(cheat1);
		//else if (m == 2)
		//	RunInstance(cheat2);
		//else
		RunInstance(work);
	}
}

int main()
{
#ifndef JUDGE
	freopen("mayuri.in", "r", stdin);
	freopen("mayuri.out", "w", stdout);
#endif
	run();
	return 0;
}
