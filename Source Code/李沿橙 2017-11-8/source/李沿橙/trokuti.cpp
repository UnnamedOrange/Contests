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
INT readIn()
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
void printOut(INT x)
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

const INT mod = INT(1e9) + 7;
const INT maxn = INT(3e5) + 5;
const INT inv6 = 166666668;
INT n;
struct REAL
{
	INT up, down;
	REAL() : up(), down() {}
	REAL(INT up, INT down) : up(up), down(down) {}
	bool operator< (const REAL& b) const
	{
		const REAL& a = *this;
		if (!a.down) return false;
		if (!b.down) return true;
		return a.up * b.down < b.up * a.down;
	}
};

std::map<REAL, INT> kmap;

void run()
{
	n = readIn();

	for (int i = 1; i <= n; i++)
	{
		INT a = readIn();
		INT b = readIn();
		INT c = readIn();
		kmap[REAL(-a, b)]++;
	}

	std::vector<INT> k;
	k.reserve(kmap.size());
	for (std::map<REAL, INT>::iterator it = kmap.begin(); it != kmap.end(); it++)
		k.push_back(it->second);

	INT ans = 0;
	if (n <= 500)
	{
		for (int i = 0; i < k.size(); i++)
			for (int j = i + 1; j < k.size(); j++)
				for (int l = j + 1; l < k.size(); l++)
					ans = (ans + k[i] * k[j] * k[l]) % mod;
		printOut(ans);
	}
	else
	{
		INT sum2 = 0;
		for (int i = 0; i < k.size(); i++)
			sum2 = (sum2 + k[i] * (n - k[i])) % mod;

		INT sum3 = sum2 * n % mod;
		for (int i = 0; i < k.size(); i++)
			sum3 = (sum3 - 2 * k[i] * k[i] * (n - k[i])) % mod;

		sum3 = (sum3 + mod) % mod;
		sum3 = sum3 * inv6 % mod;

		printOut(sum3);
	}
}

int main()
{
#ifndef LOCAL
	freopen("trokuti.in", "r", stdin);
	freopen("trokuti.out", "w", stdout);
#endif
	run();
	return 0;
}
