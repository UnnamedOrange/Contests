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
typedef long long INT;
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

const INT mod = 1e9 + 7;
const INT maxA = 1e9 + 1;
const INT maxn = 1e5 + 5;
INT n;
struct attribute
{
	INT s;
	INT l;
	INT r;
} ats[maxn];

inline INT Pow(INT temp, INT y)
{
	INT ans = 1;
	while (y)
	{
		if (y & 1) ans = (ans * temp) % mod;
		y >>= 1;
		temp = (temp * temp) % mod;
	}
	return ans;
}
inline INT Inv(INT x)
{
	return Pow(x, mod - 2);
}
const INT inv2 = Inv(2);

class SegTree
{
	struct NODE
	{
		INT sum;
		INT lc;
		INT rc;

		INT a1;
		INT d;
		INT add;
		NODE() : sum(0), a1(0), d(0), add(0), lc(0), rc(0)
		{
		}
	};
	std::vector<NODE> nodes;
	INT g_L, g_R, g_Val, g_A1;

	void pushDown(INT node, INT l, INT r)
	{
		NODE& cnt = nodes[node];
		NODE& L = nodes[nodes[node].lc];
		NODE& R = nodes[nodes[node].rc];

		INT mid = (l + r) >> 1;
		INT lengthL = mid - l + 1;
		INT lengthR = r - mid;

		if (cnt.add)
		{
			L.sum = (L.sum + cnt.add * lengthL % mod) % mod;
			R.sum = (R.sum + cnt.add * lengthR % mod) % mod;
			L.add = (L.add + cnt.add) % mod;
			R.add = (R.add + cnt.add) % mod;
			cnt.add = 0;
		}

		if (cnt.a1 || cnt.d)
		{
			INT a2 = (cnt.a1 + cnt.d * lengthL % mod) % mod;
			INT sumL = (cnt.a1 + cnt.a1 + cnt.d * (lengthL - 1) % mod) * lengthL % mod * inv2 % mod;
			L.sum = (L.sum + sumL) % mod;
			INT sumR = (a2 + a2 + cnt.d * (lengthR - 1) % mod) * lengthR % mod * inv2 % mod;
			R.sum = (R.sum + sumR) % mod;
			L.a1 = (L.a1 + cnt.a1) % mod;
			L.d = (L.d + cnt.d) % mod;
			R.a1 = (R.a1 + a2) % mod;
			R.d = (R.d + cnt.d) % mod;
			cnt.a1 = 0;
			cnt.d = 0;
		}
	}
	INT query_(INT node = 1, INT l = 1, INT r = maxA)
	{
		if (g_L <= l && r <= g_R)
		{
			return nodes[node].sum;
		}
		INT mid = (l + r) >> 1;
		if (!nodes[node].lc)
		{
			nodes[node].lc = nodes.size();
			nodes.push_back(NODE());
		}
		if (!nodes[node].rc)
		{
			nodes[node].rc = nodes.size();
			nodes.push_back(NODE());
		}
		pushDown(node, l, r);

		INT ans = 0;
		if (g_L <= mid) ans = (ans + query_(nodes[node].lc, l, mid)) % mod;
		if (g_R > mid) ans = (ans + query_(nodes[node].rc, mid + 1, r)) % mod;
		return ans;
	}
	void add_(INT node = 1, INT l = 1, INT r = maxA)
	{
		if (g_L <= l && r <= g_R)
		{
			nodes[node].sum = (nodes[node].sum + g_Val * (r - l + 1) % mod) % mod;
			nodes[node].add = (nodes[node].add + g_Val) % mod;
			return;
		}
		INT mid = (l + r) >> 1;
		if (!nodes[node].lc)
		{
			nodes[node].lc = nodes.size();
			nodes.push_back(NODE());
		}
		if (!nodes[node].rc)
		{
			nodes[node].rc = nodes.size();
			nodes.push_back(NODE());
		}
		pushDown(node, l, r);

		if (g_L <= mid) add_(nodes[node].lc, l, mid);
		if (g_R > mid) add_(nodes[node].rc, mid + 1, r);
		nodes[node].sum = (nodes[nodes[node].lc].sum + nodes[nodes[node].rc].sum) % mod;
	}
	void addD_(INT a1, INT node = 1, INT l = 1, INT r = maxA)
	{
		if (g_L <= l && r <= g_R)
		{
			INT length = r - l + 1;
			INT sumD = (a1 + a1 + g_Val * (length - 1) % mod) % mod * length % mod * inv2 % mod;
			nodes[node].sum = (nodes[node].sum + sumD) % mod;
			nodes[node].a1 = (nodes[node].a1 + a1) % mod;
			nodes[node].d = (nodes[node].d + g_Val) % mod;
			return;
		}
		INT mid = (l + r) >> 1;
		if (!nodes[node].lc)
		{
			nodes[node].lc = nodes.size();
			nodes.push_back(NODE());
		}
		if (!nodes[node].rc)
		{
			nodes[node].rc = nodes.size();
			nodes.push_back(NODE());
		}
		pushDown(node, l, r);

		if (g_R <= mid)
		{
			addD_(a1, nodes[node].lc, l, mid);
		}
		else if (g_L > mid)
		{
			addD_(a1, nodes[node].rc, mid + 1, r);
		}
		else
		{
			addD_(a1, nodes[node].lc, l, mid);
			addD_((a1 + g_Val * (mid - std::max(l, g_L) + 1)) % mod,
				nodes[node].rc, mid + 1, r);
		}
		nodes[node].sum = (nodes[nodes[node].lc].sum + nodes[nodes[node].rc].sum) % mod;
	}

public:
	SegTree() : nodes(2)
	{
		nodes.reserve(6000000);
	}

	INT query(INT l, INT r)
	{
		g_L = l;
		g_R = r;
		return query_();
	}
	void add(INT l, INT r, INT val)
	{
		g_L = l;
		g_R = r;
		g_Val = val;
		add_();
	}
	void addD(INT l, INT r, INT d, INT a1)
	{
		g_L = l;
		g_R = r;
		g_Val = d;
		addD_(a1);
	}

	void clear()
	{
		nodes.clear();
		nodes.resize(2);
	}
};

INT contribution[maxn];
INT invLength[maxn];
INT ans;
void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
	{
		ats[i].s = readIn();
		ans = (ans + ats[i].s) % mod;
		ats[i].l = readIn() + 1;
		ats[i].r = readIn() + 1;
		invLength[i] = Inv(ats[i].r - ats[i].l + 1);
	}
	SegTree st;

	for (int i = 1; i <= n; i++)
	{
		contribution[i] = st.query(ats[i].l, ats[i].r);
		st.addD(ats[i].l, ats[i].r, invLength[i], invLength[i]);
		st.add(ats[i].r + 1, maxA, 1);
	}

	st.clear();
	for (int i = n; i >= 1; i--)
	{
		contribution[i] += st.query(ats[i].l, ats[i].r);
		contribution[i] %= mod;
		st.addD(ats[i].l, ats[i].r, invLength[i], 0);
		st.add(ats[i].r + 1, maxA, 1);
	}

	for (int i = 1; i <= n; i++)
	{
		ans = (ans + contribution[i] * ats[i].s % mod * invLength[i] % mod) % mod;
	}
	cout << ans << endl;
}

int main()
{
#ifndef JUDGE
	freopen("sort.in", "r", stdin);
	freopen("sort.out", "w", stdout);
#endif
	run();
	return 0;
}
