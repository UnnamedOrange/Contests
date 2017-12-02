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
inline void printOut(INT x)
{
	if(!x)
	{
		putchar('0');
	}
	else
	{
		char buffer[9];
		INT length = 0;
		while(x)
		{
			buffer[length++] = x % 10 + '0';
			x /= 10;
		}
		do
		{
			putchar(buffer[--length]);
		}
		while(length);
	}
	putchar('\n');
}

const INT maxn = INT(3e5) + 5;
INT n, m;
INT origin[maxn];

#define RunInstance(x) delete new x
struct work
{
	std::vector<INT> colors[maxn];

	work()
	{
		for(int i = 1; i <= n; i++)
		{
			colors[origin[i]].push_back(i);
		}

		while(m--)
		{
			INT ins = readIn();
			if(ins == 1)
			{
				INT l = readIn();
				INT r = readIn();
				INT c = readIn();

				INT num = std::upper_bound(colors[c].begin(), colors[c].end(), r) - std::lower_bound(colors[c].begin(), colors[c].end(), l);
				printOut(num);
			}
			else if(ins == 2)
			{
				INT x = readIn();
				if(origin[x] != origin[x + 1])
				{
					INT& l = *std::lower_bound(colors[origin[x]].begin(), colors[origin[x]].end(), x);
					INT& r = *std::lower_bound(colors[origin[x + 1]].begin(), colors[origin[x + 1]].end(), x + 1);
					l++;
					r--;
					std::swap(origin[x], origin[x + 1]);
				}
			}
		}
	}
};

void run()
{
	n = readIn();
	m = readIn();
	for(int i = 1; i <= n; i++)
	{
		origin[i] = readIn();
	}

	RunInstance(work);
}

int main()
{
#ifndef JUDGE
	freopen("color.in", "r", stdin);
	freopen("color.out", "w", stdout);
#endif
	run();
	return 0;
}
