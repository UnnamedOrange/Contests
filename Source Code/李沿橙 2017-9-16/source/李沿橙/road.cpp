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

const INT maxn = 405;
const INT maxm = 50005;
INT n, m;
INT wG, wS;
struct Edge
{
	INT from;
	INT to;
	INT g;
	INT s;

	void read()
	{
		from = readIn();
		to = readIn();
		g = readIn() * wG;
		s = readIn() * wS;
	}

	bool operator< (const Edge& b) const
	{
		return g < b.g;
	}
} edges[maxm];

class DS
{
	INT size;
	std::vector<INT> parent;

	INT find(INT x)
	{
		if(x == parent[x]) return x;
		return parent[x] = find(parent[x]);
	}

public:
	DS(INT size) : size(size), parent(size + 1)
	{
		clear();
	}

	void clear()
	{
		for(int i = 1; i <= n; i++)
		{
			parent[i] = i;
		}
	}

	void unite(INT x, INT y)
	{
		parent[find(y)] = find(x);
	}

	bool judge(INT x, INT y)
	{
		return find(x) == find(y);
	}
};

INT x[maxm], y[maxm];

void run()
{
	n = readIn();
	m = readIn();
	wG = readIn();
	wS = readIn();
	for(int i = 1; i <= m; i++)
	{
		edges[i].read();
	}
	std::sort(edges + 1, edges + 1 + m);

	INT ans = -1;
	INT *es, *sel;
	es = x;
	sel = y;
	DS ds(n);
	for(int i = 1; i <= m; i++)
	{
		if(ans != -1 && edges[i].g + edges[i].s > ans) continue;
		for(int j = es[0]; j >= 1; j--)
		{
			if(edges[es[j]].s > edges[i].s)
			{
				es[j + 1] = es[j];
			}
			else
			{
				es[j + 1] = i;
				break;
			}
		}
		if(es[1] == es[2]) es[1] = i;
		es[0]++;
		
		ds.clear();
		sel[0] = 0;
		INT maxSel = 0;
		for(int j = 1; j <= es[0]; j++)
		{
			Edge& e = edges[es[j]];
			if(ds.judge(e.from, e.to)) continue;
			ds.unite(e.from, e.to);
			sel[++sel[0]] = es[j];
			maxSel = std::max(maxSel, es[j]);

			if(sel[0] == n - 1) break;
		}
		if(sel[0] == n - 1 && (ans == -1 || edges[maxSel].g + edges[sel[sel[0]]].s < ans))
		{
			ans = edges[maxSel].g + edges[sel[sel[0]]].s;
		}
		std::swap(es, sel);
	}
	cout << ans << endl;
}

int main()
{
	run();
	return 0;
}
