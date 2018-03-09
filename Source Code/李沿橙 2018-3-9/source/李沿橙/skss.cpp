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
		a = a * 10 - (ch - '0');
		ch = getchar();
	}
	if (positive) a = -a;
	return a;
}
void printOut(INT_PUT x)
{
	char buffer[40];
	int length = 0;
	if (x < 0)
		putchar('-');
	else
		x = -x;
	do
	{
		buffer[length++] = -(x % 10) + '0';
	} while (x /= 10);
	do
	{
		putchar(buffer[--length]);
	} while (length);
}

const int maxn = 200005;
int n;
int p1 = true;
struct Rect
{
	int type;
	int x, y, d;
	void read()
	{
		x = readIn();
		y = readIn();
		d = readIn();
	}
} rects[maxn];

#define RunInstance(x) delete new x
struct work
{
	static const int maxm = 3005;
	static const int maxM = 6020;
	unsigned int sum1[maxm][maxm];
	unsigned int sum2[maxM][maxM];
	static inline int code1(int x)
	{
		return x + 1501;
	}
	static inline int code2(int x)
	{
		return x + 3005;
	}
	static inline void change(int& x, int& y)
	{
		int t = x + y;
		x -= y;
		y = t;
	}

	work() : sum1(), sum2()
	{
		for (int i = 1; i <= n; i++)
		{
			Rect& r = rects[i];
			r.d >>= 1;
			if (r.type == 0)
			{
				sum1[code1(r.x - r.d)][code1(r.y - r.d)]++;
				sum1[code1(r.x - r.d)][code1(r.y + r.d)]--;
				sum1[code1(r.x + r.d)][code1(r.y - r.d)]--;
				sum1[code1(r.x + r.d)][code1(r.y + r.d)]++;
			}
			else
			{
				int x1 = r.x - r.d, y1 = r.y;
				change(x1, y1);
				int x2 = r.x, y2 = r.y + r.d;
				change(x2, y2);
				int x3 = r.x, y3 = r.y - r.d;
				change(x3, y3);
				int x4 = r.x + r.d, y4 = r.y;
				change(x4, y4);
				sum2[code2(x1)][code2(y1)]++;
				sum2[code2(x2)][code2(y2)]--;
				sum2[code2(x3)][code2(y3)]--;
				sum2[code2(x4)][code2(y4)]++;
			}
		}
		for (int i = 1; i < maxm; i++)
			sum1[0][i] += sum1[0][i - 1];
		for (int i = 1; i < maxm; i++)
		{
			sum1[i][0] += sum1[i - 1][0];
			for (int j = 1; j < maxm; j++)
				sum1[i][j] += sum1[i - 1][j] + sum1[i][j - 1] - sum1[i - 1][j - 1];
		}
		for (int i = 1; i < maxM; i++)
		{
			sum2[i][0] += sum2[i - 1][0];
			for (int j = 1; j < maxM; j++)
				sum2[i][j] += sum2[i - 1][j] + sum2[i][j - 1] - sum2[i - 1][j - 1];
		}

		int ans = 0;
		for (int i = 1; i < maxm; i++)
		{
			for (int j = 1; j < maxm; j++)
			{
				if (sum1[i][j]) ans += 4;
				else
				{
					int x = i - 1501;
					int y = j - 1501;
					change(x, y);

					if (sum2[code2(x)][code2(y)]) ans++;
					if (sum2[code2(x)][code2(y + 1)]) ans++;
					if (sum2[code2(x - 1)][code2(y + 1)]) ans++;
					if (sum2[code2(x - 1)][code2(y)]) ans++;
				}
			}
		}
		printf("%.2f", (double)ans / 4);
	}
};

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
	{
		char buffer[10];
		scanf("%s", buffer);
		if (buffer[0] == 'B')
			p1 = false;
		rects[i].type = (buffer[0] == 'A') ? 0 : 1;
		rects[i].read();
	}

	RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("skss.in", "r", stdin);
	freopen("skss.out", "w", stdout);
#endif
	run();
	return 0;
}