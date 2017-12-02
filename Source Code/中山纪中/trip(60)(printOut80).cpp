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
inline void printOut(INT a)
{
	if (!a)
	{
		putchar('0');
		putchar('\n');
		return;
	}
	INT length = 0;
	char buffer[10];
	while (a)
	{
		buffer[length++] = a % 10 + '0';
		a /= 10;
	}
	do
	{
		putchar(buffer[--length]);
	} while (length);
	putchar('\n');
}

const INT maxn = 1000005;
INT n, m;
INT origin[maxn];

INT multi;
INT nextL[21][maxn];
INT nextR[21][maxn];
INT mono[maxn];
//std::vector<std::vector<INT> > nextL;
//std::vector<std::vector<INT> > nextR;

void build()
{
	while (1 << multi < n) multi++;
	//nextL.resize(multi + 1);
	//nextR.resize(multi + 1);
	//for (int i = 0; i <= multi; i++)
	//{
	//	nextL[i].resize(n + 1);
	//	nextR[i].resize(n + 1);
	//}

	mono[0] = 1;
	mono[1] = 1;
	for (int i = 2; i <= n; i++)
	{
		while (mono[0] && origin[mono[mono[0]]] < origin[i])
		{
			nextL[0][mono[mono[0]]] = i;
			mono[0]--;
		}
		mono[++mono[0]] = i;
	}

	mono[0] = 1;
	mono[1] = n;
	for (int i = n - 1; i >= 1; i--)
	{
		while (mono[0] && origin[mono[mono[0]]] < origin[i])
		{
			nextR[0][mono[mono[0]]] = i;
			mono[0]--;
		}
		mono[++mono[0]] = i;
	}

	for (int i = 1; i <= multi; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			nextL[i][j] = nextL[i - 1][nextL[i - 1][j]];
			nextR[i][j] = nextR[i - 1][nextR[i - 1][j]];
		}
	}
}

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= n; i++)
	{
		origin[i] = readIn();
	}

	build();
	while (m--)
	{
		INT l = readIn();
		INT r = readIn();

		INT ans = 1;
		INT pos = l;
		for (INT i = multi; ~i; i--)
		{
			if (!nextL[i][pos] || nextL[i][pos] > r) continue;
			pos = nextL[i][pos];
			ans += 1 << i;
		}
		pos = r;
		for (INT i = multi; ~i; i--)
		{
			if (!nextR[i][pos] || nextR[i][pos] < l) continue;
			pos = nextR[i][pos];
			ans += 1 << i;
		}
		printOut(ans);
	}
}

int main()
{
#ifndef JUDGE
	freopen("trip.in", "r", stdin);
	freopen("trip.out", "w", stdout);
#endif
	run();
	return 0;
}
