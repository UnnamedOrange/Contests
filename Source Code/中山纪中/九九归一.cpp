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

INT n, q;
INT phiN;
INT phi(INT x)
{
	INT ret = x;
	INT to = sqrt(x);
	for (int i = 2; i <= to; i++)
	{
		if (x % i) continue;
		ret /= i;
		ret *= i - 1;
		while (!(x % i)) x /= i;
	}
	if (x > 1)
	{
		ret /= x;
		ret *= x - 1;
	}
	return ret;
}
INT power(INT x, INT y)
{
	INT ret = 1;
	while (y)
	{
		if (y & 1) ret = ret * x % n;
		x = x * x % n;
		y >>= 1;
	}
	return ret;
}
std::vector<INT> fac;
void dividePhiN()
{
	fac.push_back(1);
	INT to = sqrt(phiN);
	for (int i = 2; i <= to; i++)
	{
		if (phiN % i) continue;
		fac.push_back(i);
		fac.push_back(phiN / i);
	}
}
bool check(INT x)
{
	if (power(x, phiN) != 1) return false;
	for (int i = 0; i < fac.size(); i++)
	{
		if (power(x, fac[i]) == 1) return false;
	}
	return true;
}
void run()
{
	n = readIn();
	phiN = phi(n);
	dividePhiN();
	q = readIn();
	while (q--)
	{
		INT x = readIn();
		putchar('0' + bool(check(x)));
	}
}

int main()
{
	run();
	return 0;
}
