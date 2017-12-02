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

const INT maxn = 100005;
const INT maxk = 23;
INT n, k;
INT m;
INT seq[maxn];
INT disc[maxn];
void makeDisc()
{
	for(int i = 1; i <= n; i++)
	{
		disc[i] = seq[i];
	}
	std::sort(disc + 1, disc + 1 + n);
	m = std::unique(disc + 1, disc + 1 + n) - (disc + 1);
	for(int i = 1; i <= n; i++)
	{
		seq[i] = std::lower_bound(disc + 1, disc + 1 + m, seq[i]) - disc;
	}
}

INT refCount[maxn];
bool inc(INT x)
{
	refCount[seq[x]]++;
	return refCount[seq[x]] == 1;
}
bool dec(INT x)
{
	refCount[seq[x]]--;
	return !refCount[seq[x]];
}
INT calc()
{
	INT ret = 1;
	INT r = 1;
	INT nDiff = 0;
	for(int l = 1; l <= n; l++)
	{
		while(r <= n && (refCount[seq[r]] || nDiff < k + 1))
		{
			nDiff += inc(r);
			r++;
		}
		ret = std::max(ret, refCount[seq[l]]);

		nDiff -= dec(l);
	}
	return ret;
}

void run()
{
	n = readIn();
	k = readIn();
	for(int i = 1; i <= n; i++)
	{
		seq[i] = readIn();
	}
	makeDisc();

	cout << calc() << endl;
}

int main()
{
#ifndef JUDGE
	freopen("line.in", "r", stdin);
	freopen("line.out", "w", stdout);
#endif
	run();
	return 0;
}
