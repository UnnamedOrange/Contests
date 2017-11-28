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
typedef long long INT;
using std::cin;
using std::cout;
using std::endl;
inline INT readIn()
{
	INT a = 0;
	bool minus = false;
	char ch = getchar();
	while (!(ch == '-' || (ch >= '0' && ch <= '9'))) ch = getchar();
	if (ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		a = a * 10 + (ch - '0');
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}
inline void printOut(INT x)
{
	char buffer[15];
	INT length = 0;
	bool minus = x < 0;
	if (minus) x = -x;
	do
	{
		buffer[length++] = x % 10 + '0';
		x /= 10;
	}
	while (x);
	if (minus) buffer[length++] = '-';
	do
	{
		putchar(buffer[--length]);
	}
	while (length);
	putchar('\n');
}

const INT mod = INT(1e9) + 7;
const INT maxn = 205;
INT n, m;
INT a[maxn];

#define RunInstance(x) delete new x
struct brute
{
	typedef std::pair<INT, INT> Group;
	std::vector<Group> groups;

	INT ans;
	void search(INT stage, INT sum)
	{
		if (sum > m) return;
		if (stage > n)
		{
			ans++;
			return;
		}
		groups.push_back(Group(a[stage], a[stage]));
		search(stage + 1, sum);
		groups.pop_back();
		for (int i = 0; i < groups.size(); i++)
		{
			Group t = groups[i];
			//groups[i].first = std::min(groups[i].first, a[stage]);
			groups[i].second = std::max(groups[i].second, a[stage]);
			search(stage + 1, sum - (t.second - t.first) + (groups[i].second - groups[i].first));
			groups[i] = t;
		}
	}

	brute() : ans()
	{
		search(1, 0);
		printOut(ans);
	}
};
struct work
{
	INT f[2][maxn][1005];

	static inline void pe(INT& x, INT y)
	{
		x = (x + y) % mod;
	}

	work() : f()
	{
		f[0][0][0] = 1;
		for(int i = 1; i <= n; i++)
		{
			INT val = a[i] - a[i - 1];

			INT cnt = i & 1;
			INT pre = !cnt;
			memset(f[cnt], 0, sizeof(cnt));
			for(int j = 0; j < i; j++)
			{
				INT temp = val * j;
				for(int k = 0; k <= m; k++)
				{
					if(temp + k > m) continue;
					INT v = temp + k;

					pe(f[cnt][j + 1][v], f[pre][j][k]);
					pe(f[cnt][j][v], f[pre][j][k]);

					if(j)
						pe(f[cnt][j][v], f[pre][j][k] * j);

					if(j)
						pe(f[cnt][j - 1][v], f[pre][j][k] * j);
				}
			}
		}

		INT ans = 0;
		for(int i = 0; i <= m; i++)
		{
			pe(ans, f[n & 1][0][i]);
		}
		printOut(ans);
	}
};

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= n; i++)
	{
		a[i] = readIn();
	}
	std::sort(a + 1, a + 1 + n);

//	if (n <= 10)
//		RunInstance(brute);
//	else
	RunInstance(work);
}

int main()
{
#ifndef JUDGE
	freopen("group.in", "r", stdin);
	freopen("group.out", "w", stdout);
#endif
	run();
	return 0;
}
