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

const INT maxn = 20005;
const INT maxm = 105;
INT n, m;
INT l[maxn], r[maxn];

#define RunInstance(x) delete new x
struct work
{
	work()
	{
		m = std::min(n, m);
	}
};
struct cheat
{
	INT f[maxn][maxm];

	cheat() : f()
	{
		//if n < m, this will work
		m = std::min(n, m);
		f[1][1] = r[1] - l[1] + 1;
		INT ans = f[1][m];
		for(int i = 2; i <= n; i++)
		{
			f[i][1] = (r[i] - l[i] + 1) * i;
			for(int j = 2; j <= std::min(i, (int)m); j++)
			{
				for(int k = j - 1; k < i; k++)
				{
					f[i][j] = std::max(f[i][j], f[k][j - 1] + (r[i] - l[i] + 1) * (i - k));
				}
			}
			ans = std::max(ans, f[i][m]);
		}
		cout << ans << endl;
	}
};

void run()
{
	n = readIn();
	m = readIn();
	INT all = 0;
	for(int i = 1; i <= n; i++)
	{
		l[i] = readIn();
		r[i] = readIn();
		all += r[i] - l[i] + 1;
	}
	if(all < m)
	{
		//illegal, but problem discribtion doesn't say what to do
		cout << 0 << endl;
		return;
	}

	if(n <= 1000) RunInstance(cheat);
	else RunInstance(work);
}

int main()
{
#ifndef JUDGE
	freopen("pyramid.in", "r", stdin);
	freopen("pyramid.out", "w", stdout);
#endif
	run();
	return 0;
}
