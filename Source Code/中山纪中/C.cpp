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
	if (!x)
	{
		putchar('0');
		putchar('\n');
		return;
	}
	char buffer[10];
	INT length = 0;
	while (x)
	{
		buffer[length++] = x % 10 + '0';
		x /= 10;
	}
	do
	{
		putchar(buffer[--length]);
	} while (length);
	putchar('\n');
}

const INT mod = 1000000007;
const INT maxn = 100005;
const INT maxm = 1000005;
INT n, m, q;

INT C, count_;
struct EDGE
{
	INT from;
	INT to;
	INT next;
	INT index;
} E[maxm], edges[maxm];
bool visE[INT(1.5 * maxn)];
INT H[maxn], head[maxn];
inline void addEdge(INT from, INT to, EDGE e[maxm], INT h[maxn], INT& c, INT index = 0)
{
	c++;
	e[c].from = from;
	e[c].to = to;
	e[c].index = index;
	e[c].next = h[from];
	h[from] = c;
}

INT N;
INT reIndex[maxn];
bool isRing[maxn];
INT depth[maxn];
INT size;
INT next[18][maxn];
INT big[18][maxn];

INT nVis;
INT dfn[maxn];
INT low[maxn];
bool inStack[maxn];
std::stack<INT> s;

void dfs(INT node = 1, INT lastEdge = -1)
{
	low[node] = dfn[node] = ++nVis;
	s.push(node);
	inStack[node] = true;
	for(int i = H[node]; i; i = E[i].next)
	{
		if(visE[E[i].index]) continue;
		visE[E[i].index] = true;
		INT to = E[i].to;
		if(!dfn[to])
		{
			dfs(to, i);
			low[node] = std::min(low[node], low[to]);
		}
		else if(inStack[to])
		{
			low[node] = std::min(low[node], dfn[to]);
		}
	}
	if(dfn[node] == low[node])
	{
		N++;
		INT popped;
		INT nPop = 0;
		do
		{
			nPop++;
			popped = s.top();
			s.pop();
			inStack[popped] = false;
			reIndex[popped] = N;
		}while(popped != node);
		if(nPop > 1) isRing[N] = true;
	}
}
void dfs2(INT node = 1)
{
	for (int i = head[node]; i; i = edges[i].next)
	{
		INT to = edges[i].to;
		if (to == next[0][node]) continue;
		depth[to] = depth[node] + 1;
		next[0][to] = node;
		big[0][to] = isRing[node];
		dfs2(to);
	}
}
void rebuild()
{
	dfs();

	for (int i = 1; i <= C; i++)
	{
		if (reIndex[E[i].from] != reIndex[E[i].to])
			addEdge(reIndex[E[i].from], reIndex[E[i].to], edges, head, count_);
	}
	depth[1] = 1;
	dfs2();
	while (1 << size < N) size++;
	for (int i = 1; i <= size; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			next[i][j] = next[i - 1][next[i - 1][j]];
			big[i][j] = big[i - 1][j] + big[i - 1][next[i - 1][j]];
		}
	}
}

long long power(INT index)
{
	if (!index) return 1;
	long long temp = power(index >> 1);
	temp = temp * temp % mod;
	if (index & 1) temp = (temp << 1) % mod;
	return temp;
}
void work()
{
	INT from = reIndex[readIn()];
	INT to = reIndex[readIn()];
	if (depth[from] < depth[to]) std::swap(from, to);

	INT ans = INT(isRing[from]) + INT(isRing[to]);
	for (int i = size; i >= 0; i--)
	{
		if (depth[next[i][from]] < depth[to]) continue;
		ans += big[i][from];
		from = next[i][from];
	}
	if (from != to)
	{
		for (int i = size; i >= 0; i--)
		{
			if (next[i][from] == next[i][to]) continue;
			ans += big[i][from];
			ans += big[i][to];
			from = next[i][from];
			to = next[i][to];
		}
		ans += big[0][from] + big[0][to];
		from = next[0][from];
	}
	ans -= INT(isRing[from]);
	printOut(power(ans));
}

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= m; i++)
	{
		INT from = readIn();
		INT to = readIn();
		addEdge(from, to, E, H, C, i);
		addEdge(to, from, E, H, C, i);
	}
	rebuild();

	q = readIn();
	while (q--)
	{
		work();
	}
}

int main()
{
	run();
	return 0;
}
