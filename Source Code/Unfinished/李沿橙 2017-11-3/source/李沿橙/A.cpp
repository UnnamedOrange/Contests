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
typedef int INT;
using std::cin;
using std::cout;
using std::endl;
INT readIn()
{
	INT a = 0;
	bool minus = false;
	char ch = getchar();
	while (!(ch == '-' || (ch >= '0' && ch <= '9'))) ch = getchar();
	if (ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		a = a * 10 + (ch - '0');
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}
void printOut(INT x)
{
	char buffer[20];
	INT length = 0;
	bool minus = x < 0;
	if (minus) x = -x;
	do
	{
		buffer[length++] = x % 10 + '0';
		x /= 10;
	} while (x);
	if (minus) buffer[length++] = '-';
	do
	{
		putchar(buffer[--length]);
	} while (length);
	putchar('\n');
}

const INT INF = (~(INT(1) << (sizeof(INT) * 8 - 1)));
const INT maxn = INT(1e4) + 5;
INT n;
struct Flag
{
	INT x;
	INT y;
	void read()
	{
		x = readIn();
		y = readIn();
		if (x > y) std::swap(x, y);
	}
	bool operator< (const Flag& b) const
	{
		if (x != b.x) return x < b.x;
		return y < b.y;
	}
} flags[maxn];

#define RunInstance(x) delete new x
struct brute
{
	static const INT maxN = 25;

	brute()
	{
		INT ans = 0;
		INT U = 1 << n;
		for (int S = 0; S < U; S++)
		{
			INT x[maxN];
			for (int i = 0; i < n; i++)
			{
				if (S & (1 << i))
					x[i] = flags[i + 1].x;
				else
					x[i] = flags[i + 1].y;
			}
			std::sort(x, x + n);
			INT temp = INF;
			for (int i = 1; i < n; i++)
				temp = std::min(temp, x[i] - x[i - 1]);

			ans = std::max(ans, temp);
		}
		printOut(ans);
	}
};
struct work
{
	typedef std::map<INT, INT> map;
	typedef std::map<INT, INT>::iterator iterator;
	static bool isNeed(map& num, INT s, INT val)
	{
		iterator it = num.find(val);
		if (s && it->second > 1) return true;
		iterator pre = it, nxt = it;
		if (pre != num.begin())
		{
			pre--;
			if (val - pre->first < s) return true;
		}
		nxt++;
		if (nxt != num.end())
			if (nxt->first - val < s) return true;
		return false;
	}
	static bool check(INT s)
	{
		map num;
		num[flags[1].x]++;
		for (int i = 2; i <= n; i++)
		{
			INT x = flags[i].x;
			INT y = flags[i].y;
			num[x]++;
			if (isNeed(num, s, x))
			{
				if (!(--num[x])) num.erase(x);
				num[y]++;
				if (isNeed(num, s, y)) return false;
			}
		}
		return true;
	}
	work()
	{
		INT l = INF, r = 0;
		for (int i = 1; i < n; i++)
			l = std::min(l, flags[i + 1].x - flags[i].x);
		for (int i = 1; i <= n; i++)
			r = std::max(r, flags[i].y);
		r -= flags[1].x;
		r++;

		while (r - l > 1)
		{
			INT mid = l + ((r - l) >> 1);
			if (check(mid)) l = mid;
			else r = mid;
		}
		printOut(l);
	}
};

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
		flags[i].read();
	std::sort(flags + 1, flags + 1 + n);

	if (n <= 18)
		RunInstance(brute);
	else
		RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
#endif
	run();
	return 0;
}
