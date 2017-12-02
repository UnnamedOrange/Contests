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
using std::cin;
using std::cout;
using std::endl;
typedef long long INT;
inline INT readIn()
{
	INT a = 0;
	bool minus = false;
	char ch = getchar();
	while (!(ch == '-' || ch >= '0' && ch <= '9')) ch = getchar();
	if (ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		a *= 10;
		a += ch;
		a -= '0';
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}

const INT maxn = 5e4 + 5;
INT n, m;
struct NODE
{
	INT l;
	INT r;
	INT c;
	void read()
	{
		l = readIn();
		r = readIn();
		c = readIn();
	}
	bool operator< (const NODE& b) const
	{
		return l < b.l;
	}
} nodes1[maxn], nodes2[maxn];

void work()
{
	INT pos2 = 0;
	std::map<INT, INT> s;
	for (int i = 1; i <= n; i++)
	{
		while (pos2 < m && nodes2[pos2 + 1].l <= nodes1[i].l)
		{
			++pos2;
			s[nodes2[pos2].r] += nodes2[pos2].c;
		}
		std::map<INT, INT>::iterator it;
		while (nodes1[i].c)
		{
			it = s.lower_bound(nodes1[i].r);
			if (it == s.end())
			{
				puts("No");
				return;
			}
			if (it->second > nodes1[i].c)
			{
				it->second -= nodes1[i].c;
				nodes1[i].c = 0;
			}
			else
			{
				nodes1[i].c -= it->second;
				s.erase(it);
			}
		}
	}
	puts("Yes");
}

void run()
{
	INT T = readIn();
	while (T--)
	{
		n = readIn();
		m = readIn();
		for (int i = 1; i <= n; i++)
		{
			nodes1[i].read();
		}
		std::sort(nodes1 + 1, nodes1 + 1 + n);
		for (int i = 1; i <= m; i++)
		{
			nodes2[i].read();
		}
		std::sort(nodes2 + 1, nodes2 + 1 + m);
		work();
	}
}

int main()
{
#ifndef JUDGE
	freopen("machine.in", "r", stdin);
	freopen("machine.out", "w", stdout);
#endif
	run();
	return 0;
}