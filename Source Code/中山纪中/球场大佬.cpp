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
inline void printOut(INT x)
{
	if (!x)
	{
		putchar('0');
		putchar('\n');
		return;
	}
	char buffer[10];
	INT length = 0;
	while (x)
	{
		buffer[length++] = x % 10 + '0';
		x /= 10;
	}
	do
	{
		putchar(buffer[--length]);
	} while (length);
	putchar('\n');
}

const INT mod = 1e9 + 7;
const INT maxn = 2005;
INT n;
INT A[maxn];
INT count_;
INT Double[maxn * maxn];

void work()
{
	INT ans = 0;
	count_ = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = i + 1; j <= n; j++)
		{
			Double[++count_] = A[i] + A[j];
		}
	}
	std::sort(Double + 1, Double + 1 + count_);
	for (int i = 1; i <= count_; i++)
	{
		ans += Double[i] * ((i - 1) - (count_ - i)) % mod + mod;
		ans %= mod;
	}

	std::sort(A + 1, A + 1 + n);
	INT temp = 0;
	for (int i = 1; i <= n; i++)
	{
		temp += A[i] * ((i - 1) - (n - i)) % mod + mod;
		temp %= mod;
	}
	temp *= n - 2;
	temp %= mod;
	ans -= temp;
	ans += mod;
	ans <<= 1;
	ans %= mod;
	printOut(ans);
}

void run()
{
	INT T = readIn();
	while (T--)
	{
		n = readIn();
		for (int i = 1; i <= n; i++)
		{
			A[i] = readIn();
		}
		work();
	}
}

int main()
{
	run();
	return 0;
}
