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

LL mod = int(1e9) + 7;
LL s, t, n, m;

#define RunInstance(x) delete new x
struct brute
{
	struct Poly
	{
		LL f[105];
		LL& operator[](int x) { return f[x]; }
		const LL& operator[](int x) const { return f[x]; }
		Poly() : f() {}
		Poly operator*(const Poly& b) const
		{
			Poly ret;
			for (int i = 0; i <= s; i++)
				for (int j = 0; j <= i; j++)
					ret[i] = (ret[i] + f[j] * b[i - j]) % mod;
			return ret;
		}
	} base1, base2, ans;
	brute()
	{
		ans[0] = 1;
		for (int i = 1; i <= t; i++)
			base1[i] = 1;
		for (int i = 1; i <= s; i++)
			base2[i] = 1;
		for (int i = 1; i <= n; i++)
			ans = ans * base1;
		for (int j = n + 1; j <= m; j++)
			ans = ans * base2;
		LL ret = 0, temp;
		for (int i = 0; i <= s; i++)
			ret = (temp = ret + ans[i]) >= mod ? temp - mod : temp;
		printOut(ret);
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
	s = readIn();
	t = readIn();
	n = readIn();
	m = readIn();
	if (s <= 100 && t <= 100 && n <= 100 && m <= 100)
		RunInstance(brute);
	else
		RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("function.in", "r", stdin);
	freopen("function.out", "w", stdout);
#endif
	run();
	return 0;
}
