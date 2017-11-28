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
typedef int INT;
using std::cin;
using std::cout;
using std::endl;
inline INT readIn()
{
	INT a = 0;
	bool minus = false;
	char ch = getchar();
	while (!(ch == '-' || (ch >= '0' && ch <= '9'))) ch = getchar();
	if (ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		a = a * 10 + (ch - '0');
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}
inline void printOut(INT x)
{
	char buffer[20];
	INT length = 0;
	bool minus = x < 0;
	if (minus) x = -x;
	do
	{
		buffer[length++] = x % 10 + '0';
		x /= 10;
	} while (x);
	if (minus) buffer[length++] = '-';
	do
	{
		putchar(buffer[--length]);
	} while (length);
	putchar('\n');
}

const INT maxn = INT(1e7) + 5;
INT q;
INT l, r;

bool isPrime[maxn];
INT isLike[maxn];
INT prime[665000];
void init()
{
	const INT maxN = INT(1e7);
	std::fill(isPrime, isPrime + 1 + maxN, true);
	isPrime[0] = isPrime[1] = false;
	for (int i = 2; i <= maxN; i++)
	{
		if (isPrime[i]) prime[++prime[0]] = i;
		for (int j = 1; j <= prime[0]; j++)
		{
			INT t = i * prime[j];
			if (t > maxN) break;
			if (isPrime[i]) isLike[t] = true;
			isPrime[t] = false;
			if (!(i % prime[j])) continue;
		}
	}
	for (int i = 2; i <= maxN; i++)
		isLike[i] |= isPrime[i];
	for (int i = 1; i <= maxN; i++)
		isLike[i] += isLike[i - 1];
}

void run()
{
	init();

	q = readIn();
	while (q--)
	{
		l = readIn();
		r = readIn();
		printOut(isLike[r] - isLike[l - 1]);
	}
}

int main()
{
#ifndef LOCAL
	freopen("prime.in", "r", stdin);
	freopen("prime.out", "w", stdout);
#endif
	run();
	return 0;
}
