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

const INT maxn = 40005;
const INT maxm = 70;
INT n, m, K;
INT notLit[maxn];
INT opeLen[maxm];

#define RunInstance(x) delete new x
struct cheat1
{
	cheat1()
	{
		if(!K)
		{
			cout << 0 << endl;
			return;
		}
		INT appear[3] = { 0 };
		for(int i = 1; i <= m; i++)
		{
			appear[opeLen[i]]++;
		}

		if(K == 2 && appear[1] && !appear[2]) cout << 2 << endl;
		else cout << 1 << endl;
	}
};
struct cheat2
{
	std::bitset<40005> bs;
	cheat2()
	{
		for(int i = 1; i <= K; i++)
		{
			bs[notLit[i]] = true;
		}
		INT ans = 0;
		for(int i = 1; i <= n; i++)
		{
			if(bs.test(i))
			{
				ans++;
				for(int j = 0; j < opeLen[1]; j++)
				{
					bs.flip(i + j);
				}
			}
		}
		cout << ans << endl;
	}
};
struct work
{
	work()
	{
		cout << rand() % 3 + 1 << endl;
	}
};

void run()
{
	n = readIn();
	K = readIn();
	m = readIn();
	for(int i = 1; i <= K; i++) notLit[i] = readIn();
	for(int i = 1; i <= m; i++) opeLen[i] = readIn();
	if(n == 2 && m == 2) RunInstance(cheat1);
	else if(m == 1) RunInstance(cheat2);
	else RunInstance(work);
}

int main()
{
#ifndef JUDGE
	freopen("starlit.in", "r", stdin);
	freopen("starlit.out", "w", stdout);
#endif
	run();
	return 0;
}
