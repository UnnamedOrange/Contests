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
		a = a * 10 - (ch - '0');
		ch = getchar();
	}
	if (positive) a = -a;
	return a;
}
void printOut(INT_PUT x)
{
	char buffer[20];
	int length = 0;
	if (x < 0) putchar('-');
	else x = -x;
	do
	{
		buffer[length++] = -(x % 10) + '0';
	} while (x /= 10);
	do
	{
		putchar(buffer[--length]);
	} while (length);
	putchar('\n');
}

const int maxn = int(1e5) + 5;
int n, k, seed, p;
int a[maxn];

#define RunInstance(x) delete new x
struct brute
{
	std::vector<std::vector<int> > seqs;

	brute()
	{
		int U = 1 << n;
		seqs.reserve(U);
		for (int S = 1; S < U; S++)
		{
			seqs.resize(seqs.size() + 1);
			seqs.back().reserve(n);
			for (int i = 0; i < n; i++)
				if (S & (1 << i))
					seqs.back().push_back(a[i]);
		}

		std::sort(seqs.begin(), seqs.end());
		for (int i = 0; i < k; i++)
		{
			const std::vector<int>& t = seqs[i];
			LL hash = 0;
			for (int j = 0; j < t.size(); j++)
				hash = (hash * seed + t[j]) % p;
			printOut(hash);
		}
	}
};
struct work
{
	struct Seq
	{
		int node, preNode;
		int hash, preHash;
		int last, l, r;
	};
	Seq seqs[maxn * 3];
	int pool[maxn * 3 + 1];

	int Log[maxn];
	int rmq[17][maxn];
	void goRMQ()
	{
		for (int i = 1; i <= n; i++)
		{
			int t = 0;
			while ((1 << (t + 1)) < i) t++;
			Log[i] = t;
		}
		for (int i = 0; i < n; i++)
			rmq[0][i] = i;
		for (int i = 1; i <= Log[n]; i++)
		{
			int delta = 1 << (i - 1);
			for (int j = 0; j + (1 << i) <= n; j++)
			{
				int left = rmq[i - 1][j];
				int right = rmq[i - 1][j + delta];
				if (a[left] <= a[right])
					rmq[i][j] = left;
				else
					rmq[i][j] = right;
			}
		}
	}
	int query(int l, int r)
	{
		int length = r - l + 1;
		int t = Log[length];
		int left = rmq[t][l];
		int right = rmq[t][r - (1 << t) + 1];
		if (a[left] <= a[right])
			return left;
		else
			return right;
	}

	int tSize;
	int depth[maxn * 3];
	int val[maxn * 3];
	int parent[19][maxn * 3];
	int makeSingle(int ch, int p)
	{
		static std::vector<std::map<int, int> > son(maxn * 3);
		if (son[p].count(ch))
			return son[p][ch];
		else
		{
			int code = son[p][ch] = ++tSize;
			parent[0][code] = p;
			val[code] = ch;
			depth[code] = depth[p] + 1;
			for (int i = 1, to = Log[depth[code]] + 1; i < to; i++)
			{
				parent[i][code] = parent[i - 1][parent[i - 1][code]];
			}
			return code;
		}
	}
	bool comp(int x, int y)
	{
		const Seq& a = seqs[x];
		const Seq& b = seqs[y];

		x = a.node;
		y = b.node;
		if (x == y) return false;
		bool swap = depth[x] < depth[y];
		if (swap) std::swap(x, y);

		for (int i = Log[std::max(depth[x], depth[y])] + 1; ~i; i--)
			if (depth[parent[i][x]] >= depth[y])
				x = parent[i][x];
		if (x == y) return swap;
		for (int i = Log[std::max(depth[x], depth[y])] + 1; ~i; i--)
			if (parent[i][x] != parent[i][y])
			{
				x = parent[i][x];
				y = parent[i][y];
			}
		return swap ? val[y] < val[x] : val[x] < val[y];
	}

	int size;
	int heap[maxn * 3];
	void push(int idx)
	{
		heap[++size] = idx;
		int cnt = size;
		int p;
		while (cnt > 1)
		{
			p = cnt >> 1;
			if (comp(heap[cnt], heap[p]))
			{
				std::swap(heap[cnt], heap[p]);
				cnt = p;
			}
			else break;
		}
	}
	int top()
	{
		return heap[1];
	}
	void pop()
	{
		std::swap(heap[1], heap[size]);
		size--;
		int cnt = 1;
		int next = cnt << 1;
		while (next <= size)
		{
			if (next < size && comp(heap[next + 1], heap[next]))
				next++;
			if (comp(heap[next], heap[cnt]))
			{
				std::swap(heap[next], heap[cnt]);
				cnt = next;
				next = cnt << 1;
			}
			else
				break;
		}
	}

	work() : size(), depth(), parent(), tSize()
	{
		pool[0] = 0;
		for (int i = 0; i < sizeof(seqs) / sizeof(Seq); i++)
			pool[++pool[0]] = i;

		goRMQ();

		for (int i = 0; i < n; i++)
		{
			int idx = pool[pool[0]--];
			Seq& s = seqs[idx];
			s.node = makeSingle(a[i], 0);
			s.preNode = 0;
			s.l = i;
			s.r = i;
			s.last = i;
			s.hash = a[i] % p;
			s.preHash = 0;
			push(idx);
		}

		for (int i = 1; i <= k; i++)
		{
			int t = top();
			const Seq& cnt = seqs[t];
			pop();
			printOut(cnt.hash);

			if (cnt.last < n - 1)
			{
				int idx = pool[pool[0]--];
				Seq& s = seqs[idx];
				s = cnt;
				int minPos = query(s.last + 1, n - 1);
				s.preNode = s.node;
				s.node = makeSingle(a[minPos], s.node);
				s.preHash = s.hash;
				s.hash = ((LL)s.hash * seed + a[minPos]) % p;
				s.last = minPos;
				s.l = cnt.last + 1;
				s.r = n - 1;
				push(idx);
			}

			if (cnt.l < cnt.r)
			{
				if (cnt.l < cnt.last)
				{
					int idx = pool[pool[0]--];
					Seq& s = seqs[idx];
					s = cnt;
					int minPos = query(s.l, s.last - 1);
					s.node = makeSingle(a[minPos], s.preNode);
					s.hash = ((LL)s.preHash * seed + a[minPos]) % p;
					s.last = minPos;
					s.l = cnt.l;
					s.r = cnt.last - 1;
					push(idx);
				}
				if (cnt.last < cnt.r)
				{
					int idx = pool[pool[0]--];
					Seq& s = seqs[idx];
					s = cnt;
					int minPos = query(s.last + 1, s.r);
					s.node = makeSingle(a[minPos], s.preNode);
					s.hash = ((LL)s.preHash * seed + a[minPos]) % p;
					s.last = minPos;
					s.l = cnt.last + 1;
					s.r = cnt.r;
					push(idx);
				}
			}
			pool[++pool[0]] = t;
		}
	}
};

void run()
{
	n = readIn();
	k = readIn();
	seed = readIn();
	p = readIn();
	for (int i = 0; i < n; i++)
		a[i] = readIn();

	if (n <= 15)
		RunInstance(brute);
	else
		RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("sequence.in", "r", stdin);
	freopen("sequence.out", "w", stdout);
#endif
	run();
	return 0;
}