#pragma GCC optimize("O3")
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

const INT mod = 1000000007;
INT n, m;

inline INT power(INT x, INT y)
{
	INT ret = 1;
	INT temp = x;
	while (y)
	{
		if (y & 1)
		{
			ret *= temp;
			if (ret >= mod) ret %= mod;
		}
		y >>= 1;
		temp *= temp;
		if (temp >= mod) temp %= mod;
	}
	return ret;
}

void run()
{
	n = readIn();
	m = readIn();
	if (n < m) std::swap(n, m);

	//ans = n + C(0,n) + C(1, n + 1) + C(2, n + 2) + ... + C(m, n + m)
	//    = n + C(0,n + 1) + C(1, n + 1) + C(2, n + 2) + ... + C(m, n + m)   (C(0, n) = C(0, n + 1))
	//    = n + C(m, n + m + 1)

	INT up = 1;
	INT down = 1;
	INT to = n + m + 1;
	for (INT i = n + 2; i <= to; i++)
	{
		up *= i;
		if (up >= mod) up %= mod;
	}
	for (INT i = 2; i <= m; i++)
	{
		down *= i;
		if (down >= mod) down %= mod;
	}
	up *= power(down, mod - 2);
	if (up >= mod) up %= mod;
	up += n;
	if (up >= mod) up %= mod;
	cout << up << endl;
}

int main()
{
	run();
	return 0;
}
