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
	if (x < 0) putchar('-');
	else x = -x;
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
	putchar('\n');
}

const int maxn = 50005;
const int maxq = 100005;
const int mod = int(1e9) + 7;
int n, q;
int a[maxn];
struct Query
{
	int idx;
	int type;
	int param[2];
} querys[maxq];

#define RunInstance(x) delete new x
struct brute
{
	static int phi(int x)
	{
		int to = std::sqrt(x);
		int ret = x;
		for (int i = 2; i <= to; i++)
		{
			if (x % i) continue;
			ret = ret / i * (i - 1);
			while (!(x % i)) x /= i;
		}
		if (x != 1) ret = ret / x * (x - 1);
		return ret;
	}
	brute()
	{
		for (int i = 1; i <= q; i++)
		{
			int type = querys[i].type;
			if (type == 0)
				a[querys[i].param[0]] = querys[i].param[1];
			else if (type == 1)
			{
				int l = querys[i].param[0];
				int r = querys[i].param[1];
				int sum = 0;
				for (int i = l; i <= r; i++)
					sum += a[i];
				printOut(phi(sum));
			}
			else if (type == 2)
			{
				int l = querys[i].param[0];
				int r = querys[i].param[1];
				int mul = 1;
				for (int i = l; i <= r; i++)
					mul *= a[i];
				printOut(phi(mul));
			}
		}
	}
};
struct cheat
{
	struct BIT
	{
		int origin[maxn];
		LL bit[maxn];
		static inline int lowbit(int x) { return x & -x; }
		void add(int pos, int val)
		{
			origin[pos] += val;
			while (pos <= n)
			{
				bit[pos] += val;
				pos += lowbit(pos);
			}
		}
		LL query(int pos)
		{
			LL ret = 0;
			while (pos)
			{
				ret += bit[pos];
				pos ^= lowbit(pos);
			}
			return ret;
		}
		LL query(int l, int r) { return query(r) - query(l - 1); }
		void modify(int pos, int val) { add(pos, val - origin[pos]); }
		BIT() : bit(), origin()
		{
			for (int i = 1; i <= n; i++)
				modify(i, a[i]);
		}
	} bit;

	static const int limit = 200000;
	int prime[18000];
	int isntPrime[limit];
	int phi[limit];
	void init()
	{
		phi[1] = 1;
		isntPrime[1] = true;
		for (register int i = 2; i < limit; i++)
		{
			if (!isntPrime[i])
			{
				prime[++prime[0]] = i;
				phi[i] = i - 1;
			}
			for (register int j = 1, p = prime[j], s = i * p; j <= prime[0] && s < limit; j++, p = prime[j], s = i * p)
			{
				isntPrime[s] = true;
				if (i % p)
					phi[s] = phi[i] * (p - 1);
				else
				{
					phi[s] = phi[i] * p;
					break;
				}
			}
		}
	}

	LL Phi(LL x)
	{
		if (x < limit) return phi[x];
		LL ret = x;
		for (register LL i = 1, t = prime[i]; i <= prime[0] && t * t <= x; i++, t = prime[i])
		{
			if (x % t) continue;
			(ret /= t) *= (t - 1);
		}
		if (x != 1) (ret /= x) *= (x - 1);
		return ret;
	}

	cheat() : prime(), isntPrime(), phi()
	{
		init();
		for (int i = 1; i <= q; i++)
		{
			if (querys[i].type == 2) continue;
			if (querys[i].type == 0)
				bit.modify(querys[i].param[0], querys[i].param[1]);
			else if (querys[i].type == 1)
			{
				LL sum = bit.query(querys[i].param[0], querys[i].param[1]);
				printOut(Phi(sum) % mod);
			}
		}
	}
};

void run()
{
	n = readIn();
	q = readIn();
	for (int i = 1; i <= n; i++)
		a[i] = readIn();
	for (int i = 1; i <= q; i++)
	{
		querys[i].idx = i;
		querys[i].type = readIn();
		querys[i].param[0] = readIn();
		querys[i].param[1] = readIn();
	}

	if (n <= 5)
		RunInstance(brute);
	else
		RunInstance(cheat);
}

int main()
{
#ifndef LOCAL
	freopen("phi.in", "r", stdin);
	freopen("phi.out", "w", stdout);
#endif
	run();
	return 0;
}