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
typedef int INT_PUT;
INT_PUT readIn()
{
	INT_PUT a = 0;
	bool positive = true;
	char ch = getchar();
	while (!(ch == '-' || std::isdigit(ch))) ch = getchar();
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
	if (positive) a = -a;
	return a;
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

const int maxn = int(2e5) + 5;
int w, h, n;
struct Point
{
	int x, y;
	void read() { x = readIn(); y = readIn(); }
} points[maxn];
typedef std::set<int>::iterator IT;
IT pre(IT x)
{
	IT it = x;
	it--;
	return it;
}
IT next(IT x)
{
	IT it = x;
	it++;
	return it;
}

#define RunInstance(x) delete new x
struct brute1
{
	brute1()
	{
		int ans = 0;
		int U = 1 << (n << 1);
		for (int S = 0; S < U; S++)
		{
			int left = 0;
			int bottom = 0;
			int right = w;
			int top = h;
			int mask = 3;
			for (int i = 0; i < n; i++, mask <<= 2)
			{
				int sel = (S & mask) >> (i << 1);
				if (sel == 0)
					left = std::max(left, points[i].x);
				else if (sel == 1)
					bottom = std::max(bottom, points[i].y);
				else if (sel == 2)
					right = std::min(right, points[i].x);
				else if (sel == 3)
					top = std::min(top, points[i].y);
			}
			if (left > right || bottom > top) continue;
			ans = std::max(ans, (top - bottom + right - left) << 1);
		}
		printOut(ans);
	}
};
struct brute2
{
	static bool comp(const Point& a, const Point& b)
	{
		return a.y < b.y;
	}
	static const int maxN = 1505;
	int bound;
	int height[maxN];
	brute2()
	{
		std::sort(points, points + n, comp);
		bound = 0;
		height[bound++] = 0;
		for (int i = 0; i < n; i++)
			height[bound++] = points[i].y;
		height[bound++] = h;
		bound = std::unique(height, height + bound) - height;

		int ans = 0;
		for (int i = 0; i < bound; i++)
		{
			int ptr = 0;
			while (points[ptr].y <= height[i]) ptr++;
			std::multiset<int> colum;
			std::multiset<int> delta;
			colum.insert(0);
			colum.insert(w);
			delta.insert(w);
			for (int j = i + 1; j < bound; j++)
			{
				while (ptr < n && points[ptr].y < height[j])
				{
					int x = points[ptr].x;
					colum.insert(x);
					std::set<int>::iterator it = colum.find(x);
					delta.erase(delta.find(*next(it) - *pre(it)));
					delta.insert(*next(it) - x);
					delta.insert(x - *pre(it));
					ptr++;
				}
				ans = std::max(ans, (height[j] - height[i] + *pre(delta.end())) << 1);
			}
		}
		printOut(ans);
	}
};
struct work
{
	work()
	{

	}
};

void run()
{
	w = readIn();
	h = readIn();
	n = readIn();
	for (int i = 0; i < n; i++)
		points[i].read();

	if (n <= 10)
		RunInstance(brute1);
	else if (n <= 1500)
		RunInstance(brute2);
	else
		RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("paint.in", "r", stdin);
	freopen("paint.out", "w", stdout);
#endif
	run();
	return 0;
}