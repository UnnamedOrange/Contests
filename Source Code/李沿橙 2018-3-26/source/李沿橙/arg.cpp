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
typedef long long INT_PUT;
INT_PUT readIn()
{
	INT_PUT a = 0; bool positive = true;
	char ch = getchar();
	while (!(ch == '-' || std::isdigit(ch))) ch = getchar();
	if (ch == '-') { positive = false; ch = getchar(); }
	while (std::isdigit(ch)) { a = a * 10 - (ch - '0'); ch = getchar(); }
	return positive ? -a : a;
}
void printOut(INT_PUT x)
{
	char buffer[20]; int length = 0;
	if (x < 0) putchar('-'); else x = -x;
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
}

const int maxn = 16;
int n, m;
int a[maxn];
int b[maxn];

LL f[14348907 + 5];
int status[14348907 + 5];

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= m; i++) a[i] = readIn();
	for (int i = 1; i <= m; i++) b[a[i]] = 1;
	int U = 1;
	for (int i = 1; i <= n; i++) U *= 3;
	f[0] = 1;
	for (register int S = 0; S < U; S++) if (f[S]) // note
	{
		int appear[maxn] = {};
		int cnt[3] = {};
		int t = S;
		for (register int i = 1; i <= n; i++)
		{
			appear[i] = t % 3;
			t /= 3;
			cnt[appear[i]]++;
		}
		if (cnt[1] == m && cnt[1] + cnt[2] == n) status[++status[0]] = S;
		else if (cnt[1] > m) continue; // note
		for (register int i = 1; i <= n; i++)
		{
			if (!appear[i])
			{
				int T = 0;
				bool bFound = false;
				int t = 1, q = 0;
				for (int j = 1, base = 1; j <= n; j++, base *= 3)
				{
					if (appear[j])
					{
						if (j == a[t])
							t++;
						q += b[j];
					}

					if (i == j)
						T += base;
					else if (!bFound && j > i && appear[j] == 1)
					{
						T += (base << 1);
						bFound = true;
					}
					else
						T += base * appear[j];
				}
				if (t - 1 == q) f[T] += f[S];
			}
		}
	}
	LL ans = 0;
	for (register int i = 1; i <= status[0]; i++)
	{
		int S = status[i];
		ans += f[status[i]];
	}
	printOut(ans);
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