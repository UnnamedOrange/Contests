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
	while (!(std::isdigit(ch) || ch == '-')) ch = getchar();
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

const int maxn = int(1e6) + 5;
int n, m, mod, tp;
inline void add(int& a, const int& b)
{
	register int t;
	a = (t = a + b) >= mod ? t - mod : t;
}
inline void sub(int& a, const int& b)
{
	register int t;
	a = (t = a - b) < 0 ? t + mod : t;
}
char str[maxn];
struct OnlineHelper
{
	static const int Mod = int(1e9) + 7;
	int lastans;
	OnlineHelper() : lastans() {}
	int u, v, a, b, c;
	int i;
	void read()
	{
		u = readIn();
		v = readIn();
		a = readIn();
		b = readIn();
		c = readIn();
		i = 0;
	}
	int l, r;
	void next()
	{
		i++;
		int newU = (((LL)a * u + (LL)b * v + (LL)c * i) ^ lastans) % Mod;
		int newV = (((LL)b * u + (LL)c * v + (LL)a * i) ^ lastans) % Mod;
		u = newU;
		v = newV;
		l = u % n + 1;
		r = v % n + 1;
		if (l > r)
			std::swap(l, r);
	}
	const int& operator=(const int& t) { return lastans = t; }
} helper;

#define RunInstance(x) delete new x
struct brute1
{
	brute1()
	{
		int ans = 0;
		while (m--)
		{
			int l = readIn();
			int r = readIn();
			int length = r - l + 1;
			int U = 1 << length;
			std::vector<std::string> vec;
			for (int S = 1; S < U; S++)
			{
				int len = 0;
				char temp[20] = {};
				for (int i = 0; i < length; i++)
					if (S & (1 << i))
						temp[len++] = str[l + i];
				vec.push_back(temp);
			}
			std::sort(vec.begin(), vec.end());
			ans ^= ((std::unique(vec.begin(), vec.end()) - vec.begin()) % mod);
		}
		printOut(ans);
	}
};
struct brute2
{
	int pos[128];
	int pre[maxn];
	int sum[maxn];

	brute2() : pos(), pre()
	{
		for (int i = 1; i <= n; i++)
		{
			pre[i] = pos[str[i]];
			pos[str[i]] = i;
		}
		int ret = 0;
		while (m--)
		{
			int l, r;
			if (tp)
			{
				helper.next();
				l = helper.l;
				r = helper.r;
			}
			else
			{
				l = readIn();
				r = readIn();
			}

			std::memset(sum + l - 1, 0, sizeof(sum[0]) * (r - l + 2));
			sum[l - 1] = 1;
			for (int i = l; i <= r; i++)
			{
				sum[i] = (sum[i - 1] << 1) % mod;
				//printf("sum[%d] = %d\n", i, sum[i]);
				int t = std::max(l - 1, pre[i]);
				sub(sum[i], t - 1 >= l - 1 ? sum[t - 1] : 0);
				//printf("sum[%d] = %d\n", i, sum[i]);
			}
			int ans = sum[r];
			sub(ans, 1);
			if (tp)
				ret = helper = ans;
			else
				ret ^= ans;
		}
		printOut(ret);
	}
};

void run()
{
	n = readIn();
	m = readIn();
	mod = readIn();
	tp = readIn();
	for (int i = 1; i <= n; i++)
	{
		char ch = getchar();
		while (!std::isalpha(ch)) ch = getchar();
		str[i] = ch;
	}
	if (tp) helper.read();

	if (n <= 15 && m <= 100 && !tp)
		RunInstance(brute1);
	else if ((n <= 1000 && m <= 1000) || (n <= 100000 && m <= 1))
		RunInstance(brute2);
	else
		RunInstance(brute2);
}

int main()
{
#ifndef LOCAL
	freopen("embroidery.in", "r", stdin);
	freopen("embroidery.out", "w", stdout);
#endif
	run();
	return 0;
}