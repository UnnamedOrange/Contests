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
	while (!(ch == '-' || std::isdigit(ch))) ch = getchar();
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

int randEx()
{
	return rand() << 15 | rand();
}
#define rand randEx

const int INF = (~(int(1) << (sizeof(int) * 8 - 1)));
const int maxn = int(3e5) + 5;
const int maxm = int(5e5) + 5;
int n = 5000;
int m;
int k;

int a[maxn];
int b[maxn];
void genWeight()
{
	k = rand() % n + 1;
	for (int i = 1; i <= n; i++)
	{
		a[i] = rand() + 1 >> 1;
		b[i] = rand() + 1 >> 1;
	}
}

int idx[maxn];
std::vector<std::set<int> > G;
std::vector<std::pair<int, int> > edges;
void genMap()
{
	m = rand() % (n * 5 / 3);
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

void write()
{
	FILE* file = fopen("mincost.in", "w");
	fprintf(file, "%d %d %d\n", n, m, k);
	for (int i = 1; i <= n; i++)
		fprintf(file, "%d %d\n", a[i], b[i]);
	for (int i = 0; i < edges.size(); i++)
		fprintf(file, "%d %d\n", edges[i].first, edges[i].second);
	fclose(file);
}

void gen()
{
	genWeight();
	genMap();
	write();
}
void test1()
{
	system("1.exe < mincost.in > 1.out");
}
void test2()
{
	system("2.exe < mincost.in > 2.out");
}

void timer(const char* tip, const std::function<void()> f)
{
	int stamp = clock();
	printf("%s...\n", tip);
	f();
	printf("finished in %d ms\n", clock() - stamp);
}

void run()
{
	srand(time(NULL) + clock());
	LL stamp;
	while (true)
	{
		timer("generating data", gen);
		timer("running 1", test1);
		timer("running 2", test2);

		if (system("fc 1.out 2.out /n"))
		{
			system("pause > nul");
			break;
		}
	}
}

int main()
{
	run();
	return 0;
}
