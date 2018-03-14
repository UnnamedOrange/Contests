#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cassert>
#include <climits>
#include <cctype>
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
	char buffer[20];
	int length = 0;
	if (x < 0) putchar('-');
	else x = -x;
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
	putchar('\n');
}

const int mod = 998244353;
LL n, k;

#define RunInstance(x) delete new x
struct brute
{
	int str[50];
	int ans;
	bool isGood(int l)
	{
		int f[3] = {};
		for (int i = l; i <= str[0]; i++)
			f[str[i]]++;
		return std::abs(f[0] - f[1]) <= k &&
			std::abs(f[0] - f[2]) <= k &&
			std::abs(f[1] - f[2]) <= k;
	}
	void debugPrint()
	{
		for (int i = 1; i <= str[0]; i++)
			printf("%d ", str[i]);
		putchar('\n');
	}
	void search()
	{
		for (int i = 1; i <= str[0]; i++)
			if (!isGood(i)) return;
		if (str[0] == n)
		{
			ans++;
#ifdef LOCAL
			//			debugPrint();
#endif
			return;
		}
		for (int i = 0; i < 3; i++)
		{
			str[++str[0]] = i;
			search();
			str[0]--;
		}
	}

	brute() : ans()
	{
		str[0] = 0;
		search();
		printOut(ans);
	}
};
struct cheat1
{
	cheat1()
	{
		if (n == 1) printOut(3);
		else printOut(6);
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
	k = readIn();

	if (n <= 10)
		RunInstance(brute);
	else if (k == 1)
		RunInstance(cheat1);
	else
		RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("baofushehui.in", "r", stdin);
	freopen("baofushehui.out", "w", stdout);
#endif
	run();
	return 0;
}