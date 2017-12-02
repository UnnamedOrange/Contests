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
inline void printOut(INT x)
{
	if(!x)
	{
		putchar('0');
		putchar('\n');
		return;
	}
	char buffer[10];
	INT length = 0;
	while(x)
	{
		buffer[length++] = x % 10 + '0';
		x /= 10;
	}
	do
	{
		putchar(buffer[--length]);
	}
	while(length);
	putchar('\n');
}

const INT maxn = 100005;
INT n, m;
std::vector<bool> isGood(1000001, true);

void init()
{
	const INT maxx = 1000000;
	std::vector<INT> prime;
	prime.reserve(78501);
	for(int i = 2; i <= maxx; i++)
	{
		if(isGood[i]) prime.push_back(i);
		for(int j = 0; j < prime.size(); j++)
		{
			if(i * prime[j] > maxx) break;
			isGood[i * prime[j]] = false;
			if(i % prime[j] == 0) break;
		}
	}

	isGood[6] = true;
	for(int i = 1; i <= maxx; i <<= 1)
	{
		isGood[i] = true;
	}
}

#define RunInstance(x) delete new x
struct work
{
	class SegTree
	{
		struct Node
		{
			INT val;
			INT maxVal;

			Node() : val() {}
		} nodes[262150];
#define PARAM INT node, INT l, INT r
#define DEF INT mid = (l + r) >> 1; INT lc = node << 1; INT rc = lc | 1
		INT g_Pos, g_Val, g_L, g_R, g_Mod;

		void update(PARAM)
		{
			DEF;
			nodes[node].val = nodes[lc].val + nodes[rc].val;
			nodes[node].maxVal = std::max(nodes[lc].maxVal, nodes[rc].maxVal);
		}
		void modify(PARAM)
		{
			if(l == r)
			{
				nodes[node].val = isGood[g_Val];
				nodes[node].maxVal = g_Val;
				return;
			}
			DEF;
			if(g_Pos <= mid) modify(lc, l, mid);
			if(g_Pos > mid) modify(rc, mid + 1, r);
			update(node, l, r);
		}
		INT query(PARAM)
		{
			if(g_L <= l && r <= g_R)
			{
				return nodes[node].val;
			}
			DEF;
			INT ans = 0;
			if(g_L <= mid) ans += query(lc, l, mid);
			if(g_R > mid) ans += query(rc, mid + 1, r);
			return ans;
		}

		void deepen(PARAM)
		{
			if(l == r)
			{
				nodes[node].maxVal %= g_Mod;
				nodes[node].val = isGood[nodes[node].maxVal];
				return;
			}
			if(nodes[node].maxVal < g_Mod) return;
			DEF;
			deepen(lc, l, mid);
			deepen(rc, mid + 1, r);
			update(node, l, r);
		}
		void mod_(PARAM)
		{
			if(g_L <= l && r <= g_R)
			{
				deepen(node, l, r);
				return;
			}
			DEF;
			if(g_L <= mid) mod_(lc, l, mid);
			if(g_R > mid) mod_(rc, mid + 1, r);
			update(node, l, r);
		}

		void build(PARAM)
		{
			if(l == r)
			{
				nodes[node].maxVal = readIn();
				nodes[node].val = isGood[nodes[node].maxVal];
				return;
			}
			DEF;
			build(lc, l, mid);
			build(rc, mid + 1, r);
			update(node, l, r);
		}

	public:
		void modify(INT pos, INT val)
		{
			g_Pos = pos;
			g_Val = val;
			modify(1, 1, n);
		}
		INT query(INT l, INT r)
		{
			g_L = l;
			g_R = r;
			return query(1, 1, n);
		}
		void mod(INT l, INT r, INT Mod)
		{
			g_L = l;
			g_R = r;
			g_Mod = Mod;
			mod_(1, 1, n);
		}

		void build()
		{
			build(1, 1, n);
		}
	} st;

	work()
	{
		st.build();
		while(m--)
		{
			INT ins = readIn();
			if(ins == 1)
			{
				INT l = readIn();
				INT r = readIn();
				printOut(st.query(l, r));
			}
			else if(ins == 2)
			{
				INT l = readIn();
				INT r = readIn();
				INT mod = readIn();
				st.mod(l, r, mod);
			}
			else if(ins == 3)
			{
				INT pos = readIn();
				INT val = readIn();
				st.modify(pos, val);
			}
		}
	}
};
struct cheat1
{
	INT num[1005];

	cheat1()
	{
		for(int i = 1; i <= n; i++)
		{
			num[i] = readIn();
		}
		while(m--)
		{
			INT ins = readIn();
			if(ins == 1)
			{
				INT l = readIn();
				INT r = readIn();
				INT ans = 0;
				for(int i = l; i <= r; i++)
				{
					ans += isGood[num[i]];
				}
				printOut(ans);
			}
			else if(ins == 2)
			{
				INT l = readIn();
				INT r = readIn();
				INT mod = readIn();
				for(int i = l; i <= r; i++)
				{
					num[i] %= mod;
				}
			}
			else if(ins == 3)
			{
				INT pos = readIn();
				INT val = readIn();
				num[pos] = val;
			}
		}
	}
};

void run()
{
	init();
	n = readIn();
	m = readIn();
//	if(n <= 1000 && m <= 1000) RunInstance(cheat1);
//	else
	RunInstance(work);
}

int main()
{
#ifndef JUDGE
	freopen("good.in", "r", stdin);
	freopen("good.out", "w", stdout);
#endif
	run();
	return 0;
}
