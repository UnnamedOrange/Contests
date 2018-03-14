#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cassert>
#include <climits>
#include <cctype>
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
typedef LL INT_PUT;
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

const int maxn = int(1e5) + 5;
int n, w;
struct People
{
	int a;
	int b;
	void read()
	{
		a = readIn();
		b = readIn();
	}
	bool operator<(const People& y) const
	{
		return b < y.b;
	}
} people[maxn];
int maxb;

#define RunInstance(x) delete new x
struct brute
{
	brute()
	{
		std::sort(people + 1, people + 1 + n);
		int cnt = 1;
		std::vector<int> A;
		for (int c = 1, to = maxb + 1; c <= to; c++)
		{
			while (cnt <= n && c > people[cnt].b)
			{
				A.insert(std::upper_bound(A.begin(), A.end(), people[cnt].a), people[cnt].a);
				cnt++;
			}
			LL ans = 0;
			for (int i = 0, size = A.size(); i < size; i++)
				ans = std::max(ans, (LL)(size - i) * A[i]);
			ans += (LL)(n - cnt + 1) * c * w;
			printOut(ans);
		}
	}
};
struct brute2
{
	brute2()
	{
		std::sort(people + 1, people + 1 + n);
		int cnt = 1;
		std::multiset<int> A;
		for (int c = 1, to = maxb + 1; c <= to; c++)
		{
			while (cnt <= n && c > people[cnt].b)
			{
				A.insert(people[cnt].a);
				cnt++;
			}
			LL ans = 0;
			int j = 0;
			int size = A.size();
			for (std::multiset<int>::iterator it = A.begin(); it != A.end(); it++)
				ans = std::max(ans, (LL)(size - (j++)) * *it);
			ans += (LL)(n - cnt + 1) * c * w;
			printOut(ans);
		}
	}
};
struct work
{
	work()
	{

	}
};

void run()
{
	n = readIn();
	w = readIn();
	for (int i = 1; i <= n; i++)
	{
		people[i].read();
		maxb = std::max(maxb, people[i].b);
	}

	if (n <= 1000 && (LL)n * maxb <= LL(1e8))
		RunInstance(brute);
	else
		RunInstance(brute2);
}

int main()
{
#ifndef LOCAL
	freopen("laofu.in", "r", stdin);
	freopen("laofu.out", "w", stdout);
#endif
	run();
	return 0;
}