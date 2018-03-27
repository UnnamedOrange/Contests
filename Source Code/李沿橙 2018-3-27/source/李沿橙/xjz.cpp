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
	int positive = true;
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

const int maxn = int(1e6) + 5;
int T, alphabet;
int n, m;
int s[maxn];
int t[maxn];

const ULL base = 1313131;
ULL power[maxn];
ULL hashT;
int buf[maxn];
int pres[maxn];
int pret[maxn];
void init()
{
	memset(buf, 0, sizeof(int) * (alphabet + 1));
	for (int i = 1; i <= n; i++)
	{
		pres[i] = buf[s[i]];
		buf[s[i]] = i;
	}
	memset(buf, 0, sizeof(int) * (alphabet + 1));
	for (int i = 1; i <= m; i++)
	{
		pret[i] = buf[t[i]];
		buf[t[i]] = i;
	}
	hashT = 0;
	for (int i = 1; i <= m; i++)
		if (pret[i])
			hashT += power[m - pret[i]] * (i - pret[i]);
}

int next[maxn];
int ans[maxn];

void run()
{
	power[0] = 1;
	for (int i = 1; i <= int(1e6); i++)
		power[i] = power[i - 1] * base;

	T = readIn();
	alphabet = readIn();
	while (T--)
	{
		n = readIn();
		m = readIn();
		for (int i = 1; i <= n; i++)
			s[i] = readIn();
		for (int i = 1; i <= m; i++)
			t[i] = readIn();
		init();

		memset(next, 0, sizeof(int) * (n + 1));
		ULL hashS = 0;
		for (int i = 1; i <= m; i++)
			if (pres[i])
			{
				next[pres[i]] = i;
				hashS += power[m - pres[i]] * (i - pres[i]);
			}
		ans[0] = 0;
		if (hashS == hashT) ans[++ans[0]] = 1;

		for (int i = m + 1; i <= n; i++)
		{
			if (next[i - m])
				hashS -= power[m - 1] * (next[i - m] - (i - m));
			hashS *= base;
			if (i - m + 1 <= pres[i] && pres[i] <= i)
			{
				next[pres[i]] = i;
				hashS += power[i - pres[i]] * (i - pres[i]);
			}
			if (hashS == hashT)
				ans[++ans[0]] = i - m + 1;
		}
		printOut(ans[0]);
		putchar('\n');
		for (int i = 1; i <= ans[0]; i++)
		{
			printOut(ans[i]);
			putchar(' ');
		}
		putchar('\n');
	}
}

int main()
{
#ifndef LOCAL
	freopen("xjz.in", "r", stdin);
	freopen("xjz.out", "w", stdout);
#endif
	run();
	return 0;
}