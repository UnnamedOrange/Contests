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

const INT maxn = 1005;
INT n, m;
INT q1, q2;

void run()
{
	n = readIn();
	m = readIn();
	q1 = q2 = m - 1;
	for(int i = 1; i <= n; i++)
	{
		INT rank = readIn();
		q1 -= m - rank;
		q2 -= rank - 1;
	}
	if(q1 < 0) q1 = 0;
	if(q2 < 0) q2 = 0;
	cout << 1 + q1 << endl;
	cout << m - q2 << endl;
}

int main()
{
#ifndef JUDGE
	freopen("rank.in", "r", stdin);
	freopen("rank.out", "w", stdout);
#endif
	run();
	return 0;
}
