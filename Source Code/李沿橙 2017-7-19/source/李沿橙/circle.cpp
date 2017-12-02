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
	bool minus = false;
	INT a = 0;
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

INT n, m, k, x;

INT power(INT down, INT up)
{
	if (!up) return 1;
	INT temp = power(down, up >> 1);
	temp *= temp;
	temp %= n;
	if (up & 1)
	{
		temp *= down;
		temp %= n;
	}
	return temp;
}

void run()
{
	n = readIn();
	m = readIn();
	k = readIn();
	x = readIn();

	INT ans = (x + m * power(10, k) % n) % n;
	cout << ans << endl;
}

int main()
{
	run();
	return 0;
}