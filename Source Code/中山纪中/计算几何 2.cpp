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

const INT maxn = 1e5 + 5;
INT n, m;
INT X[maxn];
INT Y[maxn];
INT queryX;
INT queryY;

bool check(INT index)
{
	if (!index) return true;
	else if (index > n) return false;
	if (queryX >= X[index]) return true;
	if (queryY >= Y[index]) return true;

	return (long long)X[index] * queryY >= (long long)Y[index] * (X[index] - queryX);
}

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
	{
		X[i] = readIn();
	}
	for (int i = 1; i <= n; i++)
	{
		Y[i] = readIn();
	}
	std::sort(X + 1, X + 1 + n);
	std::sort(Y + 1, Y + 1 + n);

	m = readIn();
	for (int i = 1; i <= m; i++)
	{
		queryX = readIn();
		queryY = readIn();
		INT l = 0, r = n;
		while (r - l > 1)
		{
			INT mid = (l + r) >> 1;
			if (check(mid))
			{
				l = mid;
			}
			else
			{
				r = mid - 1;
			}
		}
		if (check(l + 1)) l++;
		printf("%d\n", l); //INT is int here
	}
}

int main()
{
	run();
	return 0;
}
