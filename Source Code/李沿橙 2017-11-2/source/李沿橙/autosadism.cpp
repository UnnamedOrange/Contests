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
typedef int INT;
using std::cin;
using std::cout;
using std::endl;
INT readIn()
{
	INT a = 0;
	bool minus = false;
	char ch = getchar();
	while (!(ch == '-' || (ch >= '0' && ch <= '9'))) ch = getchar();
	if (ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		a = a * 10 + (ch - '0');
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}
void printOut(INT x)
{
	char buffer[20];
	bool minus = x < 0;
	INT length = 0;
	if (minus) x = -x;
	do
	{
		buffer[length++] = x % 10 + '0';
		x /= 10;
	} while (x);
	if (minus) buffer[length++] = '-';
	do
	{
		putchar(buffer[--length]);
	} while (length);
}

const INT maxp = INT(1e7) + 5;
const INT maxn = INT(1e5) + 5;
INT n;
INT p[maxn];

struct DS
{
	INT parent[maxn];
	DS() {}
	DS(INT size)
	{
		clear(size);
	}
	void clear(INT size)
	{
		for (int i = 1; i <= size; i++) parent[i] = i;
	}
	INT find(INT x)
	{
		if (x == parent[x]) return x;
		return parent[x] = find(parent[x]);
	}
	bool unite(INT x, INT y)
	{
		INT px = find(x);
		INT py = find(y);
		if (px == py) return false;
		parent[py] = px;
		return true;
	}
};

long long ans;
INT mp;
INT ar[maxp];
bool vis[maxn];
DS ds;

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
		p[i] = readIn();
	std::sort(p + 1, p + 1 + n);
	n = std::unique(p + 1, p + 1 + n) - (p + 1);

	ds.clear(n);
	for (int i = 1; i <= n; i++) ar[p[i]] = i;
	mp = p[n];

	INT st = 1;
	INT nEdge = 0;
	for (int i = 0; i <= mp; i++)
	{
		while (st <= n && p[st] <= i) st++;
		for (int j = st; j <= n; j++)
		{
			if (vis[j]) continue;
			INT val;
			INT pre = 0;
			for (int k = 2 - !!i; (val = p[j] * k + i) <= mp; k++)
			{
				INT pos = ar[val];
				if (pos && pos != pre)
				{
					if (ds.unite(j, pos))
					{
						nEdge++;
						ans += i;
						if (nEdge == n - 1)
						{
							cout << ans << endl;
							return;
						}
					}
					pre = pos;
					if (!i) vis[pos] = true;
				}
			}
		}
	}
}

int main()
{
#ifndef JUDGE
	freopen("autosadism.in", "r", stdin);
	freopen("autosadism.out", "w", stdout);
#endif
	run();
	return 0;
}
