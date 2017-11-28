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
#include <functional>
typedef int INT;
using std::cin;
using std::cout;
using std::endl;
inline INT readIn()
{
	INT a = 0;
	bool minus = false;
	char ch = getchar();
	while (!(ch == '-' || (ch >= '0' && ch <= '9'))) ch = getchar();
	if (ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		a = a * 10 + ch - '0';
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}
inline void printOut(INT x)
{
	if (!x)
	{
		putchar('0');
	}
	else
	{
		bool minus = x < 0;
		if (minus) x = -x;
		char buffer[12];
		INT length = 0;
		while (x)
		{
			buffer[length++] = x % 10 + '0';
			x /= 10;
		}
		if (minus) buffer[length++] = '-';
		do
		{
			putchar(buffer[--length]);
		} while (length);
	}
	putchar('\n');
}

const INT INF = (~(INT(1) << (sizeof(INT) * 8 - 1))) >> 1;
const INT maxn = INT(1e5) + 5;
INT n;
INT origin[maxn];

#define RunInstance(x) delete new x
struct cheat1
{
	INT ans;
	INT t;

	void search()
	{
		bool bFind = false;
		for (int i = 1; i < n; i++)
		{
			if (origin[i] && origin[i + 1])
			{
				bFind = true;

				t++;
				origin[i]--;
				origin[i + 1]--;
				search();
				t--;
				origin[i]++;
				origin[i + 1]++;
			}
		}
		if (!bFind)
		{
			ans = std::min(ans, t);
		}
	}

	cheat1() : ans(INF), t()
	{
		search();
		printOut(ans);
	}
};
struct cheat2
{
	cheat2()
	{
		INT ans = 0;
		for (int i = n - 1; i >= 1; i -= 3) ans += origin[i];
		printOut(ans);
	}
};

struct work2
{
	INT f[maxn];
	//the answer when the last number is 0

	work2() : f()
	{
		for (int i = 1; i <= n; i++)
		{
			f[i] = f[i - 1] + origin[i];
			if (i >= 2) f[i] = std::min(f[i], f[i - 2] + origin[i]);
			if (i >= 3) f[i] = std::min(f[i], f[i - 3] + std::max(origin[i - 1], origin[i]));
		}
		printOut(std::min(f[n], f[n - 1]));
	}
};
struct work
{
	static const INT maxk = INT(1e6) + 5;

	//rolling array(i), is previous 0, current status
	INT f[2][2][maxk];

	bool vis[2][2][maxk];
	INT s[2][2][maxk];

	work() : s(), vis()
	{
		memset(f, 0x7f, sizeof(f));
		s[1][0][++s[1][0][0]] = origin[1];
		f[1][0][origin[1]] = 0;
		vis[1][0][origin[1]] = true;
		for (int i = 2; i <= n; i++)
		{
			INT cnt = i & 1;
			INT pre = !cnt;
			for (int j = 1; j <= s[pre][0][0]; j++)
			{
				INT preS = s[pre][0][j];

				if (preS > origin[i])
				{
					for (int k = origin[i]; k >= 0; k--)
					{
						INT& ans = f[cnt][1][origin[i] - k];
						ans = std::min(ans, f[pre][0][preS] + k);

						if (!vis[cnt][1][origin[i] - k])
						{
							vis[cnt][1][origin[i] - k] = true;
							s[cnt][1][++s[cnt][1][0]] = origin[i] - k;
						}
					}
				}
				else
				{
					f[cnt][0][origin[i] - preS] = std::min(f[cnt][0][origin[i] - preS], f[pre][0][preS] + preS);
					if (!vis[cnt][0][origin[i] - preS])
					{
						vis[cnt][0][origin[i] - preS] = true;
						s[cnt][0][++s[cnt][0][0]] = origin[i] - preS;
					}
					for (int k = preS - 1; k >= 0; k--)
					{
						INT& ans = f[cnt][1][origin[i] - k];
						ans = std::min(ans, f[pre][0][preS] + k);

						if (!vis[cnt][1][origin[i] - k])
						{
							vis[cnt][1][origin[i] - k] = true;
							s[cnt][1][++s[cnt][1][0]] = origin[i] - k;
						}
					}
				}
			}

			for (int j = 1; j <= s[pre][1][0]; j++)
			{
				INT preS = s[pre][1][j];
				if (origin[i] < preS) continue;
				f[cnt][0][origin[i] - preS] = std::min(f[cnt][0][origin[i] - preS], f[pre][1][preS] + preS);
				if (!vis[cnt][0][origin[i] - preS])
				{
					vis[cnt][0][origin[i] - preS] = true;
					s[cnt][0][++s[cnt][0][0]] = origin[i] - preS;
				}
			}

			for (int j = 1; j <= s[pre][0][0]; j++)
			{
				vis[pre][0][s[pre][0][j]] = false;
				f[pre][0][s[pre][0][j]] = INF;
			}
			s[pre][0][0] = 0;

			for (int j = 1; j <= s[pre][1][0]; j++)
			{
				vis[pre][1][s[pre][1][j]] = false;
				f[pre][1][s[pre][1][j]] = INF;
			}
			s[pre][1][0] = 0;
		}

		INT cnt = n & 1;
		INT ans = f[cnt][1][0];
		for (int i = 0; i <= origin[n]; i++) ans = std::min(ans, f[cnt][0][i]);
		printOut(ans);
	}
};

void run()
{
	n = readIn();
	bool bInc = true;
	for (int i = 1; i <= n; i++)
	{
		origin[i] = readIn();
		bInc &= origin[i] >= origin[i + 1];
	}

	//	if (n <= 8) RunInstance(cheat1);
	//	else if (bInc) RunInstance(cheat2);
	//	else RunInstance(work);

	RunInstance(work2);
}

int main()
{
#ifndef JUDGE
	freopen("dark.in", "r", stdin);
	freopen("dark.out", "w", stdout);
#endif
	run();
	return 0;
}
