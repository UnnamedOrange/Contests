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
	while (!(std::isdigit(ch) || ch == '-')) ch = getchar();
	if (ch == '-')
	{
		positive = false;
		ch = getchar();
	}
	while (std::isdigit(ch))
	{
		(a *= 10) -= ch - '0';
		ch = getchar();
	}
	return positive ? -a : a;
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

const int maxn = int(2e5) + 5;
int n;
char str[maxn];
LL val[maxn];

struct SuffixArray
{
	int temp[maxn];
	int x[maxn];
	int y[maxn];
	int buf_size;
	int buf[maxn];

	int SA[maxn];
	int Rank[maxn];
	int Height[maxn];
	void GetSA()
	{
		buf_size = 128;
		int* rank = x;
		int* SA_second = y;
		for (int i = 0; i < n; i++)
			rank[i] = str[i];

		for (int i = 0; i < buf_size; i++) buf[i] = 0;
		for (int i = 0; i < n; i++) buf[rank[i]]++;
		for (int i = 1; i < buf_size; i++) buf[i] += buf[i - 1];
		for (int i = n - 1; ~i; i--) SA[--buf[rank[i]]] = i;

		for (int k = 1; k <= n; k <<= 1)
		{
			int t = 0;
			for (int i = n - k; i < n; i++)
				SA_second[t++] = i;
			for (int i = 0; i < n; i++)
				if (SA[i] >= k)
					SA_second[t++] = SA[i] - k;

			for (int i = 0; i < buf_size; i++) buf[i] = 0;
			for (int i = 0; i < n; i++) buf[rank[SA_second[i]]]++;
			for (int i = 1; i < buf_size; i++) buf[i] += buf[i - 1];
			for (int i = n - 1; ~i; i--)
				SA[--buf[rank[SA_second[i]]]] = SA_second[i];

			int* oldRank = rank;
			std::swap(rank, SA_second);
			rank[SA[0]] = 0;
			t = 1;
			for (int i = 1; i < n; i++)
				rank[SA[i]] = (oldRank[SA[i - 1]] == oldRank[SA[i]] &&
					SA[i - 1] + k < n && SA[i] + k < n &&
					oldRank[SA[i - 1] + k] == oldRank[SA[i] + k]) ? t - 1 : t++;
			if (t >= n)
				break;
			buf_size = t;
		}
	}
	void GetHeight()
	{
		for (int i = 0; i < n; i++)
			Rank[SA[i]] = i;
		int same = 0;
		for (int i = 0; i < n; i++)
		{
			if (Rank[i])
			{
				if (same) same--;
				int pre = SA[Rank[i] - 1];
				while (i + same < n && pre + same < n &&
					str[i + same] == str[pre + same])
					same++;
			}
			else
				same = 0;
			Height[Rank[i]] = same;
		}
	}
} suffix_array;

int* sa;
int* height;

#define RunInstance(x) delete new x
struct brute
{
	std::vector<std::pair<int, int> > ans;

	brute()
	{
		LL all = n - sa[0];
		for (int i = 1; i < n; i++)
			all += n - sa[i] - height[i];

		LL rank = 0;
		for (int i = 0; i < n; i++)
		{
			for (int j = height[i]; j < n - sa[i]; j++)
			{
				rank++;
				int k = i;
				do
				{
					if (val[sa[k] + j + 1] - val[sa[k]] == all - rank + 1)
						ans.push_back(std::make_pair(sa[k] + 1, sa[k] + j + 1));
					k++;
				} while (k < n && height[k] > j);
			}
		}
		std::sort(ans.begin(), ans.end());
		printOut(ans.size());
		putchar('\n');
		for (int i = 0; i < ans.size(); i++)
		{
			printOut(ans[i].first);
			putchar(' ');
			printOut(ans[i].second);
			putchar('\n');
		}
	}
};

void run()
{
	scanf("%s", str);
	n = strlen(str);
	suffix_array.GetSA();
	suffix_array.GetHeight();
	sa = suffix_array.SA;
	height = suffix_array.Height;

	for (int i = 1; i <= n; i++)
		val[i] = val[i - 1] + readIn();

	if (n <= 1000)
		RunInstance(brute);
}

int main()
{
#ifndef LOCAL
	freopen("platform.in", "r", stdin);
	freopen("platform.out", "w", stdout);
#endif
	run();
	return 0;
}