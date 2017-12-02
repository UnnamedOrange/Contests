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
INT seq[maxn];

void read()
{
	char ch = getchar();
	while (!(ch == '0' || ch == '1')) ch = getchar();
	while (ch == '0' || ch == '1')
	{
		seq[++n] = ch - '0';
		ch = getchar();
	}
}

INT sum0[maxn];
INT sum1[maxn];

void run()
{
	read();
	for(int i = 1; i <= n; i++)
	{
		sum1[i] = sum1[i - 1] + (seq[i] == 1);
	}
	for(int i = n; i >= 1; i--)
	{
		sum0[i] = sum0[i + 1] + (seq[i] == 0);
	}

	INT ans = n;
	INT to = n + 1;
	for(int i = 1; i <= to; i++)
	{
		ans = std::min(ans, sum1[i - 1] + sum0[i]);
	}
	cout << ans << endl;
}

int main()
{
#ifndef JUDGE
	freopen("reverse.in", "r", stdin);
	freopen("reverse.out", "w", stdout);
#endif
	run();
	return 0;
}
