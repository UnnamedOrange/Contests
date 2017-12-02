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
	std::vector<INT> upSeq;
	std::vector<INT> downSeq;

	cheat3()
	{
		INT status = down;
		for(int i = 1; i <= n; i++)
		{
			if(status == up)
			{
				if(i != n && seq[i - 1] < seq[i] && seq[i] > seq[i + 1])
				{
					upSeq.push_back(seq[i]);
					status = down;
				}
			}
			else
			{
				if((i == 1 && seq[i] < seq[i + 1]) || (i != n && seq[i - 1] > seq[i] && seq[i] < seq[i + 1]))
				{
					downSeq.push_back(seq[i]);
					status = up;
				}
			}
		}
		if(status == up) upSeq.push_back(seq[n]);
		else if(status == down) downSeq.push_back(seq[n]);

		status = down;
		INT ans = 1;
		INT minVal = downSeq[0];
		INT maxVal;
		for(int i = 0; i < upSeq.size(); i++)
		{
			if(status == down)
			{
				if(upSeq[i] - minVal >= k)
				{
					ans++;
					status = up;
					maxVal = upSeq[i];
				}
				else if(minVal > downSeq[i]) minVal = downSeq[i];
			}
			else
			{
				if(maxVal - downSeq[i] >= k)
				{
					ans++;
					status = down;
					minVal = downSeq[i];
					if(upSeq[i] - downSeq[i] >= k)
					{
						ans++;
						status = up;
						maxVal = upSeq[i];
					}
				}
				else if(maxVal < upSeq[i]) maxVal = upSeq[i];
			}
		}
		if(downSeq.size() > upSeq.size())
		{
			if(status == up && maxVal - downSeq.back() >= k)
			{
				ans++;
			}
			else if(status == down && downSeq.back() - minVal >= k)
			{
				ans++;
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
