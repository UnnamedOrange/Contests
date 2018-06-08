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
	INT_PUT a = 0; bool positive = true;
	char ch = getchar();
	while (!(ch == '-' || std::isdigit(ch))) ch = getchar();
	if (ch == '-') { positive = false; ch = getchar(); }
	while (std::isdigit(ch)) { a = a * 10 - (ch - '0'); ch = getchar(); }
	return positive ? -a : a;
}
void printOut(INT_PUT x)
{
	char buffer[20]; int length = 0;
	if (x < 0) putchar('-'); else x = -x;
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
	putchar('\n');
}

double EPS = 1e-10;
const int maxn = int(1e5) + 5;
int n, m;
int x[maxn];
int y[maxn];
int qx, qy;

int dcmp(double x)
{
	if (std::abs(x) <= EPS) return 0;
	return x < 0 ? -1 : 1;
}

bool check(int s)
{
	if (!s) return true;
	double stdY = (double)y[s] * (x[s] - qx) / x[s];
	return dcmp(qy - stdY) >= 0;
}

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++) x[i] = readIn();
	for (int i = 1; i <= n; i++) y[i] = readIn();
	std::sort(x + 1, x + 1 + n);
	std::sort(y + 1, y + 1 + n);
	m = readIn();
	while (m--)
	{
		qx = readIn();
		qy = readIn();

		int l = 0, r = n + 1;
		while (r - l > 1)
		{
			int mid = l + ((r - l) >> 1);
			if (check(mid))
				l = mid;
			else
				r = mid;
		}
		printOut(l);
	}
}

int main()
{
#ifndef LOCAL
	freopen("geometry.in", "r", stdin);
	freopen("geometry.out", "w", stdout);
#endif
	run();
	return 0;
}