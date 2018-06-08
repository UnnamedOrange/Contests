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
	putchar('\n');
}

const int mod = int(1e9) + 7;
const int maxn = int(5e4) + 5;
int n, m;
int origin[maxn];

int C[maxn][11];
class SegTree
{
	static inline int code(int l, int r)
	{
		return (l + r) | (l != r);
	}
	struct Node
	{
		int f[11];
		bool bLazyFlip;
		int iLazyAdd;
	} nodes[maxn * 2];

	void update(int l, int r)
	{
		Node& cnt = nodes[code(l, r)];
		int mid = (l + r) >> 1;
		Node& lc = nodes[code(l, mid)];
		Node& rc = nodes[code(mid + 1, r)];
		for (int i = 0; i <= 10; i++)
		{
			cnt.f[i] = 0;
			for (int j = 0; j <= i; j++)
				cnt.f[i] = (cnt.f[i] + (LL)lc.f[j] * rc.f[i - j]) % mod;
		}
	}
	void coverFlip(int l, int r)
	{
		Node& cnt = nodes[code(l, r)];
		for (int i = 1; i <= 10; i += 2)
		{
			register int t = mod - cnt.f[i];
			cnt.f[i] = t == mod ? 0 : t;
		}
		cnt.bLazyFlip = !cnt.bLazyFlip;
		cnt.iLazyAdd = (mod - cnt.iLazyAdd) % mod;
	}
	void coverAdd(int l, int r, int v)
	{
		if (!v) return;
		Node& cnt = nodes[code(l, r)];
		int f[11];
		std::memcpy(f, cnt.f, sizeof(f));
		std::memset(cnt.f, 0, sizeof(cnt.f));
		register int len = r - l + 1;

		for (int i = 0, to = std::min(len, 10); i <= to; i++)
		{
			int c = 1;
			int& t = cnt.f[i];
			for (int j = i; ~j; j--, c = (LL)c * v % mod)
				t = (t + (LL)c * f[j] % mod * C[len - j][i - j]) % mod;
		}
		register int t = cnt.iLazyAdd + v;
		cnt.iLazyAdd = t >= mod ? t - mod : t;
	}
	void pushdown(int l, int r)
	{
		Node& cnt = nodes[code(l, r)];
		int mid = (l + r) >> 1;
		if (cnt.bLazyFlip)
		{
			coverFlip(l, mid);
			coverFlip(mid + 1, r);
			cnt.bLazyFlip = false;
		}
		if (cnt.iLazyAdd)
		{
			coverAdd(l, mid, cnt.iLazyAdd);
			coverAdd(mid + 1, r, cnt.iLazyAdd);
			cnt.iLazyAdd = 0;
		}
	}
	int g_L, g_R, g_Val;
	void flip_(int l, int r)
	{
		if (g_L <= l && r <= g_R)
		{
			coverFlip(l, r);
			return;
		}
		pushdown(l, r);
		int mid = (l + r) >> 1;
		if (g_L <= mid) flip_(l, mid);
		if (g_R > mid) flip_(mid + 1, r);
		update(l, r);
	}
	void add_(int l, int r)
	{
		if (g_L <= l && r <= g_R)
		{
			coverAdd(l, r, g_Val);
			return;
		}
		pushdown(l, r);
		int mid = (l + r) >> 1;
		if (g_L <= mid) add_(l, mid);
		if (g_R > mid) add_(mid + 1, r);
		update(l, r);
	}
	int gen[11];
	void query_(int l, int r)
	{
		if (g_L <= l && r <= g_R)
		{
			int* f = nodes[code(l, r)].f;
			int temp[11] = {};
			for (int i = 0; i <= g_Val; i++)
				for (int j = 0; j <= i; j++)
					temp[i] = (temp[i] + (LL)gen[j] * f[i - j]) % mod;
			for (register int i = 0; i <= g_Val; i++)
				gen[i] = temp[i];
			return;
		}
		pushdown(l, r);
		int mid = (l + r) >> 1;
		if (g_L <= mid) query_(l, mid);
		if (g_R > mid) query_(mid + 1, r);
	}

public:
	void build(int l, int r)
	{
		if (l == r)
		{
			Node& t = nodes[l << 1];
			std::memset(t.f, 0, sizeof(t.f));
			t.f[0] = 1;
			t.f[1] = origin[l];
			return;
		}
		int mid = (l + r) >> 1;
		build(l, mid);
		build(mid + 1, r);
		update(l, r);
	}
	void flip(int l, int r)
	{
		g_L = l;
		g_R = r;
		flip_(1, n);
	}
	void add(int l, int r, int v)
	{
		g_L = l;
		g_R = r;
		g_Val = v;
		add_(1, n);
	}
	int query(int l, int r, int k)
	{
		g_L = l;
		g_R = r;
		g_Val = k;
		std::memset(gen, 0, sizeof(gen));
		gen[0] = 1;
		query_(1, n);
		return gen[k];
	}
} st;

void run()
{
	n = readIn();
	m = readIn();
	C[0][0] = 1;
	for (int i = 1; i <= n; i++)
	{
		C[i][0] = 1;
		register int t;
		for (int j = 1, to = std::min(i, 10); j <= to; j++)
			C[i][j] = (t = C[i - 1][j - 1] + C[i - 1][j]) >= mod ? t - mod : t;
	}

	for (int i = 1; i <= n; i++)
	{
		register int t = readIn();
		origin[i] = t < 0 ? t + mod : t;
	}
	st.build(1, n);

	while (m--)
	{
		int type = readIn();
		if (type == 1)
		{
			int l = readIn();
			int r = readIn();
			int x = readIn() + mod;
			if (x >= mod) x -= mod;
			st.add(l, r, x);
		}
		else if (type == 2)
		{
			int l = readIn();
			int r = readIn();
			st.flip(l, r);
		}
		else if (type == 3)
		{
			int l = readIn();
			int r = readIn();
			int k = readIn();
			printOut(st.query(l, r, k));
		}
	}
}

int main()
{
#ifndef LOCAL
	freopen("game.in", "r", stdin);
	freopen("game.out", "w", stdout);
#endif
	run();
	return 0;
}