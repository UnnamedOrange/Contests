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
inline void printOut(INT x)
{
	if (!x)
	{
		putchar('0');
	}
	else
	{
		char buffer[9];
		INT length = 0;
		bool minus = x < 0;
		if (minus) x = -x;
		while (x)
		{
			buffer[length++] = x % 10 + '0';
			x /= 10;
		}
		if (minus) buffer[length++] = '-';
		do
		{
			putchar(buffer[--length]);
		} while (length);
	}
	putchar('\n');
}

const INT INF = (~(INT(1) << (sizeof(INT) * 8 - 1)));
const INT maxn = INT(2e5) + 5;
INT n, q;
INT origin[maxn];

#define RunInstance(x) delete new x
struct cheat1
{
	bool unava[maxn];

	cheat1() : unava()
	{
		INT nStudent;
		INT sum = 0;
		for (int i = 1; i <= n; i++)
		{
			nStudent += origin[i];
			sum += i * origin[i];
		}

		while (q--)
		{
			INT ins = readIn();
			switch (ins)
			{
			case 1:
			case 2:
			{
				INT pos = readIn();
				INT val = readIn();
				if (ins == 2) val = -val;
				origin[pos] += val;
				nStudent += val;
				sum += pos * val;
				break;
			}
			case 3:
			case 4:
			{
				INT l = readIn();
				INT r = readIn();
				bool t = false;
				if (ins == 4) t = true;
				for (int i = l; i <= r; i++) unava[i] = t;
				break;
			}
			}

			INT ans = -1;
			INT minDis = INF;
			INT left = 0;
			INT right = nStudent;
			INT dis = sum;
			for (int i = 1; i <= n; i++)
			{
				dis += left;
				dis -= right;
				left += origin[i];
				right -= origin[i];
				if (unava[i]) continue;
				if (dis < minDis)
				{
					ans = i;
					minDis = dis;
				}
			}
			printOut(ans);
		}
	}
};
struct cheat2
{
	INT nStudent;

	struct BIT
	{
#define lowbit(x) ((x) & -(x))
		INT bit[maxn];

		BIT() : bit() {}
		void add(INT x, INT val)
		{
			while (x <= n)
			{
				bit[x] += val;
				x += lowbit(x);
			}
		}
		INT operator() (INT x)
		{
			INT ret = 0;
			while (x > 0)
			{
				ret += bit[x];
				x -= lowbit(x);
			}
			return ret;
		}
	} bit;

	INT divide()
	{
		INT l = 1, r = n;
		while (r - l > 0)
		{
			INT mid = l + ((r - l) >> 1);
			if (bit(mid) < (nStudent >> 1) + (nStudent & 1))
				l = mid + 1;
			else
				r = mid;
		}
		return l;
	}

	cheat2() : nStudent()
	{
		for (int i = 1; i <= n; i++)
		{
			bit.add(i, origin[i]);
			nStudent += origin[i];
		}

		while (q--)
		{
			INT ins = readIn();
			switch (ins)
			{
			case 1:
			case 2:
			{
				INT pos = readIn();
				INT val = readIn();
				if (ins == 2) val = -val;
				bit.add(pos, val);
				nStudent += val;
				break;
			}
			case 3:
			case 4:
			{
				readIn();
				readIn();
				break;
			}
			}
			printOut(divide());
		}
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
	n = readIn();
	q = readIn();
	for (int i = 1; i <= n; i++) origin[i] = readIn();

	if (n <= 2000 && q <= 2000)
		RunInstance(cheat1);
	else
		RunInstance(cheat2);
}

int main()
{
#ifndef JUDGE
	freopen("position.in", "r", stdin);
	freopen("position.out", "w", stdout);
#endif
	run();
	return 0;
}
