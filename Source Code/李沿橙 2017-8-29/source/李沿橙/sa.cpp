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

const INT maxn = INT(1e5) + 5;
INT n;
INT SA[maxn];
INT rank[maxn];

void run()
{
	while(n = readIn())
	{
		for(int i = 1; i <= n; i++)
		{
			SA[i] = readIn();
		}
		for(int i = 1; i <= n; i++)
		{
			rank[SA[i]] = i;
		}
		rank[n + 1] = 0;

		INT ans = 1;
		for(int i = 1; i < n; i++)
		{
			if(rank[SA[i] + 1] >= rank[SA[i + 1] + 1]) ans++;
		}
		cout << ans << endl;
	}
}

int main()
{
#ifndef JUDGE
	freopen("sa.in", "r", stdin);
	freopen("sa.out", "w", stdout);
#endif
	run();
	return 0;
}
