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
typedef long long INT;
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
	static char buffer[20];
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

const INT maxn = 100005;
INT n, m;
struct Object
{
	INT cost;
	INT value;

	void read()
	{
		cost = readIn();
		value = readIn();
	}
	bool operator< (const Object& b) const
	{
		if (cost != b.cost) return cost > b.cost;
		return value > b.value;
	}
} objects[maxn];
struct Man
{
	INT money;
	INT ans;

	Man() : ans() {}
	void read()
	{
		money = readIn();
	}
} men[maxn];

#define RunInstance(x) delete new x
struct brute
{
	brute()
	{
		for (int i = 1; i <= m; i++)
		{
			INT& money = men[i].money;
			INT& ans = men[i].ans;
			for (int j = 1; j <= n; j++)
			{
				if (money < objects[j].cost) continue;
				ans += objects[j].value;
				money -= objects[j].cost;
			}
			printOut(ans);
		}
	}
};
struct work
{
	INT cost[maxn];
	INT sumCost[maxn];
	INT sumValue[maxn];

	work()
	{
		sumCost[0] = sumValue[0] = 0;
		for (int i = 1; i <= n; i++)
		{
			cost[i] = objects[i].cost;
			sumCost[i] = sumCost[i - 1] + cost[i];
			sumValue[i] = sumValue[i - 1] + objects[i].value;
		}

		for (int i = 1; i <= m; i++)
		{
			INT& money = men[i].money;
			INT& ans = men[i].ans;
			INT pos = 1;
			while (pos <= n)
			{
				INT t = std::lower_bound(cost + pos, cost + 1 + n, money, std::greater<INT>()) - cost;
				if (t == n + 1) break;
				INT e = std::upper_bound(sumCost + t, sumCost + 1 + n, money + sumCost[t - 1]) - sumCost - 1;

				money -= sumCost[e] - sumCost[t - 1];
				ans += sumValue[e] - sumValue[t - 1];
				pos = e + 1;
			}
			printOut(ans);
		}
	}
};

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= n; i++)
		objects[i].read();
	std::sort(objects + 1, objects + 1 + n);
	for (int i = 1; i <= m; i++)
		men[i].read();

	if (n <= 1000 && m <= 1000)
		RunInstance(brute);
	else
		RunInstance(work);
}

int main()
{
#ifndef JUDGE
	freopen("pack.in", "r", stdin);
	freopen("pack.out", "w", stdout);
#endif
	run();
	return 0;
}
