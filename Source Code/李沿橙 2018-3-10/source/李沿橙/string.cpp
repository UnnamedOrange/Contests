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
	do
	{
		buffer[length++] = -(x % 10) + '0';
	} while (x /= 10);
	do
	{
		putchar(buffer[--length]);
	} while (length);
}

const int maxn = int(5e5) + 5;
int n;
int a[maxn];
int p1 = true;

#define RunInstance(x) delete new x
struct cheat
{
	cheat()
	{
		LL ans = 0;
		for(int i = 1; i <= n; i++)
			ans += (LL)i * (n - i + 1);
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
	n = readIn();
	for(int i = 1; i <= n; i++)
		a[i] = readIn();
	for(int i = 1; i <= n; i++)
		if(a[i]) p1 = false;
	
	if(p1)
		RunInstance(cheat);
}

int main()
{
#ifndef LOCAL
	freopen("string.in", "r", stdin);
	freopen("string.out", "w", stdout);
#endif
	run();
	return 0;
}
