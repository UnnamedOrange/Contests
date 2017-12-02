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

const INT INF = ~(INT(1) << (sizeof(INT) * 8 - 1));
const INT maxn = 100005;
INT n;
INT a[maxn];

#define RunInstance(x) delete new x
struct work
{
	class SegTree
	{
		struct Node
		{
			INT minVal;
			INT inQ;

			Node() : minVal(INF), inQ() {}
			bool operator< (const Node& b) const
			{
				return minVal < b.minVal;
			}
		} nodes[262150];
#define PARAM INT node, INT l, INT r
#define DEF INT mid = (l + r) >> 1; INT lc = node << 1; INT rc = lc | 1;

		bool bErase;
		INT g_Pos;
		INT g_InQ;
		INT g_L, g_R;

		void insert(PARAM)
		{
			if(l == r)
			{
				if(bErase)
				{
					nodes[node].minVal = INF;
					nodes[node].inQ = 0;
				}
				else
				{
					nodes[node].minVal = g_Pos;
					nodes[node].inQ = g_InQ;
				}
				return;
			}
			DEF;
			if(g_Pos <= mid) insert(lc, l, mid);
			if(g_Pos > mid) insert(rc, mid + 1, r);
			nodes[node] = std::min(nodes[lc], nodes[rc]);
		}
		INT query(PARAM)
		{
			if(g_L <= l && r <= g_R)
			{
				return nodes[node].inQ;
			}
			DEF;
			INT ans = 0;
			if(g_L <= mid)
			{
				ans = query(lc, l, mid);
				if(ans) return ans;
			}
			if(g_R > mid)
			{
				ans = query(rc, mid + 1, r);
			}
			return ans;
		}

	public:
		void insert(INT val, INT inQ)
		{
			g_Pos = val;
			g_InQ = inQ;
			bErase = false;
			insert(1, 1, n);
		}
		void erase(INT val)
		{
			g_Pos = val;
			bErase = true;
			insert(1, 1, n);
		}
		INT query(INT val)
		{
			g_L = val + 1;
			g_R = n;
			return query(1, 1, n);
		}
	};

	INT q[maxn];

	work() : q()
	{
		SegTree& st = *(new SegTree);
		INT ans = 1;
		q[1] = a[1];
		st.insert(a[1], 1);
		for(int i = 2; i <= n; i++)
		{
			INT pos = st.query(a[i]);
			if(!pos)
			{
				ans++;
				q[ans] = a[i];
				st.insert(a[i], ans);
			}
			else
			{
				st.erase(q[pos]);
				st.insert(a[i], pos);
				q[pos] = a[i];
			}
		}
		cout << ans << endl;
	}
};
struct cheat
{
	std::vector<std::vector<INT> > edges;

	bool vis[2005];
	INT linkX[2005];
	bool augment(INT from)
	{
		for(int i = 0; i < edges[from].size(); i++)
		{
			INT to = edges[from][i];
			if(vis[to]) continue;
			vis[to] = true;
			if(!linkX[to] || augment(linkX[to]))
			{
				linkX[to] = from;
				return true;
			}
		}
		return false;
	}
	cheat() : edges(n + 1), linkX()
	{
		for(int i = 1; i <= n; i++)
		{
			for(int j = i + 1; j <= n; j++)
			{
				if(a[i] > a[j]) edges[i].push_back(j);
			}
		}

		INT ans = n;
		for(int i = 1; i <= n; i++)
		{
			memset(vis, 0, sizeof(bool) * (n + 1));
			ans -= augment(i);
		}
		cout << ans << endl;
	}
};

void run()
{
	n = readIn();
	for(int i = 1; i <= n; i++)
	{
		a[i] = readIn();
	}
	if(n <= 2000) RunInstance(cheat);
	else RunInstance(work);
}

int main()
{
#ifndef JUDGE
	freopen("manage.in", "r", stdin);
	freopen("manage.out", "w", stdout);
#endif
	run();
	return 0;
}
