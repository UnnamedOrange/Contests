#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cassert>
#include <cctype>
#include <climits>
#include <ctime>
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
#include <list>
#include <functional>
typedef long long LL;
typedef unsigned long long ULL;
using std::cin;
using std::cout;
using std::endl;
typedef LL INT_PUT;
INT_PUT readIn()
{
	INT_PUT a = 0;
	bool positive = true;
	char ch = getchar();
	while (!(std::isdigit(ch) || ch == '-')) ch = getchar();
	if (ch == '-')
	{
		positive = false;
		ch = getchar();
	}
	while (std::isdigit(ch))
	{
		(a *= 10) -= ch - '0';
		ch = getchar();
	}
	return positive ? -a : a;
}
void printOut(INT_PUT x)
{
	char buffer[20];
	int length = 0;
	if (x < 0) putchar('-');
	else x = -x;
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
	putchar('\n');
}

const int maxn = int(1e5) + 5;
int m;
struct Gua
{
	int num;
	int value;
	bool operator<(const Gua& b) const
	{
		return value < b.value;
	}
} gua[3];
int a[maxn];

#define RunInstance(x) delete new x
struct cheat
{
	bool check(LL s)
	{
		int r1 = gua[0].num;
		int r2 = gua[1].num;

		for (int i = 1; i <= m; i++)
		{
			if (r1 >= 2 && (LL)gua[0].value * 2 * a[i] >= s)
			{
				r1 -= 2;
			}
			else if (r1 >= 1 && r2 >= 1 && (LL)(gua[0].value + gua[1].value) * a[i] >= s)
			{
				r1--;
				r2--;
			}
			else if (r2 >= 2 && (LL)gua[1].value * 2 * a[i] >= s)
			{
				r2 -= 2;
			}
			else
				return false;
		}
		return true;
	}

	cheat()
	{
		gua[0] = std::min(gua[1], gua[2]);
		gua[1] = std::max(gua[1], gua[2]);

		LL l = (LL)gua[0].value * 2 * a[1];
		LL r = (LL)gua[1].value * 2 * a[m] + 1;
		while (r - l > 1)
		{
			LL mid = (l + r) >> 1;
			if (check(mid))
				l = mid;
			else
				r = mid;
		}
		printOut(l);
	}
};
struct brute
{
	int v1, v2, v3;
	bool deal(int j, LL s, int& r1, int& r2, int& r3)
	{
		if (r1 >= 2 && (LL)v1 * 2 * a[j] >= s)
		{
			r1 -= 2;
		}
		else if (r1 >= 1 && r2 >= 1 && (LL)(v1 + v2) * a[j] >= s)
		{
			r1--;
			r2--;
		}
		else if (r2 >= 2 && (LL)v2 * 2 * a[j] >= s)
		{
			r2 -= 2;
		}
		else if (r2 >= 1 && r3 >= 1 && (LL)(v2 + v3) * a[j] >= s)
		{
			r2--;
			r3--;
		}
		else if (r3 >= 2 && (LL)v3 * 2 * a[j] >= s)
		{
			r3 -= 2;
		}
		else
			return false;
		return true;
	}
	bool check(LL s)
	{
		int begin;
		{
			int l = 1, r = m + 1;
			while (r - l > 0)
			{
				int mid = (l + r) >> 1;
				if ((LL)(gua[0].value + gua[2].value) * a[mid] < s)
					l = mid + 1;
				else
					r = mid;
			}
			begin = l;
		}

		int to = std::min(m - begin + 1, std::min(gua[0].num, gua[2].num));
		for (int i = 0; i <= to; i++)
		{
			int r1 = gua[0].num - i;
			int r2 = gua[1].num;
			int r3 = gua[2].num - i;
			bool bOk = true;
			for (int j = 1; j < begin; j++)
			{
				if (!deal(j, s, r1, r2, r3))
				{
					bOk = false;
					break;
				}
			}
			if (!bOk) continue;
			for (int j = begin + i; j <= m; j++)
			{
				if (!deal(j, s, r1, r2, r3))
				{
					bOk = false;
					break;
				}
			}
			if (bOk)
			{
				return true;
			}
		}
		return false;
	}
	brute()
	{
		std::sort(gua, gua + 3);
		v1 = gua[0].value;
		v2 = gua[1].value;
		v3 = gua[2].value;
		LL l = (LL)v1 * 2 * a[1];
		LL r = (LL)v3 * 2 * a[m] + 1;
		while (r - l > 1)
		{
			LL mid = (l + r) >> 1;
			if (check(mid))
				l = mid;
			else
				r = mid;
		}
		printOut(l);
	}
};
struct work
{
	int v1, v2, v3;
	bool deal(int j, LL s, int& r1, int& r2, int& r3)
	{
		if (v1 + v3 <= v2 + v2)
		{
			if (r1 >= 2 && (LL)v1 * 2 * a[j] >= s)
			{
				r1 -= 2;
			}
			else if (r1 >= 1 && r2 >= 1 && (LL)(v1 + v2) * a[j] >= s)
			{
				r1--;
				r2--;
			}
			else if (r1 >= 1 && r3 >= 1 && (LL)(v1 + v3) * a[j] >= s)
			{
				r1--;
				r3--;
			}
			else if (r2 >= 2 && (LL)v2 * 2 * a[j] >= s)
			{
				r2 -= 2;
			}
			else if (r2 >= 1 && r3 >= 1 && (LL)(v2 + v3) * a[j] >= s)
			{
				r2--;
				r3--;
			}
			else if (r3 >= 2 && (LL)v3 * 2 * a[j] >= s)
			{
				r3 -= 2;
			}
			else
				return false;
		}
		else
		{
			if (r1 >= 2 && (LL)v1 * 2 * a[j] >= s)
			{
				r1 -= 2;
			}
			else if (r1 >= 1 && r2 >= 1 && (LL)(v1 + v2) * a[j] >= s)
			{
				r1--;
				r2--;
			}
			else if (r2 >= 2 && (LL)v2 * 2 * a[j] >= s)
			{
				r2 -= 2;
			}
			else if (r1 >= 1 && r3 >= 1 && (LL)(v1 + v3) * a[j] >= s)
			{
				r1--;
				r3--;
			}
			else if (r2 >= 1 && r3 >= 1 && (LL)(v2 + v3) * a[j] >= s)
			{
				r2--;
				r3--;
			}
			else if (r3 >= 2 && (LL)v3 * 2 * a[j] >= s)
			{
				r3 -= 2;
			}
			else
				return false;
		}
		return true;
	}
	bool check(LL s)
	{
		int r1 = gua[0].num;
		int r2 = gua[1].num;
		int r3 = gua[2].num;
		for (int i = 1; i <= m; i++)
			if (!deal(i, s, r1, r2, r3))
				return false;
		return true;
	}
	work()
	{
		std::sort(gua, gua + 3);
		v1 = gua[0].value;
		v2 = gua[1].value;
		v3 = gua[2].value;
		LL l = (LL)v1 * 2 * a[1];
		LL r = (LL)v3 * 2 * a[m] + 1;
		while (r - l > 1)
		{
			LL mid = (l + r) >> 1;
			if (check(mid))
				l = mid;
			else
				r = mid;
		}
		printOut(l);
	}
};

void run()
{
	for (int i = 0; i < 3; i++)
		m += gua[i].num = readIn();
	for (int i = 0; i < 3; i++)
		gua[i].value = readIn();

	m >>= 1;
	for (int i = 1; i <= m; i++)
		a[i] = readIn();
	std::sort(a + 1, a + 1 + m);

	if (!gua[0].num)
		RunInstance(cheat);
	else if (m <= 1000)
		RunInstance(brute);
	else
		RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("champion.in", "r", stdin);
	freopen("champion.out", "w", stdout);
#endif
	run();
	return 0;
}