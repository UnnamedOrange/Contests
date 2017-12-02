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

const INT INF = (~(INT(1) << (sizeof(INT) * 8 - 1)));
const INT maxn = INT(2e6) + 5;
INT n, k;
INT seq[maxn];

#define RunInstance(x) delete new x
struct cheat3
{
	enum
	{
	    up,
	    down
	};

	cheat3()
	{
		INT status = down;
		INT ans = 1;
		INT minVal = seq[1];
		INT maxVal;
		for(int i = 2; i <= n; i++)
		{
			if(status == down)
			{
				if(seq[i] - minVal >= k)
				{
					ans++;
					status = up;
					maxVal = seq[i];
				}
				else if(minVal > seq[i]) minVal = seq[i];
			}
			else
			{
				if(maxVal - seq[i] >= k)
				{
					ans++;
					status = down;
					minVal = seq[i];
				}
				else if(maxVal < seq[i]) maxVal = seq[i];
			}
		}
		cout << ans << endl;
	}
};
struct cheat1
{
	INT f[1005]; //up
	INT g[1005]; //down

	cheat1() : f()
	{
		INT ans = 0;
		for(int i = n; i >= 1; i--)
		{
			f[i] = g[i] = 1;
			for(int j = i + 1; j <= n; j++)
			{
				if(seq[i] - seq[j] >= k)
				{
					f[i] = std::max(f[i], g[j] + 1);
				}
				if(seq[j] - seq[i] >= k)
				{
					g[i] = std::max(g[i], f[j] + 1);
				}
			}
			ans = std::max(ans, g[i]);
		}
		cout << ans << endl;
	}
};

void run()
{
	n = readIn();
	k = readIn();
	for(int i = 1; i <= n; i++)
	{
		seq[i] = readIn();
		if(i != 1 && seq[i] == seq[i - 1])
		{
			i--;
			n--;
		}
	}
	if(n <= 1000) RunInstance(cheat1);
	else RunInstance(cheat3);
}

int main()
{
#ifndef JUDGE
	freopen("wave.in", "r", stdin);
	freopen("wave.out", "w", stdout);
#endif
	run();
	return 0;
}
