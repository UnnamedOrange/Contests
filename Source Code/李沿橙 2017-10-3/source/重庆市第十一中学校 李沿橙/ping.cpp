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
typedef int INT;
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
inline void printOut(INT x)
{
	if(!x)
	{
		putchar('0');
		return;
	}
	char buffer[10];
	INT length = 0;
	while(x)
	{
		buffer[length++] = x % 10 + '0';
		x /= 10;
	}
	do
	{
		putchar(buffer[--length]);
	}
	while(length);
}

const INT maxn = INT(1e5) + 5;
const INT maxK = INT(3e5) + 5;
INT n, m, K;
std::vector<std::vector<INT> > edges;
struct Q
{
	INT u;
	INT v;
} questions[maxK];

INT parent[maxn];
INT depth[maxn];
INT root = 1;

void DFS(INT node = 1)
{
	for(int i = 0; i < edges[node].size(); i++)
	{
		INT to = edges[node][i];
		if(to == parent[node]) continue;
		parent[to] = node;
		depth[to] = depth[node] + 1;
		DFS(to);
	}
}

#define RunInstance(x) delete new x
struct work
{
	work()
	{

	}
};
struct cheat2
{
	static bool comp(const Q& a, const Q& b)
	{
		if(depth[a.v] != depth[b.v]) return depth[a.v] < depth[b.v];
		return depth[a.u] > depth[b.u];
	}

	cheat2()
	{
		for(int i = 0; i < K; i++)
		{
			if(depth[questions[i].u] > depth[questions[i].v]) std::swap(questions[i].u, questions[i].v);
		}
		std::sort(questions, questions + K, comp);

		INT ans = 0;
		std::vector<INT> ansSet;
		INT lastRight = 0;
		for(int i = 0; i < K; i++)
		{
			if(lastRight < depth[questions[i].u])
			{
				ans++;
				ansSet.push_back(questions[i].v);
				lastRight = depth[questions[i].v];
			}
		}
		printOut(ans);
		putchar('\n');
		for(int i = 0; i < ansSet.size(); i++)
		{
			printOut(ansSet[i]);
			putchar('\n');
		}
		putchar('\n');
	}
};
struct cheat1
{
	void jump(INT u, INT v, std::set<INT>& s)
	{
		if(depth[v] > depth[u]) std::swap(u, v);
		while(depth[u] > depth[v])
		{
			s.insert(u);
			u = parent[u];
		}
		while(u != v)
		{
			s.insert(u);
			s.insert(v);
			u = parent[u];
			v = parent[v];
		}
		s.insert(u);
	}

	INT count1[1 << 16];

	cheat1()
	{
		std::vector<std::set<INT> > sets(K);

		for(int i = 0; i < K; i++)
		{
			jump(questions[i].u, questions[i].v, sets[i]);
		}

		INT U = 1 << n;
		count1[0] = 0;
		for(int i = 1; i < U; i++)
		{
			count1[i] = count1[i ^ (i & -i)] + 1;
		}

		INT minVal = n + 1;
		INT minSet;
		for(int S = 0; S < U; S++)
		{
			std::vector<bool> bOk(K);
			INT remain = K;
			for(int i = 0; i < n; i++)
			{
				INT node = i + 1;
				if(S & (1 << i))
				{
					for(int k = 0; k < K; k++)
					{
						if(!bOk[k] && sets[k].count(node))
						{
							bOk[k] = true;
							remain--;
						}
					}
				}
			}
			if(!remain)
			{
				if(count1[S] < minVal)
				{
					minVal = count1[S];
					minSet = S;
				}
			}
		}
		printOut(minVal);
		putchar('\n');
		for(int i = 0; i < n; i++)
		{
			if(minSet & (1 << i))
			{
				printOut(i + 1);
				putchar(' ');
			}
		}
		putchar('\n');
	}
};

bool isLine()
{
	return *std::max_element(depth + 1, depth + 1 + n) == n;
}
INT degree[maxn];

void run()
{
	n = readIn();
	m = readIn();
	edges.resize(n + 1);
	for(int i = 1; i <= m; i++)
	{
		INT from = readIn();
		INT to = readIn();
		edges[from].push_back(to);
		edges[to].push_back(from);
		degree[from]++;
		degree[to]++;
	}
	K = readIn();
	for(int i = 0; i < K; i++)
	{
		questions[i].u = readIn();
		questions[i].v = readIn();
	}

	for(int i = 1; i <= n; i++)
	{
		if(degree[i] == 1)
		{
			root = i;
			break;
		}
	}
	depth[root] = 1;
	DFS(root);

	if(n <= 15) RunInstance(cheat1);
	else if(isLine()) RunInstance(cheat2);
	else RunInstance(work);
}

int main()
{
#ifndef JUDGE
	freopen("ping.in", "r", stdin);
	freopen("ping.out", "w", stdout);
#endif
	run();
	return 0;
}
