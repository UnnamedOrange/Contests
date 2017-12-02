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

const INT maxn = 4e5 + 5;
const INT LOG = 32;
INT n, m;
INT origin[maxn >> 1];
INT minx = -1;
INT maxx = 1e9 + 5;
struct PST
{
	struct NODE
	{
		INT l, r;
		NODE *lc, *rc;
		INT size;
		NODE() {}
		NODE(INT l, INT r, NODE* lc, NODE* rc) : l(l), r(r), lc(lc), rc(rc), size(lc->size + rc->size) {}
		NODE(INT l, INT r, NODE* lc, NODE* rc, INT size) : l(l), r(r), lc(lc), rc(rc), size(size) {}
	} *roots[maxn], *null, pool[maxn * LOG], *crt;

	INT N;

	PST() : N(0)
	{
		null = new NODE(-1, -1, NULL, NULL, 0);
		null->lc = null->rc = null;
		crt = pool;
		roots[0] = null;
	}

	NODE* insert(NODE* pre, INT l, INT r, INT x)
	{
		if (x > r || x < l) return pre;
		else if (l == r)
			return new(crt++) NODE(l, r, null, null, pre->size + 1);
		else
		{
			INT mid = l + (r - l) / 2;
			return new(crt++) NODE(l, r, insert(pre->lc, l, mid, x), insert(pre->rc, mid + 1, r, x));
		}
	}
	void insert(INT x)
	{
		N++;
		roots[N] = insert(roots[N - 1], minx, maxx, x);
	}
	void pop_back()
	{
		N--;
	}

	INT query(INT ql, INT qr, INT k)
	{
		INT l = minx, r = maxx;
		NODE* tl = roots[ql - 1];
		NODE* tr = roots[qr];

		while (l != r)
		{
			INT mid = l + (r - l) / 2;
			INT contain = tr->lc->size - tl->lc->size;

			if (k <= contain)
			{
				tl = tl->lc;
				tr = tr->lc;

				r = mid;
			}
			else
			{
				k -= contain;

				tl = tl->rc;
				tr = tr->rc;

				l = mid + 1;
			}
		}
		return l;
	}
} pst;

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= n; i++)
	{
		origin[i] = readIn();
	}
	for (int i = n; i >= 1; i--)
	{
		pst.insert(origin[i]);
	}

	while (m--)
	{
		INT ins = readIn();
		if (ins == 1)
		{
			pst.pop_back();
		}
		else if (ins == 2)
		{
			pst.insert(readIn());
		}
		else
		{
			INT from = readIn();
			INT to = readIn();
			INT k = readIn();
			printf("%d\n", pst.query(pst.N - to + 1, pst.N - from + 1, k));
		}
	}
}

int main()
{
#ifndef JUDGE
	freopen("news.in", "r", stdin);
	freopen("news.out", "w", stdout);
#endif
	run();
	return 0;
}
