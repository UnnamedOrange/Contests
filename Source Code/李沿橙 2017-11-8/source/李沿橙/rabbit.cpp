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
typedef double REAL;
INT readIn()
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
void printOut(INT x)
{
	char buffer[20];
	INT length = 0;
	bool minus = x < 0;
	if (minus) x = -x;
	do
	{
		buffer[length++] = x % 10 + '0';
		x /= 10;
	} while (x);
	if (minus) buffer[length++] = '-';
	do
	{
		putchar(buffer[--length]);
	} while (length);
	putchar('\n');
}

const INT INF = 0x3f3f3f3f;
const INT maxn = 1005;
const INT maxm = 1505;
INT n, m, K;
INT degree[maxn];
INT maxd;
INT root;

struct Edge
{
	INT to;
	INT next;
} edges[maxm * 2];
INT head[maxn];
void addEdge(INT from, INT to)
{
	static INT i;
	i++;
	edges[i].to = to;
	edges[i].next = head[from];
	head[from] = i;
}

#define RunInstance(x) delete new x
struct work
{
	INT N;
	struct Child
	{
		INT size;
		bool isRing;

		INT divideSize;
		void init()
		{
			if (isRing)
			{
				divideSize = (size + 1) / 2;
			}
			else
			{
				divideSize = size;
			}
		}
		INT calcDivide(INT remain)
		{
			if (isRing)
			{
				return size - (remain << 1);
			}
			else
			{
				return size - remain;
			}
		}
	} objects[maxn];
	bool vis[maxn];

	INT sign;
	INT size;

	void dfs(INT node, INT parent)
	{
		vis[node] = true;
		size++;
		for (int i = head[node]; i; i = edges[i].next)
		{
			INT to = edges[i].to;
			if (to == parent) continue;
			if (to == root)
				sign = true;
			else
				dfs(to, node);
		}
	}

	INT calc(INT len, INT s)
	{
		if (len <= 0) return 0;
		return (len + (s << 1)) / ((s << 1) + 1);
	}
	bool check(INT s)
	{
		for (int i = 1; i <= N; i++)
		{
			for (int j = 0; j <= s && j <= objects[i].divideSize; j++)
			{
				INT remain = s - j;
				INT t = 1;
				for (int k = 1; k <= N; k++)
				{
					if (i == k)
					{
						if (objects[i].isRing)
						{
							t += calc(objects[k].size - j - s - (s - j), s);
						}
						else
						{
							t += calc(objects[k].size - j - s, s);
						}
					}
					else
					{
						t += calc(objects[k].calcDivide(remain), s);
					}
				}
				if (t <= K) return true;
			}
		}

		return false;
	}

	work() : vis()
	{
		N = 0;
		for (int i = head[root]; i; i = edges[i].next)
		{
			INT to = edges[i].to;
			if (vis[to]) continue;
			sign = false;
			size = 0;
			dfs(to, root);

			++N;
			objects[N].size = size;
			objects[N].isRing = sign;
			objects[N].init();
		}

		INT l = 0, r = n + 1;
		while (r - l > 0)
		{
			INT mid = l + ((r - l) >> 1);
			if (!check(mid))
				l = mid + 1;
			else
				r = mid;
		}
		printOut(l);
	}
};

void run()
{
	n = readIn();
	m = readIn();
	K = readIn();
	for (int i = 1; i <= m; i++)
	{
		INT u = readIn();
		INT v = readIn();
		degree[u]++;
		degree[v]++;
		addEdge(u, v);
		addEdge(v, u);
	}
	for (int i = 1; i <= n; i++)
		if (degree[i] > maxd)
		{
			root = i;
			maxd = degree[i];
		}

	RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("rabbit.in", "r", stdin);
	freopen("rabbit.out", "w", stdout);
#endif
	run();
	return 0;
}
