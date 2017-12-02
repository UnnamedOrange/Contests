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
#include <cassert>
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

INT n, k, mod;
INT A, B, C, D;
#define Next(x) int(((long long)(x) * B + C) % D)

#define RunInstance(x) delete new x
struct work
{
	INT ans;
	int seqL[INT(2e7) + 5];
	int seqR[INT(2e7) + 5];
	INT cnt;

	work() : ans(0), cnt(A)
	{
		INT times = n / k + bool(n % k) - 2;
		for(int O = 1; O <= times; O++)
		{
			seqL[1] = cnt;
			for(int i = 2; i <= k; i++)
			{
				seqL[i] = Next(seqL[i - 1]);
			}
			cnt = Next(seqL[k]);

			seqR[1] = cnt;
			for(int i = 2; i <= k; i++)
			{
				seqR[i] = Next(seqR[i - 1]);
			}

			seqL[k + 1] = 1;
			for(int i = k - 1; i >= 1; i--)
			{
				seqL[i] = (long long)seqL[i + 1] * seqL[i] % mod;
			}
			seqR[0] = 1;
			for(int i = 2; i <= k; i++)
			{
				seqR[i] = (long long)seqR[i - 1] * seqR[i] % mod;
			}

			for(int i = 1; i <= k; i++)
			{
				ans ^= (long long)seqL[i] * seqR[i - 1] % mod;
			}
		}

		INT remain = n % k;
		remain = remain ? remain : k;
		seqL[1] = cnt;
		for(int i = 2; i <= k; i++)
		{
			seqL[i] = Next(seqL[i - 1]);
		}
		cnt = Next(seqL[k]);

		seqR[1] = cnt;
		for(int i = 2; i <= remain; i++)
		{
			seqR[i] = Next(seqR[i - 1]);
		}

		seqL[k + 1] = 1;
		for(int i = k - 1; i >= 1; i--)
		{
			seqL[i] = (long long)seqL[i + 1] * seqL[i] % mod;
		}
		seqR[0] = 1;
		for(int i = 2; i <= remain; i++)
		{
			seqR[i] = (long long)seqR[i - 1] * seqR[i] % mod;
		}

		for(int i = 1; i <= remain + 1; i++)
		{
			ans ^= (long long)seqL[i] * seqR[i - 1] % mod;
		}
		cout << ans << endl;
	}
};
//struct cheat2
//{
//	INT inv[INT(1e7) + 5];
//
//	INT ans;
//	cheat2() : ans(0)
//	{
//		inv[1] = 1;
//		for(int i = 2; i < mod; i++)
//		{
//			inv[i] = (mod - mod / i) * inv[mod % i] % mod;
//		}
//
//		INT front = A;
//		INT back = A;
//		INT mul = 1;
//		for(int i = 1; i < k; i++)
//		{
//			mul = mul * front % mod;
//			front = Next(front);
//		}
//		for(int i = k; i <= n; i++)
//		{
//			mul = mul * front % mod;
//			ans ^= mul;
//
//			mul = mul * inv[back % mod] % mod;
//
//			front = Next(front);
//			back = Next(back);
//		}
//		cout << ans << endl;
//	}
//};
struct cheat1
{
	INT ans;
	INT seq[1005];

	cheat1() : ans(0)
	{
		seq[1] = A;
		for(int i = 2; i <= n; i++)
		{
			seq[i] = Next(seq[i - 1]);
		}

		INT to1 = n - k + 1;
		for(int i = 1; i <= to1; i++)
		{
			INT to2 = i + k - 1;
			INT mul = 1;
			for(int j = i; j <= to2; j++)
			{
				mul = mul * seq[j] % mod;
			}
			ans ^= mul;
		}
		cout << ans << endl;
	}
};

bool isPrime(INT x)
{
	INT to = std::sqrt(x);
	for(int i = 2; i <= to; i++)
	{
		if(!(x % i))
			return false;
	}
	return true;
}
void run()
{
	n = readIn();
	k = readIn();
	mod = readIn();
	A = readIn();
	B = readIn();
	C = readIn();
	D = readIn();

	if(n <= 1000) RunInstance(cheat1);
//	else if(isPrime(mod) && mod <= INT(1e7)) RunInstance(cheat2);
	else RunInstance(work);
}

int main()
{
#ifndef JUDGE
	freopen("range.in", "r", stdin);
	freopen("range.out", "w", stdout);
#endif
	run();
	return 0;
}
