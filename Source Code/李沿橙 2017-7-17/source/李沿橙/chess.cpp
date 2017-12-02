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
using std::cin;
using std::cout;
using std::endl;
typedef long long INT;
inline int readIn()
{
	bool minus = false;
	int a = 0;
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

const int maxn = 100005;
INT n, m;
bool row[maxn], colum[maxn];
INT rUsed, cUsed;

void run()
{
	n = readIn();
	m = readIn();

	for (int i = 1; i <= m; i++)
	{
		int x = readIn();
		int y = readIn();

		if (!row[x])
		{
			row[x] = true;
			rUsed++;
		}
		if (!colum[y])
		{
			colum[y] = true;
			cUsed++;
		}
		INT ans = n * n - ((rUsed + cUsed) * n - rUsed * cUsed);
		cout << ans << endl;
	}
}

int main()
{
	run();
	return 0;
}