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

const INT maxn = 200005;
INT n, m;
char buffer[maxn];

#define RunInstance(x) delete new x
struct cheat1
{
	std::set<std::string> s;

	cheat1()
	{
		scanf("%s", buffer);
		for (int i = 0; i + m - 1 < n; i++)
		{
			s.insert(std::string(buffer + i, buffer + i + m));
		}
		cout << s.size() << endl;
	}
};
struct work
{
	static INT power(INT x, INT y, INT mod)
	{
		INT ret = 1;
		while (y)
		{
			if (y & 1) ret = ret * x % mod;
			x = x * x % mod;
			y >>= 1;
		}
		return ret;
	}

	static const INT mod1 = INT(1e9) + 7;
	static const INT mod2 = INT(1e9) + 9;
	static const INT p1 = 97;
	static const INT p2 = 103;

	typedef std::pair<INT, INT> doubleType;
	doubleType dh[maxn];

	std::set<doubleType> s;

	work() : dh()
	{
		scanf("%s", buffer + 1);
		for (int i = 1; i <= n; i++)
		{
			dh[i].first = (dh[i - 1].first * p1 + buffer[i]) % mod1;
			dh[i].second = (dh[i - 1].second * p2 + buffer[i]) % mod2;
		}

		for (int i = m; i <= n; i++)
		{
			s.insert(doubleType(
				(dh[i].first - dh[i - m].first * power(p1, m, mod1) % mod1 + mod1) % mod1,
				(dh[i].second - dh[i - m].second * power(p2, m, mod2) % mod2 + mod2) % mod2
			));
		}

		cout << s.size() << endl;
	}
};

void run()
{
	n = readIn();
	m = readIn();

	RunInstance(work);
}

int main()
{
#ifndef JUDGE
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif
	run();
	return 0;
}
