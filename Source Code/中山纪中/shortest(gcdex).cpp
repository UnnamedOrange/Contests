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

void gcdex(INT a, INT b, INT& gcd, INT& x, INT& y)
{
	if (!b)
	{
		gcd = a;
		x = 1;
		y = 0;
		return;
	}
	gcdex(b, a % b, gcd, y, x);
	y -= x * (a / b);
}
inline INT Inv(INT a)
{
	INT gcd, x, y;
	gcdex(a, mod, gcd, x, y);
	return x < 0 ? x + mod : x;
}
inline void Add(INT& x, INT y)
{
	x += y;
	if (x >= mod) x -= mod;
}
inline void Mul(INT& x, INT y)
{
	x *= y;
	if (x >= mod)
		x %= mod;
}
inline void Div(INT& x, INT y)
{
	x *= Inv(y);
	if (x >= mod)
		x %= mod;
}

void run()
{
	n = readIn();
	m = readIn();
	if (n < m) std::swap(n, m);

	INT ans = (n + 1) % mod;
	INT base = 1;
	for (int i = 1; i <= m; i++)
	{
		INT temp = base;
		Mul(temp, n + 1);
		Div(temp, i); //Notice that the name "div" will be ambiguous. Use upper-case to solve this problem.
		Add(ans, temp);
		Add(base, temp);
	}
	cout << ans << endl;
}

int main()
{
	run();
	return 0;
}
