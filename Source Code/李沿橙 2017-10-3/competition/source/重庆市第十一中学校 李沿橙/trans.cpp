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

const INT maxn = INT(1e6) + 5;
INT n, k;
INT d[maxn];

void print()
{
	for(int i = 1; i <= n; i++)
	{
		putchar(d[i] + '0');
	}
	putchar('\n');
}

void run()
{
	while(~scanf("%d%d", &n, &k))
	{
		for(int i = 1; i <= n; i++)
		{
			scanf("%1d", &d[i]);
		}

		if(!k)
		{
			print();
			continue;
		}

		for(int i = 1; i < n; i++)
		{
			if(i % 2 == 1 && d[i] == 2 && d[i + 1] == 3)
			{
				d[i + 1] = 2;
				k--;
				if(!k) break;
			}
			else if(i % 2 == 0 && d[i] == 2 && d[i + 1] == 3)
			{
				if(i == 1 || d[i - 1] != 2)
				{
					d[i] = 3;
					k--;
					if(!k) break;
				}
				else if(d[i - 1] == 2)
				{
					k %= 2;
					if(k)
					{
						d[i] = 3;
						k--;
					}
					break;
				}
			}
		}
		print();
	}
}

int main()
{
#ifndef JUDGE
	freopen("trans.in", "r", stdin);
	freopen("trans.out", "w", stdout);
#endif
	run();
	return 0;
}
