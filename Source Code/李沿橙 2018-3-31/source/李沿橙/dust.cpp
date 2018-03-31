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
#define rint register int
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
}

const int maxn = 2505;
int n;
int a, b, c;

#define RunInstance(x) delete new x
struct brute
{
	static const int maxN = 505;
	long double rect[maxN][maxN];

	void a_powerful_function_named_Gauss()
	{
		for (rint i = 0; i < n; i++)
		{
			int r = i;
			for (rint j = i + 1; j < n; j++)
				if (std::abs(rect[j][i]) > std::abs(rect[r][i]))
					r = j;
			if (r != i)
				for (rint j = 0; j <= n; j++)
					std::swap(rect[i][j], rect[r][j]);

			for (rint j = i + 1; j < n; j++)
				for (rint k = n; k >= i; k--)
					rect[j][k] -= rect[i][k] * rect[j][i] / rect[i][i];
		}
		for (rint i = n - 2; ~i; i--)
		{
			long double num = rect[i][n] /= rect[i][i];
			for (rint j = 0; j < i; j++)
				rect[j][n] -= num * rect[j][i];
		}
	}

	brute() : rect()
	{
		LL sum = n + b;
		rect[0][0] = b;
		int pre = b;
		for (rint i = 1; i < n; i++)
			sum += pre = rect[i][0] = (a * pre + b) % c;
		for (rint i = 0; i < n; i++)
			(++rect[i][0]) /= sum;
		for (rint i = 1; i < n; i++)
		{
			sum = n;
			for (rint j = 0; j < n; j++)
				sum += pre = rect[j][i] = (a * pre + b) % c;
			for (rint j = 0; j < n; j++)
				(++rect[j][i]) /= sum;
		}
		for (int i = 0; i < n; i++)
			rect[i][i]--;

		for (int i = 0; i < n; i++)
			rect[n][i] = 1;
		rect[n][n + 1] = 1;
		n++;
		a_powerful_function_named_Gauss();

		for (int i = 0; i < n - 1; i++)
			printf("%.20Lf ", rect[i][n]);
	}
};
struct work
{
	long double rect[maxn][maxn];
	long double x[maxn];
	long double y[maxn];

	work() : rect(), x(), y()
	{
		LL sum = n + b;
		rect[0][0] = b;
		int pre = b;
		for (rint i = 1; i < n; i++)
			sum += pre = rect[i][0] = (a * pre + b) % c;
		for (rint i = 0; i < n; i++)
			(++rect[i][0]) /= sum;
		for (rint i = 1; i < n; i++)
		{
			sum = n;
			for (rint j = 0; j < n; j++)
				sum += pre = rect[j][i] = (a * pre + b) % c;
			for (rint j = 0; j < n; j++)
				(++rect[j][i]) /= sum;
		}

		long double* d = x;
		long double* p = y;
		d[0] = 1;
		while (std::abs(d[0] - p[0]) > 1e-15)
		{
			std::swap(d, p);
			for (int i = 0; i < n; i++)
			{
				d[i] = 0;
				for (int j = 0; j < n; j++)
					d[i] += p[j] * rect[i][j];
			}
		}
		for (int i = 0; i < n; i++)
			printf("%.20Lf ", d[i]);
	}
};

void run()
{
	n = readIn();
	a = readIn();
	b = readIn();
	c = readIn();

	if (n <= 500)
		RunInstance(brute);
	else
		RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("dust.in", "r", stdin);
	freopen("dust.out", "w", stdout);
#endif
	run();
	return 0;
}