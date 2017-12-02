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
		putchar('\n');
		return;
	}
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
	putchar('\n');
}

INT n, m;
INT inCase[INT(1e6) + 5];
bool caseIn[200005];

void run()
{
	n = readIn();
	m = readIn();
	INT ins;
	INT Index;
	while(m--)
	{
		ins = readIn();
		Index = readIn();
		if(ins == 1)
		{
			INT pos0 = 0;
			INT pos1 = 0;
			INT pos2 = 0;
			INT dis = 0;
			INT here = 0;
			for(int i = 1; i <= n; i++)
			{
				if(!caseIn[i]) continue;
				if(!pos1)
				{
					pos0 = pos1 = pos2 = i;
				}
				else if(pos1 == pos2)
				{
					pos2 = i;
					dis = (pos2 - pos1) >> 1;
					here = pos1 + dis;
				}
				else
				{
					pos1 = pos2;
					pos2 = i;
					if((pos2 - pos1) >> 1 > dis)
					{
						dis = (pos2 - pos1) >> 1;
						here = pos1 + dis;
					}
				}
			}
			if(!caseIn[1])
			{
				if(pos0 && pos0 - 1 >= dis)
				{
					dis = pos0 - 1;
					here = 1;
				}
				else if(!pos0)
				{
					here = 1;
				}
			}
			if(!caseIn[n])
			{
				if(pos2 && n - pos2 > dis)
				{
					dis = n - pos2;
					here = n;
				}
			}

			inCase[Index] = here;
			caseIn[here] = true;
			printOut(here);
		}
		else if(ins == 2)
		{
			caseIn[inCase[Index]] = false;
			inCase[Index] = 0;
		}
	}
}

int main()
{
	run();
	return 0;
}
