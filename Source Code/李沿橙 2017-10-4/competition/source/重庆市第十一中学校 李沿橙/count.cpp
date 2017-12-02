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

const INT mod = 998244353;
const INT maxn = INT(1e8) + 5;
INT l, r, k;

INT gcd(INT a, INT b)
{
	return !b ? a : gcd(b, a % b);
}
inline INT power(INT x, INT y)
{
	INT ret = 1;
	while(y)
	{
		if(y & 1) ret = ret * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return ret;
}

//2, 2, 3, 4, 5, 6, 7, 8, ...
#define RunInstance(x) delete new x
struct cheat2
{
	cheat2()
	{
		INT ans = 0;
		if(l == 1)
		{
			ans = power(2, k);
			l++;
		}
		for(int i = l; i <= r; i++)
		{
			ans = (ans + power(i, k)) % mod;
		}
		cout << ans << endl;
	}
};
struct cheat1
{
	static INT f(INT x)
	{
		INT sum = 0;
		INT count_ = 0;
		for(int i = 1; i <= x; i++)
		{
			if(gcd(x, i) == 1)
			{
				sum += i;
				count_++;
			}
		}
		return sum * 2 / count_;
	}

	cheat1()
	{
		INT ans = 0;
		for(int i = l; i <= r; i++)
		{
			ans = (ans + power(f(i), k)) % mod;
		}
		cout << ans << endl;
	}
};
struct work : cheat2
{
	work()
	{

	}
};

void run()
{
	l = readIn();
	r = readIn();
	k = readIn();

	if(r <= 100) RunInstance(cheat1);
	else if(r <= 1000000) RunInstance(cheat2);
	else if(k == 1)
	{
		INT ans = 0;
		if(l == 1)
		{
			ans = 2;
			l++;
		}
		if(r >= l)
		{
			ans = (ans + (l + r) * (r - l + 1) % mod * power(2, mod - 2) % mod) % mod;
		}
		cout << ans << endl;
	}
	else if(k == 2)
	{
		INT ans = 0;
		if(l == 1)
		{
			ans = 4;
			l++;
		}
		if(r >= l)
		{
			ans = (ans + (r * (r + 1) % mod * (2 * r + 1) % mod * power(6, mod - 2)) - ((l - 1) * l % mod * (2 * l - 1) % mod * power(6, mod - 2))) % mod;
		}
		cout << ans << endl;
	}
	else if(k == 3)
	{
		INT ans = 0;
		if(l == 1)
		{
			ans = 8;
			l++;
		}
		if(r >= l)
		{
			INT R = r * (r + 1) % mod * power(2, mod - 2) % mod;
			R = R * R % mod;
			INT L = (l - 1) * l % mod * power(2, mod - 2) % mod;
			L = L * L % mod;
			ans = (ans + R - L + mod) % mod;
		}
		cout << ans << endl;
	}
	else RunInstance(work);
}
int main()
{
#ifndef JUDGE
	freopen("count.in", "r", stdin);
	freopen("count.out", "w", stdout);
#endif
	run();
	return 0;
}
