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
int maxa, maxb;

#define RunInstance(x) delete new x
struct brute
{
	brute()
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
	int inBlock[maxn];
	int lBegin[maxn];
	int rEnd[maxn];
	int sqrtN;
	int N;
	void initBlocks()
	{
		sqrtN = std::sqrt(maxa);
		N = maxa / sqrtN + 1;
		for (int i = 0; i <= maxa; i++)
		{
			int t = inBlock[i] = i / sqrtN;
			if (!lBegin[t]) lBegin[t] = i;
			rEnd[t] = i;
		}
	}

	static const int maxN = 455;
	std::deque<int> mono[maxN];
	int tag[maxN];
	LL val[maxn];
	LL ans;

	void maintain(int v)
	{
		int block = inBlock[v];
		for (int i = 0; i < block; i++)
		{
			tag[i]++;
			std::deque<int>& q = mono[i];
			while (q.size() >= 2 && val[q.front()] + (LL)q.front() * tag[i] <= val[q[1]] + (LL)q[1] * tag[i])
				q.pop_front();
			if (q.size())
				ans = std::max(ans, val[q.front()] + (LL)q.front() * tag[i]);
		}
		for (int i = lBegin[block], to = rEnd[block]; i <= to; i++)
			val[i] += (LL)i * tag[block];
		tag[block] = 0;
		for (int i = lBegin[block]; i <= v; i++)
			val[i] += i;

		std::deque<int>& q = mono[block];
		q.clear();
		for (int i = lBegin[block], to = rEnd[block]; i <= to; i++)
		{
			while (q.size() >= 2 &&
				(double)(val[q[q.size() - 2]] - val[q.back()]) / (q.back() - q[q.size() - 2]) > (double)(val[q.back()] - val[i]) / (i - q.back()))
				q.pop_back();
			q.push_back(i);
			ans = std::max(ans, val[i]);
		}
	}

	work() : lBegin(), tag(), val(), ans()
	{
		initBlocks();
		std::sort(people + 1, people + 1 + n);

		int cnt = 1;
		for (int c = 1, to = maxb + 1; c <= to; c++)
		{
			while (cnt <= n && c > people[cnt].b)
			{
				int a = people[cnt].a;
				cnt++;
				maintain(a);
			}
			printOut(ans + (LL)(n - cnt + 1) * c * w);
		}
	}
};

void run()
{
	n = readIn();
	w = readIn();
	for (int i = 1; i <= n; i++)
	{
		people[i].read();
		maxa = std::max(maxa, people[i].a);
		maxb = std::max(maxb, people[i].b);
	}

	if ((LL)n * maxb <= LL(1e8))
		RunInstance(brute);
	else
		RunInstance(work);
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