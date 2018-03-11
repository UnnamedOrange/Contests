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
	do buffer[length++] = -(x % 10) + '0';
	while (x /= 10);
	do putchar(buffer[--length]);
	while (length);
	putchar('\n');
}

const int mod = 998244353;
const int maxn = int(1e6) + 5;
int n;
int a[maxn];

#define RunInstance(x) delete new x
struct brute
{
	brute()
	{
		int p[15];
		for (int i = 1; i <= n; i++)
			p[i] = i;

		int ans = 0;
		do
		{
			bool bOk = true;
			for (int i = 1; i <= n; i++)
			{
				if (a[i] && a[i] != p[i])
				{
					bOk = false;
					break;
				}
				else if (!a[i] && p[i] == i)
				{
					bOk = false;
					break;
				}
			}
			if (bOk) ans++;
		} while (std::next_permutation(p + 1, p + 1 + n));
		printOut(ans);
	}
};
struct work
{
	int wp[maxn];
	void GetWP()
	{
		wp[0] = 1;
		wp[1] = 0;
		wp[2] = 1;
		for (int i = 3; i <= n; i++)
			wp[i] = (LL)(i - 1) * (wp[i - 2] + wp[i - 1]) % mod;
	}

	int fac[maxn];
	int inv[maxn];
	int invFac[maxn];
	void init()
	{
		fac[0] = 1;
		for (int i = 1; i <= n; i++)
			fac[i] = (LL)fac[i - 1] * i % mod;
		inv[1] = 1;
		for (int i = 2; i <= n; i++)
			inv[i] = (LL)(mod - mod / i) * inv[mod % i] % mod;
		invFac[0] = 1;
		for (int i = 1; i <= n; i++)
			invFac[i] = (LL)invFac[i - 1] * inv[i] % mod;
	}
	inline int C(int down, int up)
	{
		return (up > down) ? 0 : ((LL)fac[down] * invFac[up] % mod * invFac[down - up] % mod);
	}

	bool inDegree[maxn];
	int nHemi;
	int cHemiNode;
	int cCircNode;
	int remain;
	bool vis[maxn];
	work() : inDegree(), vis()
	{
		for (int i = 1; i <= n; i++)
			if (a[i]) inDegree[a[i]]++;

		nHemi = 0;
		cHemiNode = 0;
		cCircNode = 0;
		for (int i = 1; i <= n; i++)
		{
			if (a[i] && !inDegree[i])
			{
				nHemi++;
				int cnt = i;
				while (cnt)
				{
					vis[cnt] = true;
					cHemiNode++;
					cnt = a[cnt];
				}
			}
		}

		for (int i = 1; i <= n; i++)
		{
			if (a[i] && !vis[i])
			{
				int cnt = i;
				while (!vis[cnt])
				{
					vis[cnt] = true;
					cCircNode++;
					cnt = a[cnt];
				}
			}
		}

		remain = n - cCircNode - cHemiNode;
		GetWP();
		init();
		int tot = remain + nHemi;
		int ans = 0;
		for (int i = 0; i <= nHemi; i++)
		{
			int t = (LL)C(nHemi, i) * wp[tot - i] % mod;
			ans = (ans + t) % mod;
		}
		printOut(ans);
	}
};

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
		a[i] = readIn();

	if (n <= 10)
		RunInstance(brute);
	else
		RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("permutation.in", "r", stdin);
	freopen("permutation.out", "w", stdout);
#endif
	run();
	return 0;
}