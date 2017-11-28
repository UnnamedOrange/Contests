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

const INT INF = (~(INT(1) << (sizeof(INT) * 8 - 1)));
const INT maxn = INT(2e5) + 5;
INT n;
INT y[maxn];
INT c[maxn];

#define RunInstance(x) delete new x
struct work
{
	class SegTree
	{
		struct Node
		{
			INT minf;
			
			INT max;
			
		} nodes[262150];

#define PARAM INT node, INT l, INT r
#define DEF INT mid = (l + r) >> 1; INT lc = node << 1; INT rc = lc | 1

		INT g_Pos, g_L, g_R;
		
		void update(PARAM)
		{
			DEF;
			nodes[node].max = std::max(nodes[lc].max, nodes[rc].max);
		}
		
		void modify_
		
		INT query_(PARAM, INT push)
		{
			if(g_L <= l && r <= g_R)
			{
				return nodes[node].minf;
			}
			DEF;
			INT rmax = nodes[rc].max;
			INT ret = INF;
			if(rmax > push)
			{
				if(l <= mid) ret = std::min(ret, query_(lc, l, mid, rmax));
				if(r > mid) ret = std::min(ret, query_(rc, mid + 1, r, push));
			}
			else
			{
				if(l <= mid) ret = std::min(ret, query_(lc, l, mid, push));
			}
			return ret;
		}

	public:
		SegTree()
		{

		}
	};

	INT x[maxn];

	work()
	{
		for(int i = 1; i <= n; i++) x[y[i]] = i;
		
	}
};
//Oriented to 20% data
struct cheat2
{
	INT f[maxn];

	cheat2()
	{
		memset(f, 0x3f, sizeof(f));
		f[0] = 0;
		f[1] = c[1];
		y[n + 1] = n + 1;
		for (int i = 2; i <= n + 1; i++)
		{
			for (int j = std::max(0, i - 15); j < i; j++)
			{
				if (y[j] > y[i]) continue;
				bool bOk = true;
				for (int k = j + 1; k < i; k++)
				{
					if (y[k] > y[j] && y[k] < y[i])
					{
						bOk = false;
						break;
					}
				}
				if (bOk)
				{
					f[i] = std::min(f[i], f[j] + c[i]);
				}
			}
		}
		cout << std::min(f[n], f[n + 1]) << endl;
	}
};
//Brute: normal DP, O(n ^ 2)
struct cheat
{
	static const INT maxN = 1005;
	INT f[maxN];

	cheat()
	{
		memset(f, 0x3f, sizeof(f));
		f[0] = 0;
		f[1] = c[1];
		y[n + 1] = n + 1;
		for (int i = 2; i <= n + 1; i++)
		{
			for (int j = 0; j < i; j++)
			{
				if (y[j] > y[i]) continue;
				bool bOk = true;
				for (int k = j + 1; k < i; k++)
				{
					if (y[k] > y[j] && y[k] < y[i])
					{
						bOk = false;
						break;
					}
				}
				if (bOk)
				{
					f[i] = std::min(f[i], f[j] + c[i]);
				}
			}
		}
		cout << std::min(f[n], f[n + 1]) << endl;
	}
};

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
	{
		y[i] = readIn();
	}
	for (int i = 1; i <= n; i++)
	{
		c[i] = readIn();
	}

	if (n <= 1000) RunInstance(cheat);
	else RunInstance(work);
}

int main()
{
#ifndef JUDGE
	freopen("knows.in", "r", stdin);
	freopen("knows.out", "w", stdout);
#endif
	run();
	return 0;
}
