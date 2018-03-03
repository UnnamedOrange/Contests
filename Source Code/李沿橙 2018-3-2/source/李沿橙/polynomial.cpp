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
#include <functional>
#include <cassert>
typedef long long LL;
typedef unsigned long long ULL;
typedef __int128 INT128;
using std::cin;
using std::cout;
using std::endl;
LL readIn()
{
	LL a = 0;
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
void printOut(LL x)
{
	int length = 0;
	char buffer[20];
	if (x < 0)
	{
		putchar('-');
		x = -x;
	}
	do
	{
		buffer[length++] = x % 10 + '0';
		x /= 10;
	} while (x);
	do
	{
		putchar(buffer[--length]);
	} while (length);
	putchar('\n');
}

const int mod = 998244353;
LL a, b, c;

#define RunInstance(x) delete new x
struct work
{
	std::vector<INT128> power1;
	std::vector<INT128> power2;
	int ans;

	void search(int idx, INT128 sum1, INT128 sum2)
	{
		if (!idx)
		{
			if (sum1 == sum2)
			{
				ans++;
				if (ans == mod)
					ans = 0;
			}
			return;
		}
		else if (idx == 1)
		{
			LL a1 = (sum1 - sum2) / (power1[idx] - power2[idx]);
			if (a1 >= 0 && sum1 - a1 * power1[idx] >= 0 && a1 * (power1[idx] - power2[idx]) == (sum1 - sum2) && sum1 - a1 * power1[idx] == sum2 - a1 * power2[idx])
				ans++;
			return;
		}
		INT128 mul1 = 0, mul2 = 0;
		while (mul1 <= sum1 && mul2 <= sum2)
		{
			search(idx - 1, sum1 - mul1, sum2 - mul2);
			mul1 += power1[idx];
			mul2 += power2[idx];
		}
	}

	work() : ans()
	{
		power2.push_back(1);
		while (power2.back() * b <= c)
			power2.push_back(power2.back() * b);

		power1.push_back(1);
		while (power1.size() < power2.size())
			power1.push_back(power1.back() * a);

		search(power2.size() - 1, b, c);
		printOut(ans);
	}
};

void run()
{
	while (cin >> a >> b >> c)
	{
		if (a == 1 && b == 1 && c == 1) //任意一项系数为1即可满足条件
		{
			puts("infinity");
			continue;
		}
		else if (a == b && b != c) //矛盾
		{
			printOut(0);
			continue;
		}
		else if (a > b && c > b) //不满足单调性
		{
			printOut(0);
			continue;
		}
		else if (a > b && b == c) //如果有非常数项，将不满足单调性，所以只有一个常数项
		{
			printOut(1);
			continue;
		}
		else if (a == b && b == c && a == c) //要么常数项，要么一次项
		{
			printOut(2);
			continue;
		}
		RunInstance(work);
	}
}

int main()
{
#ifndef LOCAL
	freopen("polynomial.in", "r", stdin);
	freopen("polynomial.out", "w", stdout);
#endif
	run();
	return 0;
}