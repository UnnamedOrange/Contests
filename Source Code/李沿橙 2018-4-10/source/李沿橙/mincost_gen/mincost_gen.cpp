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
	INT_PUT a = 0; bool positive = true;
	char ch = getchar();
	while (!(ch == '-' || std::isdigit(ch))) ch = getchar();
	if (ch == '-') { positive = false; ch = getchar(); }
	while (std::isdigit(ch)) { a = a * 10 - (ch - '0'); ch = getchar(); }
	return positive ? -a : a;
}
void printOut(INT_PUT x)
{
	char buffer[20]; int length = 0;
	if (x < 0) putchar('-'); else x = -x;
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
}

const int buffer_size = 8192;
char buffer[buffer_size];
const char name[] = "mincost";
int g_idx;
LL rand(LL from, LL to)
{
#define r(x) ((LL)rand() << x)
	LL ret = r(45) | r(30) | r(15) | r(0);
#undef r
	return from + ret % (to - from + 1);
}
struct CaseBase
{
	CaseBase()
	{
		g_idx++;
		sprintf(buffer, "%s%d.in", name, g_idx);
		freopen(buffer, "w", stdout);

		srand(time(NULL) + clock());
	}
	~CaseBase()
	{
		fclose(stdout);

		sprintf(buffer, "%s.exe < %s%d.in > %s%d.ans", name, name, g_idx, name, g_idx);
		system(buffer);
	}
};
#define GoCase(x, t, ...) for (int o = 0; o < t; o++) x(__VA_ARGS__)

const int INF = (~(int(1) << (sizeof(int) * 8 - 1)));
const int maxn = int(3e5) + 5;
const int maxm = int(5e5) + 5;
int n, m, k;
int a[maxn];
int b[maxn];
void genWeight()
{
	k = rand(1, 1e9) % n + 1;
	for (int i = 1; i <= n; i++)
	{
		a[i] = rand(1, 1e9) + 1 >> 1;
		b[i] = rand(1, 1e9) + 1 >> 1;
	}
}

int idx[maxn];
std::vector<std::set<int> > G;
std::vector<std::pair<int, int> > edges;
void genMap()
{
	G.clear();
	G.resize(n + 1);

	if (m < n - 1)
	{
		for (int i = 1; i <= m; )
		{
			int from = rand() % (n - 1) + 1;
			int to = rand() % (n - from) + from + 1;
			if (!G[from].count(to))
			{
				G[from].insert(to);
				i++;
			}
		}
	}
	else
	{
		for (int i = 1; i <= n; i++)
			idx[i] = i;
		std::random_shuffle(idx + 1, idx + 1 + n);

		int chain = n * 3 / 5;
		chain = chain + rand() % (n - chain + 1);
		for (int i = 1; i < chain; i++)
			G[idx[i]].insert(idx[i + 1]);
		for (int i = chain + 1; i <= n; i++)
		{
			int from = rand() % (i - 1) + 1;
			G[idx[from]].insert(idx[i]);
		}

		for (int i = n; i <= m; )
		{
			int from = rand() % (n - 1) + 1;
			int to = rand() % (n - from) + from + 1;
			if (!G[idx[from]].count(idx[to]))
			{
				G[idx[from]].insert(idx[to]);
				i++;
			}
		}
	}
	edges.clear();
	edges.reserve(m);
	for (int i = 1; i <= n; i++)
		for (std::set<int>::iterator it = G[i].begin(); it != G[i].end(); it++)
		{
			edges.push_back(std::make_pair(i, *it));
			if (rand() > rand())
				std::swap(edges.back().first, edges.back().second);
		}

	std::random_shuffle(edges.begin(), edges.end());
}

struct case1 : private CaseBase
{
	case1(int N, int M)
	{
		n = rand((double)N * 0.9, N);
		m = rand((double)M * 0.5, M);
		genWeight();
		genMap();

		printf("%d %d %d\n", n, m, k);
		for (int i = 1; i <= n; i++)
			printf("%d %d\n", a[i], b[i]);
		for (int i = 0; i < edges.size(); i++)
			printf("%d %d\n", edges[i].first, edges[i].second);
	}
};
struct case2 : private CaseBase
{
	case2(int N)
	{
		n = rand((double)N * 0.9, N);
		m = n - 1;
		genWeight();
		genMap();

		printf("%d %d %d\n", n, m, k);
		for (int i = 1; i <= n; i++)
			printf("%d %d\n", a[i], b[i]);
		for (int i = 0; i < edges.size(); i++)
			printf("%d %d\n", edges[i].first, edges[i].second);
	}
};

void run()
{
	GoCase(case1, 6, 20, 100);
	GoCase(case1, 4, 5000, 5000);
	GoCase(case2, 4, 300000);
	GoCase(case1, 10, 300000, 500000);
}

int main()
{
	run();
	return 0;
}