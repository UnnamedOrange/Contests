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
	putchar(' ');
}

const char no[] = "NO", yes[] = "YES";
const int maxn = int(1e5) + 5;
LL n, c, d, task;
struct Enemy
{
	int a, b;
	void read() { a = readIn(); b = readIn(); }
} enemies[maxn];
int nUpper;
int upper[maxn];
int nLower;
int lower[maxn];
bool comp1(const int& a, const int& b)
{
	if (enemies[a].a != enemies[b].a)
		return enemies[a].a < enemies[b].a;
	return enemies[a].b < enemies[b].b;
}
bool comp2(const int& a, const int& b)
{
	if (enemies[a].b != enemies[b].b)
		return enemies[a].b > enemies[b].b;
	return enemies[a].a > enemies[b].a;
}

void run()
{
	n = readIn();
	c = readIn();
	c -= readIn() + 1;
	task = readIn();
	if (c < 0)
	{
		puts("NO");
		return;
	}

	for (int i = 1; i <= n; i++)
		enemies[i].read();
	for (int i = 1; i <= n; i++)
	{
		const Enemy& e = enemies[i];
		if (e.a <= e.b) upper[++nUpper] = i;
		else lower[++nLower] = i;
	}
	std::sort(upper + 1, upper + 1 + nUpper, comp1);
	std::sort(lower + 1, lower + 1 + nLower, comp2);

	for (int i = 1; i <= nUpper; i++)
	{
		const Enemy& e = enemies[upper[i]];
		if (c < e.a)
		{
			puts(no);
			return;
		}
		c += e.b - e.a;
	}
	for (int i = 1; i <= nLower; i++)
	{
		const Enemy& e = enemies[lower[i]];
		if (c < e.a)
		{
			puts(no);
			return;
		}
		c -= e.a - e.b;
	}
	puts(yes);
	for (int i = 1; i <= nUpper; i++)
		printOut(upper[i]);
	for (int i = 1; i <= nLower; i++)
		printOut(lower[i]);
}

int main()
{
#ifndef LOCAL
	freopen("resist.in", "r", stdin);
	freopen("resist.out", "w", stdout);
#endif
	run();
	return 0;
}