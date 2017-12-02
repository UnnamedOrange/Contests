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

const INT INF = 10000;
const INT maxn = 205;
char buffer[maxn];
INT n = 1;
INT seq[maxn];

#define RunInstance(x) delete new x
struct work
{
	INT f[maxn][maxn];

	INT dp(INT l, INT r)
	{
		INT& ans = f[l][r];
		if (ans != -1) return ans;
		if (l == r) return ans = 3 - seq[l];

		INT ret = INF;
		for (int i = l; i < r; i++)
		{
			ret = std::min(ret, dp(l, i) + dp(i + 1, r));
		}
		if ((r - l - 1) & 1) //偶数个必定至少要打2颗，而拆解的结果已经在前面计算过了
		{
			if (seq[l] + seq[r] == 2) //根据已有的计算要用的
			{
				ret = std::min(ret, dp(l + 1, r - 1) + 1);
			}
			else //并考虑各种情况，做到 递推的步伐小一点，状态的定义简单点
			{
				ret = std::min(ret, dp(l + 1, r - 1));
			}

			if (seq[l] + seq[r] < 4) //最后的情况：两边不都是2颗，中间有1颗的，把剩下的分两次打掉，左右连同中间的就消掉了
			{
				for (int i = l + 2; i < r; i += 2)
				{
					if (seq[i] == 1)
					{
						ret = std::min(ret, dp(l + 1, i - 1) + dp(i + 1, r - 1));
					}
				}
			}
		}
		return ans = ret;
	}

	work()
	{
		memset(f, -1, sizeof(f));
		cout << dp(1, n) << endl;
	}
};
struct cheat1
{
	std::map<std::vector<INT>, INT> m;

	INT search(std::vector<INT> origin = std::vector<INT>(seq + 1, seq + 1 + n))
	{
		if (m.count(origin)) return m[origin];
		if (!origin.size())
		{
			return 0;
		}
		INT ret = INF;
		for (int i = 0; i < origin.size(); i++)
		{
			INT l = i - 1, r = i + 1;
			while (l >= 0 && r < origin.size() && origin[l] + origin[r] >= 3)
			{
				l--;
				r++;
			}
			std::vector<INT> temp;

			bool sign = l >= 0 && r < origin.size();
			for (int j = 0; j <= l - sign; j++)
			{
				temp.push_back(origin[j]);
			}
			if (sign) temp.push_back(origin[l] + origin[r]);
			for (int j = r + sign; j < origin.size(); j++)
			{
				temp.push_back(origin[j]);
			}
			ret = std::min(ret, (origin[i] == 1 ? 2 : 1) + search(temp));
		}
		return m[origin] = ret;
	}

	cheat1()
	{
		cout << search() << endl;
	}
};

void run()
{
	scanf("%s", buffer);
	INT length = strlen(buffer);
	for (int i = 0; i < length; i++)
	{
		if (i && buffer[i] != buffer[i - 1]) n++;
		seq[n]++;
	}
	if (n <= 20) RunInstance(cheat1);
	else RunInstance(work);
}

int main()
{
#ifndef JUDGE
	freopen("zuma.in", "r", stdin);
	freopen("zuma.out", "w", stdout);
#endif
	run();
	return 0;
}