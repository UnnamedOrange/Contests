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

const int maxn = int(1e5) + 5;
int n;
int str[maxn * 2];
int w[maxn], d[maxn];
int table[3][3] =
{
	{ 0, 1, -1 },
	{ -1, 0, 1 },
	{ 1, -1, 0 }
};

#define RunInstance(x) delete new x
struct brute1
{
	struct Trie
	{
		struct Node
		{
			int son[3];
			Node() : son() {}
		};
		std::vector<Node> nodes;
		Trie() : nodes(1) {}
		void insert(int st)
		{
			int cnt = 0;
			for (int i = 0; i < n; i++)
			{
				if (!nodes[cnt].son[str[st + i]])
				{
					nodes[cnt].son[str[st + i]] = nodes.size();
					nodes.push_back(Node());
				}
				cnt = nodes[cnt].son[str[st + i]];
			}
		}
		LL DP(int node = 0, int depth = 1)
		{
			if (depth == n + 1) return 0;
			LL ret = 0;
			LL temp[3] = {};
			for (int i = 0; i < 3; i++)
				if (nodes[node].son[i])
					temp[i] = DP(nodes[node].son[i], depth + 1);

			for (int i = 0; i < 3; i++)
			{
				LL min = LLONG_MAX;
				for (int j = 0; j < 3; j++)
				{
					if (nodes[node].son[j])
					{
						int accum = 0;
						switch (table[i][j])
						{
						case 1: accum = w[depth]; break;
						case 0: accum = d[depth]; break;
						case -1: accum = 0; break;
						}
						min = std::min(min, temp[j] + accum);
					}
				}
				ret = std::max(ret, min);
			}
			return ret;
		}
	} trie;

	brute1()
	{
		for (int i = 1; i <= n; i++)
			trie.insert(i);
		printOut(trie.DP());
	}
};

bool checkSame()
{
	std::vector<int> temp(str + 1, str + 1 + n);
	return std::unique(temp.begin(), temp.end()) - temp.begin() == 1;
}
void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
	{
		char ch = getchar();
		while (!std::isalpha(ch)) ch = getchar();
		if (ch == 'r') str[i] = 0;
		else if (ch == 's') str[i] = 1;
		else if (ch == 'p') str[i] = 2;
	}
	std::memcpy(str + n + 1, str + 1, sizeof(str[0]) * n);
	for (int i = 1; i <= n; i++)
	{
		w[i] = readIn();
		d[i] = readIn();
	}
	if (checkSame())
	{
		LL ans = 0;
		for (int i = 1; i <= n; i++)
			ans += w[i];
		printOut(ans);
		return;
	}

	if (n <= 1000)
		RunInstance(brute1);
}

int main()
{
#ifndef LOCAL
	freopen("dexterity.in", "r", stdin);
	freopen("dexterity.out", "w", stdout);
#endif
	run();
	return 0;
}