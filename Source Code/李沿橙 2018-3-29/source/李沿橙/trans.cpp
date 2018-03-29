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
	int a = 0;
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
}

const int mod = int(1e9) + 7;
const int maxn = int(2e5) + 5;
int n;
int a[maxn];

int idx[maxn];
bool comp(const int& x, const int& y)
{
	return a[x] < a[y];
}
int left[maxn];
int right[maxn];

LL csum[maxn];

LL ans;

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
		a[i] = readIn();
	for (int i = 1; i <= n; i++)
		csum[i] = i;
	for (int i = 2; i <= n; i++)
		csum[i] += csum[i - 1];
	for (int i = 2; i <= n; i++)
		csum[i] += csum[i - 1];

	for (int i = 1; i <= n; i++)
		idx[i] = i;
	std::sort(idx + 1, idx + 1 + n, comp);

	for (int i = 1; i < n; i++)
	{
		left[i + 1] = i;
		right[i] = i + 1;
	}
	for (int i = 1; i < n; i++)
	{
		int lBound, rBound;
		if (left[idx[i]])
			lBound = left[idx[i]] + 1;
		else
			lBound = 1;
		if (right[idx[i]])
			rBound = right[idx[i]] - 1;
		else
			rBound = n;

		if (left[idx[i]]) right[left[idx[i]]] = right[idx[i]];
		if (right[idx[i]]) left[right[idx[i]]] = left[idx[i]];

		int pos = idx[i];
		int times = pos - lBound + 1;
		int len = rBound - pos + 1;
		int maxVal = std::min(times, len);
		int interval = rBound - lBound + 1;
	}

}

int main()
{
#ifndef LOCAL
	freopen("trans.in", "r", stdin);
	freopen("trans.out", "w", stdout);
#endif
	run();
	return 0;
}