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
using LL = long long;
using ULL = unsigned long long;
using std::cin;
using std::cout;
using std::endl;
using INT_PUT = LL;
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

const int maxn = int(1e5) + 5;
int n;
struct Triple
{
	int a, b, c;
	bool operator<(const Triple& y) const
	{
		return a < y.a;
	}
} triples[maxn];

struct BIT
{
	int c[maxn];
	static inline int lowbit(int x) { return x & -x; }
	void add(int pos, int val)
	{
		while (pos <= n)
		{
			c[pos] += val;
			pos += lowbit(pos);
		}
	}
	int query(int pos)
	{
		int ret = 0;
		while (pos)
		{
			ret += c[pos];
			pos ^= lowbit(pos);
		}
		return ret;
	}
	void clear(int pos)
	{
		while (pos <= n)
		{
			if (c[pos]) c[pos] = 0;
			else break;
			pos += lowbit(pos);
		}
	}
} bit;

LL ans;
int idx[maxn];
int temp[maxn];
int A[maxn];
void cdq3(int l, int r)
{
	if (l == r)
		return;
	int mid = (l + r) >> 1;
	cdq3(l, mid);
	cdq3(mid + 1, r);

	int i = l, j = mid + 1, k = l;
	while (k <= r)
	{
		if (j > r || (i <= mid && triples[idx[i]].b <= triples[idx[j]].b))
		{
			bit.add(triples[idx[i]].c, 1);
			temp[k++] = idx[i++];
		}
		else
		{
			LL t = bit.query(triples[idx[j]].c);
			ans -= t;
			A[idx[j]] += t;
			temp[k++] = idx[j++];
		}
	}
	for (i = l; i <= mid; i++)
		bit.clear(triples[idx[i]].c);
	for (i = l; i <= r; i++)
		idx[i] = temp[i];
}

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
		triples[i].a = readIn();
	for (int i = 1; i <= n; i++)
		triples[i].b = readIn();
	for (int i = 1; i <= n; i++)
		triples[i].c = readIn();

	ans += n + (LL)n * (n - 1) / 2;
	std::sort(triples + 1, triples + 1 + n);
	for (int i = 1; i <= n; i++)
		idx[i] = i;
	cdq3(1, n);

	LL X = 0;
	for (int i = 1; i <= n; i++)
	{
		LL t = bit.query(triples[i].b - 1);
		X += t * (t - 1) / 2;
		bit.add(triples[i].b, 1);
	}
	std::memset(bit.c, 0, sizeof(bit.c));
	for (int i = 1; i <= n; i++)
	{
		LL t = bit.query(triples[i].c - 1);
		X += t * (t - 1) / 2;
		bit.add(triples[i].c, 1);
	}
	std::memset(bit.c, 0, sizeof(bit.c));
	std::sort(triples + 1, triples + 1 + n,
		[](const Triple& x, const Triple& y)
	{
		return x.b < y.b;
	});
	for (int i = 1; i <= n; i++)
	{
		LL t = bit.query(triples[i].c - 1);
		X += t * (t - 1) / 2;
		bit.add(triples[i].c, 1);
	}
	for (int i = 1; i <= n; i++)
		ans += (LL)A[i] * (A[i] - 1);

	printOut(ans + (LL)n * (n - 1) * (n - 2) / 6 - X);
}

int main()
{
#ifndef LOCAL
	freopen("subset.in", "r", stdin);
	freopen("subset.out", "w", stdout);
#endif
	run();
	return 0;
}