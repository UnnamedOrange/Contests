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
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
}

const int maxn = 20;
int n, m;
int a[maxn];

#define RunInstance(x) delete new x
struct brute
{
	brute()
	{
		LL ans = 0;
		int per[maxn];
		for (int i = 1; i <= n; i++)
			per[i] = i;
		do
		{
			int f[maxn];
			int pre[maxn] = {};
			int max = 0;
			for (int i = 1; i <= n; i++)
			{
				f[i] = 1;
				for (int j = 0; j < i; j++)
				{
					if (per[j] < per[i])
					{
						if (f[j] + 1 >= f[i] && (f[j] + 1 > f[i] || per[j] == a[f[j]]))
						{
							f[i] = f[j] + 1;
							pre[i] = j;
						}
					}
				}
				max = std::max(max, f[i]);
			}
			if (max != m) continue;
			int cnt;
			for (cnt = 1; cnt <= n; cnt++)
				if (per[cnt] == a[m]) break;
			if (f[cnt] != max) continue;
			bool bOk = true;
			int t;
			for (t = m; cnt && t; cnt = pre[cnt], t--)
			{
				if (per[cnt] != a[t])
				{
					bOk = false;
					break;
				}
			}
			if (cnt || t) bOk = false;
			if (bOk) ans++;
		} while (std::next_permutation(per + 1, per + 1 + n));
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
	m = readIn();
	for (int i = 1; i <= m; i++) a[i] = readIn();

	if (n <= 9)
		RunInstance(brute);
	else
		RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("arg.in", "r", stdin);
	freopen("arg.out", "w", stdout);
#endif
	run();
	return 0;
}
