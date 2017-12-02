//So big the constant = =, and it is required to specified O2 in the original problem. So I do this.
//Don't ask why I use English = =, I need Unicode QAQ.
#pragma GCC optimize("O2")
#pragma G++ optimize("O2")
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

const INT maxn = INT(1e6) + 5;
INT n, N;
INT A[maxn];
INT disc[maxn];
void discretize()
{
	for(int i = 1; i <= n; i++)
	{
		disc[i] = A[i];
	}
	std::sort(disc + 1, disc + 1 + n);
	N = std::unique(disc + 1, disc + 1 + n) - (disc + 1);
	for(int i = 1; i <= n; i++)
	{
		A[i] = std::lower_bound(disc + 1, disc + 1 + N, A[i]) - disc;
	}
}

const INT INF = ~(1ll << (sizeof(INT) * 8 - 1));
INT ans = INF;
class SegTree
{
#define PARAM INT node = 1, INT l = 1, INT r = N
#define DEF INT mid = (l + r) >> 1; INT lc = node << 1; INT rc = lc | 1;
	struct Node
	{
		INT minPos;
		INT maxPos;
		INT minSub;
		INT contain;

		Node() : minSub(INF >> 1) {}
	} tree[maxn * 4];

	INT g_Pos, g_Val;
	void update(PARAM)
	{
		DEF;
		tree[node].minSub = std::min(tree[lc].minSub, tree[rc].minSub);
		if(tree[lc].maxPos && tree[rc].minPos)
			tree[node].minSub = std::min(tree[node].minSub, disc[tree[rc].minPos] - disc[tree[lc].maxPos]);

		tree[node].minPos = tree[lc].minPos;
		if(!tree[node].minPos) tree[node].minPos = tree[rc].minPos;

		tree[node].maxPos = tree[rc].maxPos;
		if(!tree[node].maxPos) tree[node].maxPos = tree[lc].maxPos;
	}

	void add_(PARAM)
	{
		if(l == r)
		{
			tree[node].contain += g_Val;
			if(tree[node].contain) tree[node].minPos = tree[node].maxPos = l;
			else tree[node].minPos = tree[node].maxPos = 0;

			if(tree[node].contain >= 2) tree[node].minSub = 0;
			else tree[node].minSub = INF;
			return;
		}
		DEF;
		if(g_Pos <= mid) add_(lc, l, mid);
		if(g_Pos > mid) add_(rc, mid + 1, r);
		update(node, l, r);
	}

public:
	INT query()
	{
		return tree[1].minSub;
	}

	void insert(INT x)
	{
		g_Pos = x;
		g_Val = 1;
		add_();
	}
	void erase(INT x)
	{
		g_Pos = x;
		g_Val = -1;
		add_();
	}
} st;

void run()
{
	n = readIn();
	for(int i = 1; i <= n; i++)
	{
		A[i] = readIn();
	}
	discretize();

	INT l = 1;
	st.insert(A[1]);
	for(int i = 2; i <= n; i++)
	{
		st.insert(A[i]);
		INT cntSub = st.query();
		ans = std::min(ans, std::max(cntSub, i - l + 1));
		while(i - l > 1 && cntSub < i - l + 1)
		{
			st.erase(A[l]);
			l++;

			cntSub = st.query();
			ans = std::min(ans, std::max(cntSub, i - l + 1));
		}
	}
	cout << ans << endl;
}

int main()
{
	run();
	return 0;
}
