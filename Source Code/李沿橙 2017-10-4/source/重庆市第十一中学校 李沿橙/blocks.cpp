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
	static bool output = false;
	if(output) putchar(' ');
	output = true;
	if(!x)
	{
		putchar('0');
	}
	else
	{
		char buffer[7];
		INT length = 0;
		while(x)
		{
			buffer[length++] = x % 10 + '0';
			x /= 10;
		}
		do
		{
			putchar(buffer[--length]);
		}
		while(length);
	}
}

const INT INF = (~(INT(1) << (sizeof(INT) * 8 - 1)));
const INT maxn = 1000005;
INT n, m, K;
INT a[maxn];

INT sum[maxn];
INT s[maxn];
INT t;
#define RunInstance(x) delete new x
struct work
{
	work()
	{
		t = 1;
		for(int i = 1; i <= n; i++) sum[i] = sum[i - 1] + a[i] - K;
		for(int i = 1; i <= n; i++)
		{
			if(!t || sum[i] < sum[s[t]]) s[++t] = i;
		}
		INT ans = 0;
		for(int i = n; i >= 1; i--)
		{
			while(t && sum[s[t]] <= sum[i]) t--;
			ans = std::max(ans, i - s[t + 1]);
		}
		printOut(ans);
	}
};

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= n; i++)
	{
		a[i] = readIn();
	}
	while (m--)
	{
		K = readIn();
		RunInstance(work);
	}
}

int main()
{
#ifndef JUDGE
	freopen("blocks.in", "r", stdin);
	freopen("blocks.out", "w", stdout);
#endif
	run();
	return 0;
}
