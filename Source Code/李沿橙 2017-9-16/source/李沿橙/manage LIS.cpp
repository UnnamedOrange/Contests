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

const INT INF = ~(INT(1) << (sizeof(INT) * 8 - 1));
const INT maxn = 100005;
INT n;
INT seq[maxn];

void run()
{
	n = readIn();
	for(int i = 1; i <= n; i++)
	{
		INT num = readIn();
		if(!seq[0] || seq[seq[0]] < num)
		{
			seq[++seq[0]] = num;
		}
		else
		{
			*std::lower_bound(seq + 1, seq + 1 + seq[0], num) = num;
		}
	}
	cout << seq[0] << endl;
}

int main()
{
#ifndef JUDGE
	freopen("manage.in", "r", stdin);
	freopen("manage.out", "w", stdout);
#endif
	run();
	return 0;
}
