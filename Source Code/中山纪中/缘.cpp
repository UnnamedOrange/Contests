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

const INT maxn = 100005;
INT n;
INT p[maxn];
INT pT[maxn];
class Tree
{
public:
	INT root;

	INT count_;
	INT head[maxn];
	INT To[maxn];
	INT next[maxn];

	INT vis[maxn];
	INT depth[maxn];
	INT N;
	INT rmq[18][maxn * 2];

	void addEdge(INT from, INT to)
	{
		count_++;
		To[count_] = to;
		next[count_] = head[from];
		head[from] = count_;
	}
private:
	void dfs(INT node)
	{
		N++;
		vis[node] = N;
		rmq[0][N] = node;
		for (int i = head[node]; i; i = next[i])
		{
			depth[To[i]] = depth[node] + 1;
			dfs(To[i]);
			N++;
			rmq[0][N] = node;
		}
	}

public:
	void goRMQ()
	{
		dfs(root);
		INT size = 0;
		while (1 << (size + 1) < N) size++;
		for (int i = 1; i <= size; i++)
		{
			for (int j = 1; j + (1 << i) - 1 <= N; j++)
			{
				if (depth[rmq[i - 1][j]] < depth[rmq[i - 1][j + (1 << (i - 1))]])
				{
					rmq[i][j] = rmq[i - 1][j];
				}
				else
				{
					rmq[i][j] = rmq[i - 1][j + (1 << (i - 1))];
				}
			}
		}
	}
	INT LCA(INT x, INT y) const
	{
		INT visX = vis[x];
		INT visY = vis[y];
		if (visX > visY) std::swap(visX, visY);
		INT length = visY - visX + 1;
		INT size = 0;
		while (1 << (size + 1) < length) size++;
		if (depth[rmq[size][visX]] < depth[rmq[size][visY - (1 << size) + 1]])
		{
			return rmq[size][visX];
		}
		else
		{
			return rmq[size][visY - (1 << size) + 1];
		}
	}
} t1, t2;

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
	{
		p[i] = readIn();
	}
	for (int i = 1; i <= n; i++)
	{
		pT[p[i]] = i;
	}
	t1.root = 1;
	t2.root = pT[1];
	for (int i = 2; i <= n; i++)
	{
		t1.addEdge(readIn(), i);
	}
	for (int i = 2; i <= n; i++)
	{
		t2.addEdge(pT[readIn()], pT[i]);
	}
	t1.goRMQ();
	t2.goRMQ();

	INT ans = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = i + 1; j <= n; j++)
		{
			ans = std::max(ans, t1.depth[t1.LCA(i, j)] + t2.depth[t2.LCA(i, j)]);
		}
	}
	cout << ans << endl;
}

int main()
{
	run();
	return 0;
}
