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
typedef int INT;
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

const INT maxn = 2e6 + 5;
INT n, k, f;
INT A[maxn];
INT sum[maxn];
bool sieve[maxn];

INT maxA;

void work(INT g)
{
	if (sieve[g]) return;
	INT accepted = 0;
	if (g <= k)
	{
		accepted += sum[maxA] - sum[g - 1];
	}
	else
	{
		for (int i = g; i <= maxA; i += g)
		{
			accepted += sum[std::min(maxA, i + k)] - sum[i - 1];
		}
	}

	if (accepted + f < n)
	{
		for (int i = g; i <= maxA; i += g)
		{
			sieve[i] = true;
		}
	}
}

void run()
{
	INT T = readIn();
	while (T--)
	{
		n = readIn();
		k = readIn();
		f = readIn();
		memset(sum, 0, sizeof(sum));
		memset(sieve, 0, sizeof(sieve));

		maxA = 0;
		for (int i = 1; i <= n; i++)
		{
			A[i] = readIn();
			maxA = std::max(maxA, A[i]);
			sum[A[i]]++;
		}
		for (int i = 1; i <= maxA; i++)
		{
			sum[i] += sum[i - 1];
		}

		for (int i = 1; i <= maxA; i++)
		{
			work(i);
		}

		for (int i = 1; i <= maxA; i++)
		{
			if (!sieve[i]) printf("%d ", i);
		}
		puts("");
	}
}

int main()
{
	run();
	return 0;
}