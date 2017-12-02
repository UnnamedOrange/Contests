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
inline void printOut(INT a)
{
	if (!a)
	{
		putchar('0');
		putchar('\n');
		return;
	}
	INT length = 0;
	char buffer[10];
	while (a)
	{
		buffer[length++] = a % 10 + '0';
		a /= 10;
	}
	do
	{
		putchar(buffer[--length]);
	} while (length);
	putchar('\n');
}

const INT maxn = 1000005;
INT n, m;
INT origin[maxn];
struct query
{
	INT l, r;
	INT ans;
	query() : ans(-1)
	{
	}
} querys[maxn];
INT mono[maxn];

INT headL[maxn];
INT L[maxn];
INT nextL[maxn];
INT headR[maxn];
INT R[maxn];
INT nextR[maxn];
void addL(INT l, INT to)
{
	L[0]++;
	L[L[0]] = to;
	nextL[L[0]] = headL[l];
	headL[l] = L[0];
}
void addR(INT r, INT to)
{
	R[0]++;
	R[R[0]] = to;
	nextR[R[0]] = headR[r];
	headR[r] = R[0];
}

struct node
{
	INT to;
	INT index;
	INT next;
};
INT headQueryL[maxn];
INT headQueryR[maxn];
INT cQL, cQR;
node queryL[maxn];
node queryR[maxn];
void addQL(INT l, INT r, INT index)
{
	cQL++;
	queryL[cQL].to = r;
	queryL[cQL].index = index;
	queryL[cQL].next = headQueryL[l];
	headQueryL[l] = cQL;
}
void addQR(INT l, INT r, INT index)
{
	cQR++;
	queryR[cQR].to = l;
	queryR[cQR].index = index;
	queryR[cQR].next = headQueryR[r];
	headQueryR[r] = cQR;
}

class BIT
{
	inline static INT lowbit(INT x)
	{
		return x & -x;
	}
	std::vector<INT> bit;

	INT add(INT x, INT val)
	{
		while (x <= n)
		{
			bit[x] += val;
			x += lowbit(x);
		}
	}

	INT query(INT x)
	{
		INT ans = 0;
		while (x > 0)
		{
			ans += bit[x];
			x -= lowbit(x);
		}
		return ans;
	}

public:
	void init()
	{
		bit.resize(n + 1);
	}
	void set(INT x)
	{
		add(x, 1);
	}
	INT query(INT from, INT to)
	{
		return query(to) - query(from - 1);
	}
} bitL, bitR;

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= n; i++)
	{
		origin[i] = readIn();
		while (mono[0] && origin[mono[mono[0]]] < origin[i])
		{
			addR(i, mono[mono[0]--]);
		}
		addL(mono[mono[0]], i);
		mono[++mono[0]] = i;
	}
	for (int i = 1; i <= m; i++)
	{
		querys[i].l = readIn();
		querys[i].r = readIn();
		querys[i].ans = -1;

		addQL(querys[i].l, querys[i].r, i);
		addQR(querys[i].l, querys[i].r, i);
	}

	bitL.init();
	for (int i = headL[0]; i; i = nextL[i])
	{
		bitL.set(L[i]);
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = headQueryL[i]; j; j = queryL[j].next)
		{
			querys[queryL[j].index].ans += bitL.query(i, queryL[j].to);
		}
		for (int j = headL[i]; j; j = nextL[j])
		{
			bitL.set(L[j]);
		}
	}

	bitR.init();
	for (int i = 1; i <= mono[0]; i++)
	{
		bitR.set(mono[i]);
	}
	for (int i = n; i >= 1; i--)
	{
		for (int j = headQueryR[i]; j; j = queryR[j].next)
		{
			querys[queryR[j].index].ans += bitR.query(queryR[j].to, i);
		}
		for (int j = headR[i]; j; j = nextR[j])
		{
			bitR.set(R[j]);
		}
	}

	for (int i = 1; i <= m; i++)
	{
		printOut(querys[i].ans);
	}
}

int main()
{
#ifndef JUDGE
	freopen("trip.in", "r", stdin);
	freopen("trip.out", "w", stdout);
#endif
	run();
	return 0;
}
