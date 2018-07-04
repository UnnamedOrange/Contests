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
	putchar('\n');
}

const int maxn = 1005;
int n, m;
std::vector<int> seq[maxn];
int target[maxn];

#define RunInstance(x) delete new x
struct brute
{
	int buffer[10000000];
	void make(int depth, int cnt)
	{
		if (!depth)
		{
			buffer[++buffer[0]] = cnt;
			return;
		}
		for (int i = 0; i < seq[cnt].size(); i++)
			make(depth - 1, seq[cnt][i]);
	}

	brute()
	{
		int ans = 1;
		for (; ans <= 5; ans++)
		{
			buffer[0] = 0;
			make(ans - 1, 1);
			bool bOk = false;

			for (int i = 1; i <= buffer[0]; i++)
			{
				bool bFound = true;
				for (int j = 1; j <= m; j++)
				{
					if (i + j - 1 > buffer[0])
					{
						bFound = false;
						break;
					}
					if (buffer[i + j - 1] != target[j])
					{
						bFound = false;
						break;
					}
				}
				if (bFound)
				{
					bOk = true;
					break;
				}
			}
			if (bOk)
				break;
		}
		printOut(ans > 5 ? -1 : ans);
	}
};
struct work
{
	int g1[maxn];
	int g2[maxn][maxn];

	void GetG1()
	{
		memset(g1, 0, sizeof(g1));
		std::vector<int> q;
		g1[1] = 1;
		q.push_back(1);
		int head = 0;
		while (head < q.size())
		{
			int from = q[head++];
			std::vector<int>& s = seq[from];
			for (int i = 0; i < s.size(); i++)
			{
				if (!g1[s[i]])
				{
					g1[s[i]] = g1[from] + 1;
					q.push_back(s[i]);
				}
			}
		}
	}
	void GetG2()
	{
		memset(g2, 0, sizeof(g2));
		std::vector<std::pair<int, int> > q;
		{
			std::vector<int>& s = seq[1];
			for (int i = 1; i < s.size(); i++)
			{
				if (!g2[s[i - 1]][s[i]])
				{
					g2[s[i - 1]][s[i]] = 2;
					q.push_back(std::make_pair(s[i - 1], s[i]));
				}
			}
		}
		int head = 0;
		while (head < q.size())
		{
			std::pair<int, int> from = q[head++];

			std::vector<int>& s1 = seq[from.first];
			for (int i = 1; i < s1.size(); i++)
			{
				if (!g2[s1[i - 1]][s1[i]])
				{
					g2[s1[i - 1]][s1[i]] = g2[from.first][from.second] + 1;
					q.push_back(std::make_pair(s1[i - 1], s1[i]));
				}
			}
			std::vector<int>& s2 = seq[from.second];
			for (int i = 1; i < s2.size(); i++)
			{
				if (!g2[s2[i - 1]][s2[i]])
				{
					g2[s2[i - 1]][s2[i]] = g2[from.first][from.second] + 1;
					q.push_back(std::make_pair(s2[i - 1], s2[i]));
				}
			}
			if (!g2[s1.back()][s2.front()])
			{
				g2[s1.back()][s2.front()] = g2[from.first][from.second] + 1;
				q.push_back(std::make_pair(s1.back(), s2.front()));
			}
		}
	}

	int f[maxn];
	std::bitset<1002> left[11][maxn];
	std::bitset<1002> right[11][maxn];
	void initFailureS()
	{
		f[0] = f[1] = 0;
		int pre = 0;
		for (int i = 1; i < m; i++)
		{
			while (pre && target[pre + 1] != target[i + 1]) pre = f[pre];
			if (target[pre + 1] == target[i + 1]) pre++;
			f[i + 1] = pre;
		}
	}

	int temp[maxn];
	int cnt[maxn];
	void GetLeft(int idx, int depth)
	{
		if (depth > 10)
			return;
		if (!depth)
		{
			temp[0] = cnt[0] = 0;
			cnt[++cnt[0]] = idx;
			temp[++temp[0]] = idx;
		}
		else
		{
			temp[0] = 0;
			for (int i = 1; i <= cnt[0] && temp[0] < m; i++)
			{
				const std::vector<int> s = seq[cnt[i]];
				for (int j = s.size() - 1; ~j && temp[0] < m; j--)
					temp[++temp[0]] = s[j];
			}
			cnt[0] = temp[0];
			for (int i = 1; i <= cnt[0]; i++)
				cnt[i] = temp[i];

			std::reverse(temp + 1, temp + 1 + temp[0]);
		}

		int match = 0;
		for (int i = 1; i <= temp[0]; i++)
		{
			while (match && temp[i] != target[match + 1])
				match = f[match];
			if (temp[i] == target[match + 1]) match++;
		}
		while (match)
		{
			if (match != m)
				left[depth][idx].set(match);
			match = f[match];
		}
		GetLeft(idx, depth + 1);
	}
	void GetRight(int idx, int depth)
	{
		if (depth > 10)
			return;
		if (!depth)
		{
			temp[0] = cnt[0] = 0;
			cnt[++cnt[0]] = idx;
			temp[++temp[0]] = idx;
		}
		else
		{
			temp[0] = 0;
			for (int i = 1; i <= cnt[0] && temp[0] < m; i++)
			{
				const std::vector<int> s = seq[cnt[i]];
				for (int j = 0; j < s.size() && temp[0] < m; j++)
					temp[++temp[0]] = s[j];
			}
			cnt[0] = temp[0];
			for (int i = 1; i <= cnt[0]; i++)
				cnt[i] = temp[i];

			std::reverse(temp + 1, temp + 1 + temp[0]);
		}

		int match = 0;
		for (int i = 1; i <= temp[0]; i++)
		{
			while (match && temp[i] != target[match + 1])
				match = f[match];
			if (temp[i] == target[match + 1]) match++;
		}
		while (match)
		{
			if (match != m)
				right[depth][idx].set(m - match);
			match = f[match];
		}
		GetRight(idx, depth + 1);
	}

	int tempA[maxn];
	int tempB[maxn];
	int tempAll[maxn * 2];
	void GetCut(int idx, int pos)
	{
		tempA[0] = tempB[0] = 0;
		const std::vector<int>& s = seq[idx];
		for (int i = pos - 1; ~i; i--)
			tempA[++tempA[0]] = s[i];
		for (int i = pos; i < s.size(); i++)
			tempB[++tempB[0]] = s[i];

		int depth = 1;
		for (; depth <= 10; depth++)
		{
			tempAll[0] = 0;
			for (int i = tempA[0]; i; i--)
				tempAll[++tempAll[0]] = tempA[i];
			for (int i = 1; i <= tempB[0]; i++)
				tempAll[++tempAll[0]] = tempB[i];

			int match = 0;
			for (int i = 1; i <= tempAll[0]; i++)
			{
				while (match && tempAll[i] != target[match + 1])
					match = f[match];
				if (tempAll[i] == target[match + 1]) match++;
				if (match == m)
				{
					if (!~ans || ans > g1[idx] + depth)
						ans = g1[idx] + depth;
					return;
				}
			}

			temp[0] = 0;
			for (int i = 1; i <= tempA[0] && temp[0] < m; i++)
			{
				const std::vector<int> s = seq[tempA[i]];
				for (int j = s.size() - 1; ~j && temp[0] < m; j--)
					temp[++temp[0]] = s[j];
			}
			tempA[0] = temp[0];
			for (int i = 1; i <= tempA[0]; i++)
				tempA[i] = temp[i];

			temp[0] = 0;
			for (int i = 1; i <= tempB[0] && temp[0] < m; i++)
			{
				const std::vector<int> s = seq[tempB[i]];
				for (int j = 0; j < s.size() && temp[0] < m; j++)
					temp[++temp[0]] = s[j];
			}
			tempB[0] = temp[0];
			for (int i = 1; i <= tempB[0]; i++)
				tempB[i] = temp[i];
		}
	}

	int ans;

	work() : ans(-1)
	{
		GetG1();
		if (m == 1)
		{
			printOut(g1[target[1]] ? g1[target[1]] : -1);
			return;
		}
		GetG2();
		initFailureS();
		for (int i = 1; i <= n; i++)
			GetLeft(i, 0);
		for (int i = 1; i <= n; i++)
			for (int j = 1; j < seq[i].size(); j++) if (g1[i])
				GetCut(i, j);
		std::reverse(target + 1, target + 1 + m);
		initFailureS();
		for (int i = 1; i <= n; i++)
			GetRight(i, 0);

		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++) if (g2[i][j])
				for (int k = 0; k <= 10; k++)
					if ((left[k][i] & right[k][j]).any())
						if (!~ans || ans > g2[i][j] + k)
							ans = g2[i][j] + k;

		printOut(ans);
	}
};

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= n; i++)
	{
		seq[i].resize(readIn());
		for (int j = 0; j < seq[i].size(); j++)
			seq[i][j] = readIn();
	}
	for (int i = 1; i <= m; i++)
		target[i] = readIn();

	RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("cell.in", "r", stdin);
	freopen("cell.out", "w", stdout);
#endif
	run();
	return 0;
}