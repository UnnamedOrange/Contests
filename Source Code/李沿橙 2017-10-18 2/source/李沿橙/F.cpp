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
typedef unsigned long long ULL;
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
	putchar(' ');
}

const INT INF = (~(INT(1) << (sizeof(INT) * 8 - 1)));
const INT maxn = 100005;
INT n;

struct Tree
{
	struct Edge
	{
		INT to;
		INT next;
	} edges[maxn * 2];
	INT head[maxn];
	INT count_;
	void addEdge(INT from, INT to)
	{
		count_++;
		edges[count_].to = to;
		edges[count_].next = head[from];
		head[from] = count_;
	}
	void read()
	{
		for (int i = 1; i < n; i++)
		{
			INT u = readIn();
			INT v = readIn();
			degree[u]++;
			degree[v]++;
			addEdge(u, v);
			addEdge(v, u);
		}
	}

	Tree() : count_(), head(), edges(), degree() {}

	INT minVal, wu, wv;
	void dfs1(INT node, INT parent)
	{
		INT val = 0;
		size[node] = 1;
		for (int i = head[node]; i; i = edges[i].next)
		{
			INT to = edges[i].to;
			if (to == parent) continue;
			dfs1(to, node);
			size[node] += size[to];
			val = std::max(val, size[to]);
		}
		val = std::max(val, n - size[node]);

		if (val < minVal)
		{
			minVal = val;
			wu = node;
			wv = 0;
		}
		else if (val == minVal)
		{
			wv = node;
		}
	}
	void getW()
	{
		minVal = INF;
		wu = wv = 0;
		dfs1(1, 0);
	}

	INT size[maxn];
	INT degree[maxn];
	struct HashNode
	{
		INT node;
		template <ULL p, ULL mod>
		struct HashVal
		{
			ULL val;
			HashVal() : val() {}
			HashVal(ULL val) : val(val) {}
			void calcHash(const std::vector<INT>& t, INT size, INT depth, INT degree)
			{
				val = 0;
				for (int i = 0; i < int(t.size()); i++)
					val = (val * p + t[i]) % mod;
				val = (val * p + size) % mod;
				val = (val * p + depth) % mod;
				val = (val * p + degree) % mod;
			}
			HashVal operator+ (const HashVal& b) const
			{
				return HashVal((val * p + b.val) % mod);
			}
			HashVal operator+= (ULL b)
			{
				val = (val * p + b) % mod;
			}
			bool operator< (const HashVal& b) const
			{
				return val < b.val;
			}
			bool operator!= (const HashVal& b) const
			{
				return val != b.val;
			}
		};
		HashVal<29, INT(1e9) + 7> val1;
		HashVal<31, INT(1e9) + 9> val2;
		HashNode() : node() {}
		bool operator< (const HashNode& b) const
		{
			if (val1 != b.val1) return val1 < b.val1;
			return val2 < b.val2;
		}
		bool operator!= (const HashNode& b) const
		{
			return *this < b || b < *this;
		}
		bool operator> (const HashNode& b) const
		{
			return node < b.node;
		}
		HashNode operator+ (const HashNode& b) const
		{
			HashNode ret;
			ret.val1 = val1 + b.val1;
			ret.val2 = val2 + b.val2;
			return ret;
		}
	} hash[2][maxn];

	void dfs2(INT node, INT parent, INT depth, HashNode* nodes)
	{
		size[node] = 1;
		std::vector<INT> t1, t2;
		for (int i = head[node]; i; i = edges[i].next)
		{
			INT to = edges[i].to;
			if (to == parent) continue;
			dfs2(to, node, depth + 1, nodes);
			t1.push_back(nodes[to].val1.val);
			t2.push_back(nodes[to].val2.val);
			size[node] += size[to];
		}
		std::sort(t1.begin(), t1.end());
		std::sort(t2.begin(), t2.end());

		nodes[node].node = node;

		nodes[node].val1.calcHash(t1, size[node], depth, degree[node]);
		nodes[node].val2.calcHash(t2, size[node], depth, degree[node]);
	}
	INT clock;
	INT finalMap[2][maxn];
	void dfs3(INT node, INT parent, HashNode* nodes, INT idx)
	{
		std::vector<HashNode> t;
		for (int i = head[node]; i; i = edges[i].next)
		{
			INT to = edges[i].to;
			if (to == parent) continue;
			t.push_back(nodes[to]);
		}
		std::sort(t.begin(), t.end());
		for (int i = 0; i < t.size(); i++)
			finalMap[idx][++clock] = t[i].node;
		for (int i = 0; i < t.size(); i++)
			dfs3(t[i].node, node, nodes, idx);
	}
	void runHash(INT root, INT idx)
	{
		dfs2(root, 0, 1, hash[idx]);
		std::sort(hash[idx] + 1, hash[idx] + 1 + n, std::greater<HashNode>());
	}
	void runMap(INT root, INT idx)
	{
		finalMap[idx][clock = 1] = root;
		dfs3(root, 0, hash[idx], idx);
	}
	bool compHash(INT idx1, Tree& tb, INT idx2)
	{
		return !(this->hash[idx1][idx1 ? wv : wu] != tb.hash[idx2][idx2 ? tb.wv : tb.wu]);
	}
} t1, t2;

void map(INT idx1, INT idx2)
{
	puts("YES");

	t1.runMap(idx1 ? t1.wv : t1.wu, idx1);
	t2.runMap(idx2 ? t2.wv : t2.wu, idx2);

	std::vector<INT> ans(n + 1);
	for (int i = 1; i <= n; i++)
		ans[t1.finalMap[idx1][i]] = t2.finalMap[idx2][i];
	for (int i = 1; i <= n; i++)
		printOut(ans[i]);
	putchar('\n');
}

void run()
{
	n = readIn();
	t1.read();
	t2.read();
	t1.getW();
	t2.getW();
	t1.runHash(t1.wu, 0);
	if (t1.wv) t1.runHash(t1.wv, 1);
	t2.runHash(t2.wu, 0);
	if (t2.wv) t2.runHash(t2.wv, 1);

	if (t1.compHash(0, t2, 0))
	{
		map(0, 0);
		return;
	}
	else if (t1.wv && t2.wv && t1.compHash(1, t2, 1))
	{
		map(1, 1);
		return;
	}
	else if (t1.wv && t1.compHash(1, t2, 0))
	{
		map(1, 0);
		return;
	}
	else if (t2.wv && t1.compHash(0, t2, 1))
	{
		map(0, 1);
		return;
	}
	else
		puts("NO");
}

int main()
{
#ifndef LOCAL
	freopen("check.in", "r", stdin);
	freopen("check.out", "w", stdout);
#endif
	run();
	return 0;
}
