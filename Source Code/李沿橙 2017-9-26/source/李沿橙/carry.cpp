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

INT a, b, c;

#define RunInstance(x) delete new x
struct work
{
	static inline bool go(INT& A, INT &B, INT &C)
	{
		INT x = (B + C) >> 1;
		INT y = (A + C) >> 1;
		INT z = (A + B) >> 1;
		A = x;
		B = y;
		C = z;
		return A & 1 || B & 1 || C & 1;
	}

	work()
	{
		INT ans = 0;
		INT na = a, nb = b, nc = c;
		INT ma = a, mb = b, mc = c;
		while(true)
		{
			go(na, nb, nc);

			bool ret;
			ret = go(ma, mb, mc);
			if(ret)
			{
				ans = (ans << 1) + 1;
				break;
			}
			ret = go(ma, mb, mc);
			if(ret)
			{
				ans = (ans << 1) + 2;
				break;
			}
			ans++;

			if(na == ma && nb == mb && nc == mc)
			{
				ans = -1;
				break;
			}

		}
		cout << ans << endl;
	}
};

void run()
{
	INT T = readIn();
	while(T--)
	{
		a = readIn();
		b = readIn();
		c = readIn();
		if(a & 1 || b & 1 || c & 1) cout << 0 << endl;
		else RunInstance(work);
	}
}

int main()
{
#ifndef JUDGE
	freopen("carry.in", "r", stdin);
	freopen("carry.out", "w", stdout);
#endif
	run();
	return 0;
}
