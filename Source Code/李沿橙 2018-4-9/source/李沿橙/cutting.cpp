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
		(a *= 10) -= ch - '0';
		ch = getchar();
	}
	return positive ? -a : a;
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

const int maxn = int(1e5) + 5;
int n, q;
char str[maxn];
struct Query
{
	int l, r;
	void read() { l = readIn(); r = readIn(); }
} querys[maxn];

#define RunInstance(x) delete new x
struct brute
{
	static const int maxN = maxn;
	ULL hashVal[maxN];
	ULL power[maxN];
	bool appear[maxN];
	int nxt[maxN];

	brute()
	{
		power[0] = 1;
		for (int i = 1; i <= n; i++)
			power[i] = power[i - 1] * 131;
		hashVal[0] = 0;
		for (int i = 1; i <= n; i++)
			hashVal[i] = hashVal[i - 1] * 131 + str[i];

		for (int i = 1; i <= q; i++)
		{
			int l = querys[i].l;
			int r = querys[i].r;
			int len = r - l + 1;
			memset(appear, 0, sizeof(appear));
			ULL hashThis = hashVal[r] - hashVal[l - 1] * power[len];
			for (int j = len; j <= n; j++)
				if (hashVal[j] - hashVal[j - len] * power[len] == hashThis)
					appear[j] = true;
			int pre = 0;
			for (int j = n; j; j--)
			{
				if (appear[j]) pre = j;
				nxt[j] = pre;
			}
			int rightOne = 0;
			for (int j = n; j; j--)
			{
				if (appear[j])
				{
					rightOne = j;
					break;
				}
			}

			LL ans = 0;
			for (int L = 1; L <= n; L++)
			{
				if (appear[L])
				{
					ans += (LL)(n - L) * (n - L - 1) / 2;
					break;
				}
				if (rightOne - len + 1 < L + 1) continue;
				int right_left = L + 2;
				int right_right = rightOne - len + 1;

				int right_left2 = nxt[L + len] + 1;
				if (right_right > right_left2) right_right = right_left2 - 1;
				ans += right_right - right_left + 1 + n - right_left2 + 1;
			}
			printOut(ans);
		}
	}
};

void run()
{
	n = readIn();
	q = readIn();
	scanf("%s", str + 1);
	for (int i = 1; i <= q; i++)
		querys[i].read();

	if (n <= 2000)
		RunInstance(brute);
	else
		RunInstance(brute);
}

int main()
{
#ifndef LOCAL
	freopen("cutting.in", "r", stdin);
	freopen("cutting.out", "w", stdout);
#endif
	run();
	return 0;
}
