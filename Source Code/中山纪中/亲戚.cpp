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
const INT maxn = 2e5 + 5;
INT n;
INT parent[maxn];

INT count_;
INT head[maxn];
INT son[maxn];
INT next[maxn];

INT size[maxn];
INT f[maxn];

INT Inv(INT x)
{
	INT y = mod - 2;
	INT ans = 1;
	while (y)
	{
		if (y & 1) ans = ans * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return ans;
}
INT C(INT up, INT down)
{
	up = std::min(up, down - up);

	INT Mul = 1;
	INT Div = 1;
	for (int i = down - up + 1; i <= down; i++)
	{
		Mul = Mul * i % mod;
	}
	for (int i = 2; i <= up; i++)
	{
		Div = Div * i % mod;
	}
	return Mul * Inv(Div) % mod;
}
INT getInsert(INT x, INT y)
{
	return C(x, x + y);
}

void dfs(INT node = 0)
{
	f[node] = 1;
	for (int i = head[node]; i; i = next[i])
	{
		INT to = son[i];
		dfs(to);

		f[node] = f[node] * f[to] % mod * getInsert(size[node], size[to]) % mod;
		size[node] += size[to];
	}
	size[node]++;
}

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
	{
		parent[i] = readIn();
		count_++;
		son[count_] = i;
		next[count_] = head[parent[i]];
		head[parent[i]] = count_;
	}

	dfs();
	cout << f[0] << endl;
}

int main()
{
	run();
	return 0;
}
