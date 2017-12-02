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

const INT maxn = 2e5 + 5;
INT n, q, attr;
INT head[maxn];
INT To[maxn * 2];
INT next[maxn * 2];
inline void addEdge(INT s, INT e)
{
	To[0]++;
	To[To[0]] = e;
	next[To[0]] = head[s];
	head[s] = To[0];
}

INT vis[maxn];
INT depth[maxn];
struct RMQ
{
	INT& N;
	INT seq[19][2 * maxn];

	RMQ() : N(seq[0][0])
	{
	}

	void build()
	{
		INT size = 0;
		while (1 << (size + 1) < N) size++;
		for (int i = 1; i <= size; i++)
		{
			for (int j = 1; j + (1 << i) - 1 <= N; j++)
			{
				if (depth[seq[i - 1][j]] < depth[seq[i - 1][j + (1 << (i - 1))]])
				{
					seq[i][j] = seq[i - 1][j];
				}
				else
				{
					seq[i][j] = seq[i - 1][j + (1 << (i - 1))];
				}
			}
		}
	}

	INT LCA(INT from, INT to)
	{
		INT visF = vis[from];
		INT visT = vis[to];
		if (visF > visT) std::swap(visF, visT);
		INT size = 0;
		while (1 << (size + 1) < (visT - visF + 1)) size++;
		if (depth[seq[size][visF]] < depth[seq[size][visT - (1 << size) + 1]])
		{
			return seq[size][visF];
		}
		else
		{
			return seq[size][visT - (1 << size) + 1];
		}
	}
} rmq;
void dfs(INT node = 1)
{
	INT& size = rmq.seq[0][0];
	vis[node] = size + 1;
	rmq.seq[0][++size] = node;
	for (int i = head[node]; i; i = next[i])
	{
		if (vis[To[i]]) continue;
		depth[To[i]] = depth[node] + 1;
		dfs(To[i]);
		rmq.seq[0][++size] = node;
	}
}

void run()
{
	n = readIn();
	q = readIn();
	attr = readIn();
	INT e = n - 1;
	for (int i = 1; i <= e; i++)
	{
		INT from = readIn();
		INT to = readIn();
		addEdge(from, to);
		addEdge(to, from);
	}

	depth[1] = 1;
	dfs();
	rmq.build();

	while (q--)
	{
		INT A = readIn();
		INT B = readIn();
		INT C = readIn();
		INT AB = rmq.LCA(A, B);
		INT BC = rmq.LCA(B, C);
		INT AC = rmq.LCA(A, C);

		INT ans = 0;
		//if (depth[AB] < depth[B])
		//{
		//	if (depth[BC] > depth[AB])
		//	{
		//		ans = depth[B] - depth[BC] + 1;
		//	}
		//	else if (depth[BC] == depth[AB])
		//	{
		//		ans = depth[B] - depth[BC] + 1 + (depth[AC] - depth[BC]);
		//	}
		//	else if (depth[BC] < depth[AB])
		//	{
		//		ans = depth[B] - depth[AB] + 1;
		//	}
		//}
		//else if (depth[AB] == depth[B])
		//{
		//	if (depth[BC] < depth[B])
		//	{
		//		ans = 1;
		//	}
		//	else if (depth[BC] == depth[B])
		//	{
		//		ans = depth[AC] - depth[B] + 1;
		//	}
		//}
#define dis(x, y) (depth[x] + depth[y] - (depth[x##y] << 1) + 1)
		ans = (dis(A, B) + dis(B, C) - dis(A, C) + 1) >> 1;
		printf("%d\n", ans); //INT is int here
	}
}

int main()
{
	run();
	return 0;
}
