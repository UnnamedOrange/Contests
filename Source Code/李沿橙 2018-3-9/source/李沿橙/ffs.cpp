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

const int maxn = int(1e5) + 5;
int n, q;
int a[maxn];
int pos[maxn];
int x, y;

#define RunInstance(x) delete new x
struct brute
{
	brute()
	{
		while (q--)
		{
			x = readIn();
			y = readIn();

			int minPos = x;
			int maxPos = y;
			int minVal = a[x];
			int maxVal = a[x];
			for (int i = x + 1; i <= y; i++)
			{
				minVal = std::min(minVal, a[i]);
				maxVal = std::max(maxVal, a[i]);
			}

			int newMinPos = minPos;
			int newMaxPos = maxPos;
			for (int i = minVal; i <= maxVal; i++)
			{
				newMinPos = std::min(newMinPos, pos[i]);
				newMaxPos = std::max(newMaxPos, pos[i]);
			}

			while (maxVal - minVal != maxPos - minPos)
			{
				int newMinVal = minVal;
				int newMaxVal = maxVal;
				for (int i = newMinPos; i < minPos; i++)
				{
					newMinVal = std::min(newMinVal, a[i]);
					newMaxVal = std::max(newMaxVal, a[i]);
				}
				for (int i = maxPos + 1; i <= newMaxPos; i++)
				{
					newMinVal = std::min(newMinVal, a[i]);
					newMaxVal = std::max(newMaxVal, a[i]);
				}
				minPos = newMinPos;
				maxPos = newMaxPos;

				for (int i = newMinVal; i < minVal; i++)
				{
					newMinPos = std::min(newMinPos, pos[i]);
					newMaxPos = std::max(newMaxPos, pos[i]);
				}
				for (int i = maxVal + 1; i <= newMaxVal; i++)
				{
					newMinPos = std::min(newMinPos, pos[i]);
					newMaxPos = std::max(newMaxPos, pos[i]);
				}
				minVal = newMinVal;
				maxVal = newMaxVal;
			}
			printOut(minPos);
			putchar(' ');
			printOut(maxPos);
			putchar('\n');
		}
	}
};
struct RMQ
{
	struct LOG
	{
		int l[maxn];
		LOG()
		{
			l[0] = 0;
			for (int i = 1; i < maxn; i++)
			{
				int k = 0;
				while ((1 << (k + 1)) < i) k++;
				l[i] = k;
			}
		}
		inline const int& operator[](int x) const {
			return l[x];
		}
	};
	static LOG Log;

	int minVal[18][maxn];
	int maxVal[18][maxn];

	RMQ() {}
	RMQ(int a[maxn])
	{
		std::memcpy(minVal[0], a, sizeof(minVal[0]));
		std::memcpy(maxVal[0], a, sizeof(maxVal[0]));
		int k = Log[n];
		for (int i = 1; i <= k; i++)
		{
			for (int j = 1; j + (1 << i) - 1 <= n; j++)
			{
				minVal[i][j] = std::min(minVal[i - 1][j], minVal[i - 1][j + (1 << (i - 1))]);
				maxVal[i][j] = std::max(maxVal[i - 1][j], maxVal[i - 1][j + (1 << (i - 1))]);
			}
		}
	}
	int queryMin(int l, int r)
	{
		int length = r - l + 1;
		int k = Log[length];
		return std::min(minVal[k][l], minVal[k][r - (1 << k) + 1]);
	}
	int queryMax(int l, int r)
	{
		int length = r - l + 1;
		int k = Log[length];
		return std::max(maxVal[k][l], maxVal[k][r - (1 << k) + 1]);
	}
};
RMQ::LOG RMQ::Log;
struct work
{
	RMQ Val, Pos;
	work()
	{
		new(&Val) RMQ(a);
		new(&Pos) RMQ(pos);

		while (q--)
		{
			x = readIn();
			y = readIn();

			int minPos = x;
			int maxPos = y;
			int minVal = Val.queryMin(minPos, maxPos);
			int maxVal = Val.queryMax(minPos, maxPos);

			while (maxPos - minPos != maxVal - minVal)
			{
				minPos = Pos.queryMin(minVal, maxVal);
				maxPos = Pos.queryMax(minVal, maxVal);
				minVal = Val.queryMin(minPos, maxPos);
				maxVal = Val.queryMax(minPos, maxPos);
			}
			printOut(minPos);
			putchar(' ');
			printOut(maxPos);
			putchar('\n');
		}
	}
};

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
		a[i] = readIn();
	for (int i = 1; i <= n; i++)
		pos[a[i]] = i;
	q = readIn();

	if (n <= 1000 && q <= 1000)
		RunInstance(brute);
	else
		RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("ffs.in", "r", stdin);
	freopen("ffs.out", "w", stdout);
#endif
	run();
	return 0;
}