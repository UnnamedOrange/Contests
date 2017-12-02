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

const INT INF = ~(INT(1) << (sizeof(INT) * 8 - 1));
const INT maxn = INT(1e6) + 5;
const INT maxk = 21;
INT n, k;
INT w[maxn], d[maxn], num[maxn];

struct deque : std::deque<INT>
{
	INT& front2()
	{
		return std::deque<INT>::operator[](1);
	}
	INT& back2()
	{
		return std::deque<INT>::operator[](std::deque<INT>::size() - 2);
	}
};

INT pre[maxn][maxk];
INT f[maxn][maxk];
INT dp(INT stage, INT s, INT param)
{
	return f[s][param - 1] + num[stage] - num[s] - d[s + 1] * (w[stage] - w[s]);
}

#define RunInstance(x) delete new x
struct work
{
	INT x(INT s, INT param = 0)
	{
		return d[s + 1];
	}
	INT y(INT s, INT param)
	{
		return f[s][param] - num[s + 1] + d[s + 1] * w[s + 1];
	}
	INT up(INT s1, INT s2, INT param)
	{
		return y(s1, param) - y(s2, param);
	}
	INT down(INT s1, INT s2, INT param = 0)
	{
		return x(s1) - x(s2);
	}

	deque q[maxk];
	bool lt(INT up1, INT down1, INT up2, INT down2)
	{
		return up1 * down2 < down1 * up2;
	}
	std::vector<INT> ans;

	work()
	{
		f[0][0] = 0;
		q[0].push_back(0);
		for(int i = 1; i <= n; i++)
		{
			f[i][0] = num[i];
			for(int j = std::min(INT(i - 1), INT(k)); j >= 1; j--)
			{
				while(q[j - 1].size() > 1 && lt(
				            up(q[j - 1].front2(), q[j - 1].front(), j - 1),
				            down(q[j - 1].front2(), q[j - 1].front()),

				            w[i], 1
				        ))
				{
					q[j - 1].pop_front();
				}

				INT strategy = q[j - 1].front();
				pre[i][j] = strategy;
				f[i][j] = dp(i, strategy, j);

				while(q[j].size() > 1 && lt(
				            up(i, q[j].back(), j),
				            down(i, q[j].back()),

				            up(q[j].back(), q[j].back2(), j),
				            down(q[j].back(), q[j].back2())
				        ))
				{
					q[j].pop_back();
				}
				q[j].push_back(i);
			}

			while(q[0].size() > 1 && lt(
			            up(i, q[0].back(), 0),
			            down(i, q[0].back()),

			            up(q[0].back(), q[0].back2(), 0),
			            down(q[0].back(), q[0].back2())
			        ))
			{
				q[0].pop_back();
			}
			q[0].push_back(i);
		}
		cout << f[n][k] << endl;
		INT pos = pre[n][k];
		while(k)
		{
			cout << n - pos - 1 << " ";
			k--;
			pos = pre[pos][k];
		}
		cout << endl;
	}
};
struct cheat
{
	cheat()
	{
		f[1][0] = num[1];
		f[1][1] = 0;
		for(int i = 2; i <= n; i++)
		{
			f[i][0] = num[i];
			for(int j = 1; j <= k; j++)
			{
				f[i][j] = INF;
				for(int l = 1; l < i; l++)
				{
					INT val = dp(i, l, j);
					if(val < f[i][j])
					{
						pre[i][j] = l;
						f[i][j] = val;
					}
				}
			}
		}
		cout << f[n][k] << endl;
		INT pos = pre[n][k];
		while(k)
		{
			cout << n - pos - 1 << " ";
			k--;
			pos = pre[pos][k];
		}
		cout << endl;
	}
};

void run()
{
	n = readIn();
	k = readIn();
	for(int i = 0; i < n; i++)
	{
		w[n - i] = readIn();
		d[n - i] = readIn();
	}
	for(int i = 1; i <= n; i++)
	{
		d[i] += d[i - 1];
	}
	for(int i = 1; i <= n; i++)
	{
		num[i] = w[i] * d[i];
	}
	for(int i = 1; i <= n; i++)
	{
		w[i] += w[i - 1];
		num[i] += num[i - 1];
	}

	if(n <= 1000) RunInstance(cheat);
	else RunInstance(work);
}

int main()
{
#ifndef JUDGE
	freopen("life.in", "r", stdin);
	freopen("life.out", "w", stdout);
#endif
	run();
	return 0;
}
