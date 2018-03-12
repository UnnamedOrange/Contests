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
	char buffer[20];
	int length = 0;
	if (x < 0)
		putchar('-');
	else
		x = -x;
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
	putchar('\n');
}

const int maxn = int(1e5) + 5;
int l;
int n;
int v[maxn], a[maxn];
int m;
int w[maxn], b[maxn];

#define RunInstance(x) x()

int delta[maxn];
void brute()
{
	memset(delta, 0, sizeof(int) * (l + 1));
	int t, accum;
	t = 0;
	accum = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= a[i]; j++, t++)
			delta[t + 1] = (accum += v[i]);
	t = 0;
	accum = 0;
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= b[i]; j++, t++)
			delta[t + 1] -= (accum += w[i]);

	std::sort(delta, delta + 1 + t);
	int ans = 1;
	int cnt = 1;
	int pre = delta[0];
	for (int i = 1; i <= l; i++)
	{
		if (delta[i] != pre)
		{
			cnt = 1;
			pre = delta[i];
		}
		else cnt++;
		ans = std::max(ans, cnt);
	}
	printOut(ans);
}

void work()
{

}


void run()
{
	int T = readIn();
	while (T--)
	{
		l = 0;
		n = readIn();
		for (int i = 1; i <= n; i++)
		{
			v[i] = readIn();
			a[i] = readIn();
			l += a[i];
		}
		m = readIn();
		for (int i = 1; i <= m; i++)
		{
			w[i] = readIn();
			b[i] = readIn();
		}

		if (l <= int(2e5))
			RunInstance(brute);
		else
			RunInstance(work);
	}
}

int main()
{
#ifndef LOCAL
	freopen("robot.in", "r", stdin);
	freopen("robot.out", "w", stdout);
#endif
	run();
	return 0;
}