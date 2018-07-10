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
	putchar('\n');
}

const int maxn = int(5e5) + 5;
int n, m;
int minx = INT_MAX, maxx = INT_MIN;
int a[maxn];
LL sum[maxn];
struct Query
{
	int x, y;
	void read()
	{
		x = readIn();
		y = readIn();
		minx = std::min(minx, x);
		maxx = std::max(maxx, x);
	}
} querys[maxn];

#define RunInstance(x) delete new x
struct brute1
{
	static const int maxN = 305;
	static const int maxx = 1005;
	LL f[maxx][maxN];

	LL DP(int x, int y)
	{
		LL& ans = f[x][y];
		if (~ans) return ans;
		if (x == 1) return ans = a[y];
		if (y == 1) return ans = DP(x - 1, y) + a[y];
		return ans = std::min(DP(x - 1, y - 1), DP(x - 1, y)) + a[y];
	}

	brute1()
	{
		std::memset(f, -1, sizeof(f));
		for (int i = 1; i <= m; i++)
			printOut(DP(querys[i].x, querys[i].y));
	}
};
struct brute2
{
	brute2()
	{
		for (int i = 1; i <= m; i++)
		{
			const Query& q = querys[i];
			LL ans = (LL)q.x * a[q.y];
			for (int j = 1; j < q.x && q.y - j >= 1; j++)
			{
				ans = std::min(ans, sum[q.y] - sum[q.y - j] +
					(LL)(q.x - j) * a[q.y - j]);
			}
			printOut(ans);
		}
	}
};
struct brute3
{
	int N;
	struct Ins
	{
		int pos;
		int idx;
		Ins() {}
		Ins(int pos, int idx) : pos(pos), idx(idx) {}
		bool operator<(const Ins& b) const
		{
			if (pos != b.pos) return pos < b.pos;
			return idx < b.idx;
		}
	} inss[maxn * 2];
	int idx[maxn * 2];
	int temp[maxn * 2];

	static long double slope(int j, int k)
	{
		LL up = (sum[j] - sum[k]) -
			((LL)j * a[j] - (LL)k * a[k]);
		if (!up) return 0;
		if (a[j] == a[k]) return up > 0 ? 1e100 : 1e-100;
		return (long double)up / (a[j] - a[k]);
	}
	static int dcmp(long double x)
	{
		const long double EPS = 1e-8;
		if (std::abs(x) <= EPS) return 0;
		return x < 0 ? -1 : 1;
	}

	struct SegTree
	{
		int deque[maxn * 20];
		static inline int code(int l, int r)
		{
			return (l + r) | (l != r);
		}
		int stamp;
		int size;
		int begin[maxn * 2];
		int head[maxn * 2];
		int tail[maxn * 2];
		int vis[maxn * 2];

		void helper(int l, int r)
		{
			int c = code(l, r);
			if (vis[c] != stamp)
			{
				vis[c] = stamp;
				head[c] = tail[c] = begin[c];
			}
		}
		int g_Pos, g_Val, g_L, g_R, X, Y;
		void insert_(int l, int r)
		{
			helper(l, r);
			int c = code(l, r);
			int& h = head[c];
			int& t = tail[c];
			while (t - h > 1 &&
				dcmp(slope(g_Pos, deque[t - 1]) -
					slope(deque[t - 1], deque[t - 2])) > 0)
				t--;
			deque[t++] = g_Pos;

			if (l == r)
				return;
			int mid = (l + r) >> 1;
			if (g_Pos <= mid) insert_(l, mid);
			else insert_(mid + 1, r);
		}
		LL query_(int l, int r)
		{
			helper(l, r);
			if (g_L <= l && r <= g_R)
			{
				int c = code(l, r);
				int& h = head[c];
				int& t = tail[c];
				if (h == t) return LLONG_MAX;
				while (t - h > 1 &&
					dcmp(slope(deque[h + 1], deque[h]) - g_Val) > 0)
					h++;

				int j = deque[h];
				return sum[Y] - sum[j] + (LL)(X - (Y - j)) * a[j];
			}
			int mid = (l + r) >> 1;
			LL ret = LLONG_MAX;
			if (g_L <= mid) ret = std::min(ret, query_(l, mid));
			if (g_R > mid) ret = std::min(ret, query_(mid + 1, r));
			return ret;
		}

	public:
		SegTree() : stamp(), size(), vis() {}
		void build(int l, int r)
		{
			begin[code(l, r)] = size;
			size += r - l + 1;
			if (l == r)
				return;
			int mid = (l + r) >> 1;
			build(l, mid);
			build(mid + 1, r);
		}
		void clear() { stamp++; }
		void insert(int pos)
		{
			g_Pos = pos;
			insert_(1, n);
		}
		LL query(int l, int r, int val, int x, int y)
		{
			g_L = l;
			g_R = r;
			g_Val = val;
			X = x;
			Y = y;
			return query_(1, n);
		}
	} st;

	bool comp(const Ins& x, const Ins& y)
	{
		if (x.idx && y.idx)
			return querys[x.idx].x - querys[x.idx].y >
			querys[y.idx].x - querys[y.idx].y;
		if (x.idx)
			return false;
		if (y.idx)
			return true;
		return a[x.pos] <= a[y.pos];
	}

	LL ans[maxn];
	void cdq(int l, int r)
	{
		if (l == r)
		{
			return;
		}
		int mid = (l + r) >> 1;
		cdq(l, mid);
		cdq(mid + 1, r);

		st.clear();
		for (int i = l; i <= mid; i++)
		{
			if (inss[idx[i]].idx)
				continue;
			st.insert(inss[idx[i]].pos);
		}
		for (int i = mid + 1; i <= r; i++)
		{
			const Ins& ins = inss[idx[i]];
			if (!ins.idx)
				continue;
			const Query& q = querys[ins.idx];

			ans[ins.idx] = std::min(ans[ins.idx],
				st.query(std::max(1, q.y - q.x + 1), q.y, q.x - q.y, q.x, q.y));
		}

		int i = l;
		int j = mid + 1;
		int k = l;
		while (k <= r)
		{
			if (j > r || (i <= mid && comp(inss[idx[i]], inss[idx[j]])))
				temp[k++] = idx[i++];
			else
				temp[k++] = idx[j++];
		}
		for (i = l; i <= r; i++)
			idx[i] = temp[i];
	}
	brute3() : N()
	{
		for (int i = 1; i <= n; i++)
			inss[++N] = Ins(i, 0);
		for (int i = 1; i <= m; i++)
			inss[++N] = Ins(querys[i].y, i);
		std::sort(inss + 1, inss + 1 + N);
		for (int i = 1; i <= N; i++)
			idx[i] = i;

		st.build(1, n);
		for (int i = 1; i <= m; i++)
			ans[i] = LLONG_MAX;
		cdq(1, N);

		for (int i = 1; i <= m; i++)
			printOut(ans[i]);
	}
};
struct work
{
	int idx[maxn];

	static bool comp(const int& x, const int& y)
	{
		return querys[x].y < querys[y].y;
	}

	int stack[maxn];
	LL ans[maxn];

	LL calc(int x, int y, int j)
	{
		return sum[y] - sum[j] + (LL)(x - (y - j)) * a[j];
	}

	long double GetX(int i, int p1, int p2)
	{
		return (long double)((sum[p1] - sum[p2]) +
			(LL)(i - p1) * a[p1] - (LL)(i - p2) * a[p2]) / (a[p1] - a[p2]);
	}

	work()
	{
		for (int i = 1; i <= m; i++)
			idx[i] = i;
		std::sort(idx + 1, idx + 1 + m, comp);

		stack[0] = 0;
		int cnt = 1;
		for (int i = 1; i <= n && cnt <= m; i++)
		{
			while (stack[0] && a[stack[stack[0]]] >= a[i])
				stack[0]--;
			while (stack[0] > 1)
			{
				if (GetX(i, i, stack[stack[0]]) >= GetX(i, stack[stack[0] - 1], stack[stack[0]]))
					stack[0]--;
				else
					break;
			}
			stack[++stack[0]] = i;

			while (cnt <= m && querys[idx[cnt]].y == i)
			{
				const Query& q = querys[idx[cnt]];
				int l = 1, r = stack[0];
				while (r - l > 0)
				{
					int mid = (l + r) >> 1;
					int p1 = stack[mid];
					int p2 = stack[mid + 1];
					if (GetX(i, p1, p2) >= q.x)
						l = mid + 1;
					else
						r = mid;
				}
				ans[idx[cnt]] = calc(q.x, q.y, stack[l]);
				cnt++;
			}
		}
		for (int i = 1; i <= m; i++)
			printOut(ans[i]);
	}
};

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
		sum[i] = sum[i - 1] + (a[i] = readIn());
	m = readIn();
	for (int i = 1; i <= m; i++)
		querys[i].read();

	if (n <= 300 && maxx <= 1000)
		RunInstance(brute1);
	else if (n <= 300)
		RunInstance(brute2);
	else if (n <= int(1e5) && m <= int(1e5))
		RunInstance(brute3);
	else
		RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("function.in", "r", stdin);
	freopen("function.out", "w", stdout);
#endif
	run();
	return 0;
}