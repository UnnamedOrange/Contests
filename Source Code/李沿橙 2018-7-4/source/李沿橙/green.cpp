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

const int maxn = 305;
int r, c;
int n;
struct Point
{
	int x, y;
	Point() {}
	Point(int x, int y) : x(x), y(y) {}
	void read()
	{
		x = readIn();
		y = readIn();
	}
} points[maxn];

#define RunInstance(x) delete new x
struct brute1
{
	struct Node
	{
		int status;
		int times;
		Node() {}
		Node(int status, int times) : status(status), times(times) {}
	};
	static inline int code(int x, int y)
	{
		return (x - 1) * c + y - 1;
	}

	brute1()
	{
		int initStatus = 0;
		for (int i = 1; i <= n; i++)
			initStatus |= 1 << code(points[i].x, points[i].y);
		std::queue<Node> q;
		q.push(Node(initStatus, 0));
		while (!q.empty())
		{
			Node from = q.front();
			q.pop();
			int status;

			status = from.status;
			for (int x = 1; x < r; x++)
				for (int y = 1; y <= c; y++)
					if (from.status & (1 << code(x, y)))
						status |= 1 << code(x + 1, y);
			if (status != from.status)
				q.push(Node(status, from.times + 1));
			if (status == (1 << (r * c)) - 1)
			{
				printOut(from.times + 1);
				return;
			}

			status = from.status;
			for (int x = 2; x <= r; x++)
				for (int y = 1; y <= c; y++)
					if (from.status & (1 << code(x, y)))
						status |= 1 << code(x - 1, y);
			if (status != from.status)
				q.push(Node(status, from.times + 1));
			if (status == (1 << (r * c)) - 1)
			{
				printOut(from.times + 1);
				return;
			}

			status = from.status;
			for (int x = 1; x <= r; x++)
				for (int y = 1; y < c; y++)
					if (from.status & (1 << code(x, y)))
						status |= 1 << code(x, y + 1);
			if (status != from.status)
				q.push(Node(status, from.times + 1));
			if (status == (1 << (r * c)) - 1)
			{
				printOut(from.times + 1);
				return;
			}

			status = from.status;
			for (int x = 1; x <= r; x++)
				for (int y = 2; y <= c; y++)
					if (from.status & (1 << code(x, y)))
						status |= 1 << code(x, y - 1);
			if (status != from.status)
				q.push(Node(status, from.times + 1));
			if (status == (1 << (r * c)) - 1)
			{
				printOut(from.times + 1);
				return;
			}
		}
	}
};

void run()
{
	r = readIn();
	c = readIn();
	n = readIn();
	for (int i = 1; i <= n; i++)
		points[i].read();

	if (r <= 4 && c <= 4)
		RunInstance(brute1);
}

int main()
{
#ifndef LOCAL
	freopen("green.in", "r", stdin);
	freopen("green.out", "w", stdout);
#endif
	run();
	return 0;
}