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

const int maxn = int(5e4) + 5;
int n, g, r, sum;
int base;
int d[maxn];
LL sufSum[maxn];
int q[maxn];

class SegTree
{
	struct Node
	{
		int minVal;
		Node* ch[2];
		Node() : minVal(-1), ch() {}
	};
	Node* null;
	Node* root;

	Node* alloc(Node* &t)
	{
		if (t == null)
		{
			t = new Node;
			t->ch[0] = t->ch[1] = null;
		}
		return t;
	}
	int g_Pos, g_Val;
	void modify_(Node* &t, int l, int r)
	{
		alloc(t);
		if (l == r)
		{
			t->minVal = g_Val;
			return;
		}
		int mid = (l + r) >> 1;
		if (g_Pos <= mid) modify_(t->ch[0], l, mid);
		else modify_(t->ch[1], mid + 1, r);
		t->minVal = -1;
		if (t->ch[0] != null) t->minVal = t->ch[0]->minVal;
		if (t->ch[1] != null && ~t->ch[1]->minVal) t->minVal = ~t->minVal ? std::min(t->minVal, t->ch[1]->minVal) : t->ch[1]->minVal;
	}
	int g_L, g_R;
	int query_(Node* &t, int l, int r)
	{
		alloc(t);
		if (g_L <= l && r <= g_R)
		{
			return t->minVal;
		}
		int mid = (l + r) >> 1;
		int ret = -1;
		int temp;
		if (g_L <= mid) ret = query_(t->ch[0], l, mid);
		if (g_R > mid)
		{
			if (~ret)
			{
				if (~(temp = query_(t->ch[1], mid + 1, r)))
					ret = std::min(ret, temp);
			}
			else
				ret = query_(t->ch[1], mid + 1, r);
		}
		return ret;
	}

public:
	SegTree()
	{
		null = new Node;
		null->ch[0] = null->ch[1] = null;
		root = null;
	}
	void modify(int pos, int val)
	{
		g_Pos = pos;
		g_Val = val;
		modify_(root, 0, sum - 1);
	}
	int query(int l, int r)
	{
		g_L = l;
		g_R = r;
		return query_(root, 0, sum - 1);
	}
} st;
LL f[maxn];

int queryMin(int delta)
{
	int min;
	if (!delta)
		min = st.query(g, sum - 1);
	else if (delta >= r)
		min = st.query(delta - r, delta - 1);
	else
	{
		min = st.query(delta + g, sum - 1);
		int temp;
		if (~min)
		{
			if (~(temp = st.query(0, delta - 1)))
				min = std::min(min, temp);
		}
		else
			min = st.query(0, delta);
	}
	return min;
}

void run()
{
	n = readIn();
	g = readIn();
	r = readIn();
	sum = g + r;
	base = readIn();
	for (int i = 1; i <= n; i++)
		d[i] = readIn();
	q[0] = readIn();
	for (int i = 1; i <= q[0]; i++)
		q[i] = readIn();

	sufSum[n + 1] = 0;
	for (int i = n; i; i--)
		sufSum[i] = sufSum[i + 1] + d[i];

	int delta = 0;
	f[n + 1] = 0;
	for (int i = n; i; i--)
	{
		delta = (((LL)delta - d[i]) % sum + sum) % sum;
		int min = queryMin(delta);
		if (min == -1)
			f[i] = sufSum[i];
		else
			f[i] = sufSum[i] - sufSum[min] + (sum - (sufSum[i] - sufSum[min]) % sum) + f[min];
		st.modify(delta, i);
	}
	delta = ((delta - base) % sum + sum) % sum;
	for (int i = 1; i <= q[0]; i++)
	{
		int min = queryMin((((LL)delta - q[i]) % sum + sum) % sum);
		LL ans;
		if (min == -1)
			ans = sufSum[1] + q[i] + base;
		else
			ans = q[i] + base + sufSum[1] - sufSum[min] + (sum - (q[i] + base + sufSum[1] - sufSum[min]) % sum) + f[min];
		printOut(ans);
	}
}

int main()
{
#ifndef LOCAL
	freopen("light.in", "r", stdin);
	freopen("light.out", "w", stdout);
#endif
	run();
	return 0;
}