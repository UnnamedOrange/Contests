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

const INT maxn = 1000005;
const INT maxm = 205;
INT n, m, h, k;
struct Sum
{
	static const INT limit = 1000001;
	INT s[maxn];

	Sum() : s() {}
	void add(INT x)
	{
		s[x]++;
	}
	void init()
	{
		for(int i = 1; i <= limit; i++)
		{
			s[i] += s[i - 1];
		}
	}
	INT query(INT x)
	{
		return s[x];
	}
	INT query(INT x, INT y)
	{
		if(x > y) return 0;
		return query(y) - query(x - 1);
	}
} s;
struct area
{
	INT l, r;
	void read()
	{
		l = readIn() + 1;
		r = readIn() + 1;
	}

	bool operator< (const area& b) const
	{
		if(r != b.r) return r < b.r;
		return l > b.l;
	}
} areas[maxm];

INT f[maxm][maxm];

void run()
{
	n = readIn();
	m = readIn();
	h = readIn();
	k = readIn();
	for(int i = 1; i <= n; i++)
	{
		INT height = readIn();
		if(height < h) continue;
		s.add(height - h + 1);
	}
	s.init();

	for(int i = 1; i <= m; i++)
	{
		areas[i].read();
	}
	std::sort(areas + 1, areas + 1 + m);
	
	//题目错了：只能踩着板凳摘，不能不踩板凳 
	//f[0][0] = s.query(1, 1);
	INT ans = 0;
	for(int i = 1; i <= m; i++)
	{
		INT cover = s.query(areas[i].l, areas[i].r);
		f[i][1] = cover;
		if(1 <= k) ans = std::max(ans, f[i][1]);
		for(int j = 1; j < i; j++)
		{
			INT contribution = cover - s.query(areas[i].l, areas[j].r);
			for(int sel = 2; sel <= std::min(j + 1, k); sel++)
			{
				f[i][sel] = std::max(f[i][sel], f[j][sel - 1] + contribution);
				ans = std::max(ans, f[i][sel]);
			}
		}
	}
	cout << ans << endl;
}

int main()
{
#ifndef JUDGE
	freopen("apple.in", "r", stdin);
	freopen("apple.out", "w", stdout);
#endif
	run();
	return 0;
}
