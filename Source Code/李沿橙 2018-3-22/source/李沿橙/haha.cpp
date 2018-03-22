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
	do buffer[length++] = -(x % 10) + '0';
	while (x /= 10);
	do putchar(buffer[--length]);
	while (length);
}

const int maxn = 405;
int n;
LL v[maxn];
LL w[maxn];

#define RunInstance(x) delete new x
struct brute
{
	std::map<std::vector<int>, LL> f;
	LL search(std::vector<int> seq)
	{
		if (f.count(seq)) return f[seq];
		LL& ans = f[seq];
		ans = 0;
		static int buf[maxn];
		for (int i = 0; i < seq.size(); i++)
		{
			if (i) buf[i - 1] = seq[i - 1];
			for (int j = i; j < seq.size(); j++)
			{
				if (j - i)
					if (std::abs(seq[j] - seq[j - 1]) != 1)
						break;
				if (j - i >= 2)
					if (!(2 * seq[j - 1] - seq[j] - seq[j - 2] >= 0))
						break;

				for (int k = j + 1, s = i; k < seq.size(); k++, s++)
					buf[s] = seq[k];
				ans = std::max(ans, v[j - i + 1] + search(std::vector<int>(buf, buf + (seq.size() - (j - i + 1)))));
			}
		}
		return ans;
	}
	brute()
	{
		printOut(search(std::vector<int>(w + 1, w + 1 + n)));
	}
};
struct cheat
{
	LL f[maxn][maxn];
	LL DP(int l, int r)
	{
		LL& ans = f[l][r];
		if (~ans) return ans;
		ans = 0;
		for (int i = l; i <= r; i++)
		{
			for (int j = i; j <= r; j++)
			{
				if (j - i)
					if (std::abs(w[j] - w[j - 1]) != 1)
						break;
				if (j - i >= 2)
					if (!(2 * w[j - 1] - w[j] - w[j - 2] >= 0))
						break;
				LL t = 0;
				if (i > l) t += DP(l, i - 1);
				if (j < r) t += DP(j + 1, r);
				t += v[j - i + 1];
				ans = std::max(ans, t);
			}
		}
		return ans;
	}
	cheat()
	{
		memset(f, -1, sizeof(f));
		printOut(DP(1, n));
	}
};

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
		v[i] = readIn();
	for (int i = 1; i <= n; i++)
		w[i] = readIn();

	if (n <= 10)
		RunInstance(brute);
	else
		RunInstance(cheat);
}

int main()
{
#ifndef LOCAL
	freopen("haha.in", "r", stdin);
	freopen("haha.out", "w", stdout);
#endif
	run();
	return 0;
}