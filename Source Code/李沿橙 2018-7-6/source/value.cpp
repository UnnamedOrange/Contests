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
typedef LL INT_PUT;
INT_PUT readIn()
{
	register INT_PUT a = 0;
	char positive = true;
	register char ch = getchar();
	while (!(std::isdigit(ch) || ch == '-')) ch = getchar();
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

const int maxn = int(1.5e5) + 5;
int n;
int t1 = true;
struct Vec
{
	int a, b;
	void read()
	{
		a = readIn();
		b = readIn();
	}
	bool operator<(const Vec& y) const
	{
		if (a != y.a) return a > y.a;
		return b > y.b;
	}
} vecs[maxn];

#define RunInstance(x) delete new x
struct brute
{
	static const int maxN = 3005;
	int idx[maxN];
	static bool comp(const int& x, const int& y)
	{
		return vecs[x].b > vecs[y].b;
	}

	brute()
	{
		for (int i = 1; i <= n; i++)
			idx[i] = i;
		std::sort(idx + 1, idx + 1 + n, comp);

		LL ans = 0;
		for (int i = 1; i <= n; i++)
		{
			LL base = (LL)vecs[i].a * i;
			ans = std::max(ans, base);
			int cnt = 0;
			for (int j = 1; j <= n; j++)
				if (idx[j] > i)
				{
					cnt++;
					ans = std::max(ans, base + (LL)cnt * vecs[idx[j]].b);
				}
		}
		printOut(ans);
	}
};
struct cheat
{
	LL g[maxn];
	LL f[maxn];

	int deque[maxn];
	int head, tail;

	cheat()
	{
		f[0] = g[0] = 0;
		for (int i = 1; i <= n; i++)
			g[i] = (LL)vecs[i].a * i;

		head = tail = 0;
		deque[tail++] = 0;
		for (int i = 1; i <= n; i++)
		{
			while (tail - head > 1 &&
				g[deque[head + 1]] - g[deque[head]] >
				(LL)vecs[i].b * (deque[head + 1] - deque[head]))
				head++;
			f[i] = g[deque[head]] + (LL)(i - deque[head]) * vecs[i].b;
			while (tail - head > 1 &&
				(LL)(g[i] - g[deque[tail - 1]]) * (deque[tail - 1] - deque[tail - 2]) >
				(LL)(g[deque[tail - 1]] - g[deque[tail - 2]]) * (i - deque[tail - 1]))
				tail--;
			deque[tail++] = i;
		}

		printOut(*std::max_element(f, f + 1 + n));
	}
};
struct work
{
	static const int maxN = 405;
	int sqrtN;
	int N;
	int inBlock[maxn];
	int lBegin[maxN];
	int rEnd[maxN];
	void initBlocks()
	{
		sqrtN = std::sqrt(n);
		N = (n - 1) / sqrtN + 1;
		std::memset(lBegin, 0, sizeof(lBegin));
		for (int i = 1; i <= n; i++)
		{
			int ib = inBlock[i] = (i - 1) / sqrtN;
			if (!lBegin[ib]) lBegin[ib] = i;
			rEnd[ib] = i;
		}
	}
	int idx[maxn];
	int rank[maxn];

	LL val[maxn];
	int tag[maxN];
	int deque[maxn];
	int head[maxN];
	int tail[maxN];
	bool appear[maxn];
	struct BIT
	{
		int c[maxn];
		BIT() : c() {}
		static inline int lowbit(int x) { return x & -x; }
		void add(int pos, int val)
		{
			while (pos <= n)
			{
				c[pos] += val;
				pos += lowbit(pos);
			}
		}
		int query(int pos)
		{
			int ret = 0;
			while (pos)
			{
				ret += c[pos];
				pos ^= lowbit(pos);
			}
			return ret;
		}
	} bit;
	void init()
	{
		std::memset(val, 0, sizeof(val));
		std::memset(tag, 0, sizeof(tag));
		std::memset(appear, 0, sizeof(appear));
		for (int i = 0; i < N; i++)
			head[i] = tail[i] = lBegin[i];
	}
	void release(int ib) // release the tags
	{
		if (!tag[ib]) return;
		int t = tag[ib];
		tag[ib] = 0;
		for (int i = lBegin[ib], to = rEnd[ib]; i <= to; i++)
			if (appear[i])
				val[i] += (LL)vecs[idx[i]].b * t;
	}
	inline long double slope(int j, int k)
	{
		if (val[j] == val[k]) return 0;
		if (vecs[idx[j]].b == vecs[idx[k]].b) return val[j] > val[k] ? 1e100 : -1e100;
		return (long double)(val[j] - val[k]) / (vecs[idx[j]].b - vecs[idx[k]].b);
	}

	void rebuild(int ib)
	{
		assert(!tag[ib]);
		head[ib] = tail[ib] = lBegin[ib];
		int& h = head[ib];
		int& t = tail[ib];
		for (int i = rEnd[ib], to = lBegin[ib]; i >= to; i--)
		{
			if (!appear[i]) continue;
			while (t - h > 1 &&
				slope(i, deque[t - 1]) > slope(deque[t - 1], deque[t - 2]))
				t--;
			deque[t++] = i;
		}
		while (t - h > 1 &&
			slope(deque[h + 1], deque[h]) > -tag[ib])
			head[ib]++;
	}
	void add(int ib)
	{
		tag[ib]++;
		int& h = head[ib];
		while (tail[ib] - h > 1 &&
			slope(deque[h + 1], deque[h]) > -tag[ib])
			h++;
	}
	void insert(int id)
	{
		id = rank[id];
		release(inBlock[id]);
		appear[id] = true;
		bit.add(id, 1);
		val[id] = (LL)vecs[idx[id]].b * bit.query(id);
		if (id == n)
			rebuild(inBlock[id]);
		else
		{
			if (inBlock[id] != inBlock[id + 1])
				rebuild(inBlock[id]);
			int bl = inBlock[id + 1];
			int br = inBlock[n];
			if (bl == br)
			{
				release(bl);
				for (int i = id + 1; i <= n; i++)
					val[i] += vecs[idx[i]].b;
				rebuild(bl);
			}
			else
			{
				release(bl);
				for (int i = id + 1, to = rEnd[bl]; i <= to; i++)
					val[i] += vecs[idx[i]].b;
				rebuild(bl);
				for (int i = bl + 1; i <= br; i++)
					add(i);
			}
		}
	}
	LL query()
	{
		LL ret = 0;
		for (int i = 0; i < N; i++)
		{
			if (head[i] != tail[i])
			{
				int j = deque[head[i]];
				ret = std::max(ret,
					val[j] + (LL)tag[i] * (vecs[idx[j]].b));
			}
		}
		return ret;
	}

	work()
	{
		initBlocks();
		for (int i = 1; i <= n; i++)
			idx[i] = i;
		std::sort(idx + 1, idx + 1 + n, brute::comp);
		for (int i = 1; i <= n; i++)
			rank[idx[i]] = i;

		init();
		LL ans = (LL)vecs[n].a * n;
		for (int i = n; i; i--)
		{
			LL base = (LL)vecs[i - 1].a * (i - 1);
			insert(i);
			ans = std::max(ans, base + query());
		}
		printOut(ans);
	}
};

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
	{
		vecs[i].read();
		if (vecs[i].a != vecs[i].b)
			t1 = false;
	}
	std::sort(vecs + 1, vecs + 1 + n);

	if (n <= 3000)
		RunInstance(brute);
	else if (t1)
		RunInstance(cheat);
	else
		RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("value.in", "r", stdin);
	freopen("value.out", "w", stdout);
#endif
	run();
	return 0;
}