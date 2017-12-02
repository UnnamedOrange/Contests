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
	bool minus = false;
	INT a = 0;
	char ch = getchar();
	while(!(ch == '-' || ch >= '0' && ch <= '9')) ch = getchar();
	if(ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9')
	{
		a *= 10;
		a += ch;
		a -= '0';
		ch = getchar();
	}
	if(minus) a = -a;
	return a;
}

const INT maxn = 100005;
const INT maxh = 1000005;
INT n;
INT ans;

class SegTre
{
	std::vector<INT> tree;
	INT g_L, g_R, g_Pos, g_Val;

	void set_(INT node = 1, INT l = 1, INT r = maxh)
	{
		if(l == r)
		{
			tree[node] = std::max(tree[node], g_Val);
			return;
		}
		INT mid = (l + r) >> 1;
		INT lc = node << 1;
		INT rc = lc | 1;
		if(g_Pos <= mid) set_(lc, l, mid);
		if(g_Pos > mid) set_(rc, mid + 1, r);
		tree[node] = std::max(tree[lc], tree[rc]);
	}

	INT query_(INT node = 1, INT l = 1, INT r = maxh)
	{
		if(g_L <= l && r <= g_R)
		{
			return tree[node];
		}
		INT mid = (l + r) >> 1;
		INT lc = node << 1;
		INT rc = lc | 1;
		INT ret = 0;
		if(g_L <= mid) ret = std::max(ret, query_(lc, l, mid));
		if(g_R > mid) ret = std::max(ret, query_(rc, mid + 1, r));
		return ret;
	}

public:
	SegTre() : tree(2097200)
	{
	}

	void set(INT pos, INT val)
	{
		g_Pos = pos;
		g_Val = val;
		set_();
	}
	INT query(INT l = 1, INT r = maxh)
	{
		g_L = l;
		g_R = r;
		return query_();
	}
};

void SuperDP()
{
	SegTre f; //大于
	SegTre g; //小于
	for(int i = 1; i <= n; i++)
	{
		INT height = readIn() + 2;
		INT valF = f.query(1, height - 1) + 1;
		INT valG = g.query(height + 1) + 1;
		ans = std::max(ans, std::max(valF, valG));
		f.set(height, valG);
		g.set(height, valF);
	}
}

void run()
{
	n = readIn();
	ans = 1;

	SuperDP();
	cout << ans << endl;
}

int main()
{
	run();
	return 0;
}
