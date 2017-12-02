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

const INT mod = 1e9 + 7;
const INT maxn = 3000;
const INT maxSize = 3005;
INT q;
struct node
{
	INT n;
	INT k;
	INT index;
} nodes[10005];
inline bool comp1(const node& a, const node& b)
{
	return a.k < b.k;
}
inline bool comp2(const node& a, const node& b)
{
	return a.index < b.index;
}

void init()
{
	for (int i = 0; i < q; i++)
	{
		nodes[i].n = readIn();
		nodes[i].k = readIn();
		nodes[i].index = i;
	}
	std::sort(nodes, nodes + q, comp1);
}

void work()
{

}
void cheat()
{
	INT n = readIn();
	INT k = readIn();
	std::vector<INT> permutation(n + 1);
	for (int i = 1; i <= n; i++)
	{
		permutation[i] = i;
	}

	INT ans = 0;
	do
	{
		INT temp = 0;
		for (int i = 1; i <= n; i++)
		{
			if (i > 1 && permutation[i - 1] > permutation[i] || i < n && permutation[i + 1] > permutation[i]) temp++;
		}
		if (temp >= k) ans++;
	} while (std::next_permutation(permutation.begin() + 1, permutation.end()));
	cout << ans << endl;
}
void run()
{
	q = readIn();
	if (q == 1) cheat();
	else work();
}

int main()
{
#ifndef JUDGE
	freopen("permutation.in", "r", stdin);
	freopen("permutation.out", "w", stdout);
#endif
	run();
	return 0;
}
