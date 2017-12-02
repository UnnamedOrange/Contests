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

const INT maxn = 500005;
INT n, m;
INT money[maxn];
INT ans;

void violent(INT people = 1, INT index = 1, INT count_ = 0)
{
	if (people == n + 1)
	{
		ans = std::max(ans, count_);
		people = 1;
	}
	for (int i = index; i <= m; i++)
	{
		if (money[people] < i)
		{
			return;
		}
		money[people] -= i;
		violent(people + 1, i + 1, count_ + i);
		money[people] += i;
	}
}

void run()
{
	INT a = readIn();
	while (a--)
	{
		n = readIn();
		m = readIn();
		for (int i = 1; i <= n; i++)
		{
			money[i] = readIn();
		}

		if (m <= 20)
		{
			ans = 0;
			violent();
			cout << ans << endl;
		}
	}
}

int main()
{
#ifndef JUDGE
	freopen("compete.in", "r", stdin);
	freopen("compete.out", "w", stdout);
#endif
	run();
	return 0;
}
