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

const INT maxn = 105;
INT n;
INT num[maxn];
INT f[maxn][maxn][maxn]; //[length][from][material]

INT count_;
INT table[maxn * maxn * maxn];
INT next[maxn * maxn * maxn];
INT head[maxn][maxn];
void add(INT length, INT from, INT material)
{
	count_++;
	table[count_] = material;
	next[count_] = head[length][from];
	head[length][from] = count_;
}

void run()
{
	INT T = readIn();
	while (T--)
	{
		n = readIn();
		memset(f, -1, sizeof(f));
		memset(table, 0, sizeof(table));
		memset(next, 0, sizeof(next));
		memset(head, 0, sizeof(head));
		for (int i = 1; i <= n; i++)
		{
			num[i] = readIn();
			f[1][i][num[i]] = 0;
			add(1, i, num[i]);
		}

		for (int i = 2; i <= n; i++)
		{
			for (int j = 1; j <= n - i + 1; j++)
			{
				for (int k = 1; k < i; k++)
				{
					for (int a = head[k][j]; a; a = next[a])
					{
						for (int b = head[i - k][j + k]; b; b = next[b])
						{
							INT& temp = f[i][j][(table[a] + table[b]) % 100];
							if (temp == -1) add(i, j, (table[a] + table[b]) % 100);
							INT val = f[k][j][table[a]] + f[i - k][j + k][table[b]] + table[a] * table[b];
							if (temp == -1 || temp > val)
							{
								temp = val;
							}
						}
					}
				}
			}
		}

		INT ans = -1;
		for (int i = head[n][1]; i; i = next[i])
		{
			if (f[n][1][table[i]] == -1) continue;
			if (ans == -1 || f[n][1][table[i]] < ans)
			{
				ans = f[n][1][table[i]];
			}
		}
		cout << ans << endl;
	}
}

int main()
{
	run();
	return 0;
}
