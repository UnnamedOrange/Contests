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

INT n, m;
std::vector<INT> origin;
class RMQ
{
	std::vector<std::vector<INT> > rmq;

public:
	void init()
	{
		origin.resize(n + 1);
		for (int i = 1; i <= n; i++)
		{
			origin[i] = readIn();
		}

		INT size = 0;
		while (1 << (size + 1) < n) size++;
		rmq.resize(size + 1);
		for (int i = 0; i < rmq.size(); i++)
		{
			rmq[i].resize(n + 1);
		}
		for (int i = 1; i <= n; i++)
		{
			rmq[0][i] = i;
		}

		for (int i = 1; i <= size; i++)
		{
			for (int j = 1; j + (1 << i) - 1 <= n; j++)
			{
				if (origin[rmq[i - 1][j]] > origin[rmq[i - 1][j + (1 << (i - 1))]])
				{
					rmq[i][j] = rmq[i - 1][j];
				}
				else
				{
					rmq[i][j] = rmq[i - 1][j + (1 << (i - 1))];
				}
			}
		}
	}

	INT query(INT l, INT r)
	{
		INT length = r - l + 1;
		INT size = 0;
		while (1 << (size + 1) < length) size++;
		if (origin[rmq[size][l]] > origin[rmq[size][r - (1 << size) + 1]])
		{
			return rmq[size][l];
		}
		else
		{
			return rmq[size][r - (1 << size) + 1];
		}
	}
} rmq;

INT ans;
void goLeft(INT L, INT R)
{
	if (L == R)
	{
		ans++;
		return;
	}
	INT mid = rmq.query(L, R);
	ans++;
	if (mid == L) return;
	goLeft(L, mid - 1);
}
void goRight(INT L, INT R)
{
	if (L == R)
	{
		ans++;
		return;
	}
	INT mid = rmq.query(L, R);
	ans++;
	if (mid == R) return;
	goRight(mid + 1, R);
}

void run()
{
	n = readIn();
	m = readIn();
	rmq.init();

	while (m--)
	{
		INT l = readIn();
		INT r = readIn();

		ans = 1;
		INT mid = rmq.query(l, r);
		if (mid > l) goLeft(l, mid - 1);
		if (mid < r) goRight(mid + 1, r);
		printf("%d\n", ans); //INT is int here
	}
}

int main()
{
#ifndef JUDGE
	freopen("trip.in", "r", stdin);
	freopen("trip.out", "w", stdout);
#endif
	run();
	return 0;
}
