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
	while(!(ch == '-' || ch >= '0' && ch <= '9')) ch = getchar();
	if(ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9')
	{
		a *= 10;
		a += ch;
		a -= '0';
		ch = getchar();
	}
	if(minus) a = -a;
	return a;
}

const INT mod = 998244353;
const INT maxn = 505;
INT n, m;
INT num[maxn];
INT Inv(INT x)
{
	INT y = mod - 2;
	INT ans = 1;
	while(y)
	{
		if(y & 1) ans = ans * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return ans;
}

INT t1[maxn];
INT t2[maxn];
long double t3[maxn];
long double t4[maxn];
INT maxVal[maxn][maxn];
long double maxVald[maxn][maxn];

void run()
{
	n = readIn();
	m = readIn();

	INT* cnt = t1;
	INT* pre = t2;
	long double* cntd = t3;
	long double* pred = t4;

	for(int i = 1; i <= n; i++)
	{
		cnt[i] = cntd[i] = num[i] = readIn();
	}

	INT all = n * (n - 1) / 2;
	INT invAll = Inv(all);
	while(m--)
	{
		std::swap(cnt, pre);
		std::swap(cntd, pred);
		memset(cnt, 0, sizeof(INT) * (n + 1));
		memset(cntd, 0, sizeof(long double) * (n + 1));
		memset(maxVal, 0, sizeof(maxVal));
		memset(maxVald, 0, sizeof(maxVald));
		for(int i = 1; i < n; i++)
		{
			if(pred[i] > pred[i + 1])
			{
				maxVald[i][i + 1] = pred[i];
				maxVal[i][i + 1] = pre[i];
			}
			else
			{
				maxVald[i][i + 1] = pred[i + 1];
				maxVal[i][i + 1] = pre[i + 1];
			}
			for(int j = i + 2; j <= n; j++)
			{
				if(maxVald[i][j - 1] > pred[j])
				{
					maxVal[i][j] = maxVal[i][j - 1];
					maxVald[i][j] = maxVald[i][j - 1];
				}
				else
				{
					maxVal[i][j] = pre[j];
					maxVald[i][j] = pred[j];
				}
			}
		}

		for(int i = 1; i <= n; i++)
		{
			for(int j = 1; j < n; j++)
			{
				for(int k = j + 1; k <= n; k++)
				{
					if(j <= i && i <= k)
					{
						cnt[i] = (cnt[i] + maxVal[j][k] * invAll % mod) % mod;
						cntd[i] += maxVald[j][k] / all;
					}
					else
					{
						cnt[i] = (cnt[i] + pre[i] * invAll % mod) % mod;
						cntd[i] += pred[i] / all;
					}
				}
			}
		}
	}
	for(int i = 1; i <= n; i++)
	{
		cout << cnt[i] << endl;
	}
}

int main()
{
#ifndef JUDGE
	freopen("b.in", "r", stdin);
	freopen("b.out", "w", stdout);
#endif
	run();
	return 0;
}
