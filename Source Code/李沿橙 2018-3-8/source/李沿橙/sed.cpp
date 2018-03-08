#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cctype>
#include <climits>
#include <cassert>
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
typedef ULL INT_PUT;
INT_PUT readIn()
{
	INT_PUT a = 0;
	bool minus = false;
	char ch = getchar();
	while (!(ch == '-' || std::isdigit(ch))) ch = getchar();
	if (ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while (std::isdigit(ch))
	{
		a = a * 10 + (ch - '0');
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}
void printOut(INT_PUT x)
{
	char buffer[20];
	int length = 0;
	if (x < 0)
	{
		putchar('-');
		x = -x;
	}
	do
	{
		buffer[length++] = x % 10 + '0';
		x /= 10;
	} while (x);
	do
	{
		putchar(buffer[--length]);
	} while (length);
}

const int maxn = 70;
int n;
ULL b[maxn];
ULL v;

#define RunInstance(x) delete new x
struct brute1
{
	struct Key
	{
		ULL val;
		int S;
		Key() {}
		Key(ULL val, int S) : val(val), S(S) {}
		bool operator<(const Key& b) const
		{
			return val < b.val;
		}
	};
	Key v1[(1 << 20) + 5];
	Key v2[(1 << 20) + 5];

	brute1()
	{
		int half = n / 2;
		int U1 = 1 << half;

		for (int S = 0; S < U1; S++)
		{
			ULL sum = 0;
			for (int i = 0; i < half; i++)
				if (S & (1 << i))
					sum += b[i];
			v1[S] = Key(sum, S);
		}
		std::sort(v1, v1 + U1);

		int remain = n - half;
		int U2 = 1 << remain;
		for (int S = 0; S < U2; S++)
		{
			ULL sum = 0;
			for (int i = 0; i < remain; i++)
				if (S & (1 << i))
					sum += b[half + i];
			v2[S] = Key(v - sum, S);
		}
		std::sort(v2, v2 + U2);

		int j = 0;
		for (int i = 0; i < U1; i++)
		{
			while (j < U2 && v1[i].val > v2[j].val)
				j++;
			if (v1[i].val == v2[j].val)
			{
				for (int k = 0; k < half; k++)
					if (v1[i].S & (1 << k))
						putchar('1');
					else
						putchar('0');
				for (int k = 0; k < remain; k++)
					if (v2[j].S & (1 << k))
						putchar('1');
					else
						putchar('0');
				break;
			}
		}
	}
};
ULL power(ULL x, ULL y)
{
	ULL ret = 1;
	while (y)
	{
		if (y & 1) ret *= x;
		x *= x;
		y >>= 1;
	}
	return ret;
}
struct brute2
{
	bool c[maxn];
	bool check(ULL r, ULL A)
	{
		ULL invR = power(r, (1ull << 63) - 1);
		ULL a[maxn];
		a[0] = invR * b[0];
		if (a[0] != A)
			return false;

		for (int i = 1; i < n; i++)
			a[i] = invR * b[i];

		ULL remain = invR * v;
		for (int i = n - 1; ~i; i--)
			if (remain >= a[i])
			{
				remain -= a[i];
				c[i] = true;
			}
			else
				c[i] = false;
		return !remain;
	}

	brute2()
	{
		int cnt = 0;
		ULL B = b[0];
		while (!(B & 1))
		{
			cnt++;
			B >>= 1;
		}
		for (ULL A = 1; ; A += 2)
		{
			if (!(A & 1)) continue;
			ULL invA = power(A, (1ull << (63 - cnt)) - 1);
			if (cnt) invA &= (1ull << (64 - cnt)) - 1;
			ULL r = B * invA;
			if (!(r & 1)) continue;
			if (cnt) r &= (1ull << (64 - cnt)) - 1;

			if (!cnt)
			{
				if (check(r, A))
				{
					for (int i = 0; i < n; i++)
						putchar(c[i] + '0');
					break;
				}
			}
			else
			{
				int U = 1 << cnt;
				for (int i = 0; i < U; i++)
				{
					if (check(r | ((ULL)i << (64 - cnt)), A << cnt))
					{
						for (int i = 0; i < n; i++)
							putchar(c[i] + '0');
						return;
					}
				}
			}
		}
	}
};

void run()
{
	n = readIn();
	for (int i = 0; i < n; i++)
		b[i] = readIn();
	v = readIn();

	if (n <= 40)
		RunInstance(brute1);
	else
		RunInstance(brute2);
}

int main()
{
#ifndef LOCAL
	freopen("sed.in", "r", stdin);
	freopen("sed.out", "w", stdout);
#endif
	run();
	return 0;
}