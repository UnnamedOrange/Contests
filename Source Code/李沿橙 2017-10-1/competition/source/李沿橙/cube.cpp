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
		char buffer[8];
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

const INT maxn = 30005;
const INT n = 30000;
INT p;

#define RunInstance(x) delete new x

struct cheat
{
	std::vector<INT> s[maxn];
	INT inStack[maxn];

	cheat()
	{
		for(int i = 1; i <= n; i++)
		{
			s[i].push_back(i);
			inStack[i] = i;
		}

		while(p--)
		{
			char ins;
			scanf(" %c ", &ins);
			if(ins == 'M')
			{
				INT from = readIn();
				INT to = readIn();
				INT sFrom = inStack[from];
				INT sTo = inStack[to];
				for(int i = 0; i < s[sFrom].size(); i++)
				{
					s[sTo].push_back(s[sFrom][i]);
					inStack[s[sFrom][i]] = sTo;
				}
			}
			else if(ins == 'C')
			{
				INT x = readIn();
				INT sX = inStack[x];
				INT lowMark = s[sX].size() - 1;
				while(lowMark && s[sX][lowMark] != x) lowMark--;
				printOut(lowMark);
			}
		}
	}
};
struct work : public cheat
{
};

void run()
{
	p = readIn();
	if(p <= 1000) RunInstance(cheat);
	else RunInstance(work);
}

int main()
{
#ifndef JUDGE
	freopen("cube.in", "r", stdin);
	freopen("cube.out", "w", stdout);
#endif
	run();
	return 0;
}
