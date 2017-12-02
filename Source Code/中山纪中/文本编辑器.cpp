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
#include <list>
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
inline void readIn(char& ch)
{
	ch = getchar();
	while (!(ch >= 33 && ch <= 126)) ch = getchar();
}

INT n;
INT tagReverse;
std::vector<char> left, right;
std::deque<char> middle;

char& middleL()
{
	if (!tagReverse) return middle.front();
	return middle.back();
}
char& middleR()
{
	if (!tagReverse) return middle.back();
	return middle.front();
}
void popL()
{
	if (!tagReverse)
	{
		middle.pop_front();
	}
	else
	{
		middle.pop_back();
	}
}
void popR()
{
	if (!tagReverse)
	{
		middle.pop_back();
	}
	else
	{
		middle.pop_front();
	}
}
void pushL(char ch)
{
	if (!tagReverse)
	{
		middle.push_front(ch);
	}
	else
	{
		middle.push_back(ch);
	}
}
void pushR(char ch)
{
	if (!tagReverse)
	{
		middle.push_back(ch);
	}
	else
	{
		middle.push_front(ch);
	}
}

void run()
{
	char ch = getchar();
	while (ch >= 33 && ch <= 126)
	{
		middle.push_back(ch);
		ch = getchar();
	}
	n = readIn();

	while (n--)
	{
		char ins;
		readIn(ins);
		if (ins == '<')
		{
			char param;
			readIn(param);
			if (param == 'L')
			{
				if (left.empty())
				{
					printf("F\n");
				}
				else
				{
					pushL(left.back());
					left.pop_back();
					printf("T\n");
				}
			}
			else if (param == 'R')
			{
				if (middle.empty())
				{
					printf("F\n");
				}
				else
				{
					right.push_back(middleR());
					popR();
					printf("T\n");
				}
			}
		}
		else if (ins == '>')
		{
			char param;
			readIn(param);
			if (param == 'L')
			{
				if (middle.empty())
				{
					printf("F\n");
				}
				else
				{
					left.push_back(middleL());
					popL();
					printf("T\n");
				}
			}
			else if (param == 'R')
			{
				if (right.empty())
				{
					printf("F\n");
				}
				else
				{
					pushR(right.back());
					right.pop_back();
					printf("T\n");
				}
			}
		}
		else if (ins == 'I')
		{
			char param1, param2;
			readIn(param1);
			readIn(param2);
			if (param1 == 'L')
			{
				left.push_back(param2);
			}
			else if (param1 == 'R')
			{
				pushR(param2);
			}
			printf("T\n");
		}
		else if (ins == 'D')
		{
			char param;
			readIn(param);
			if (param == 'L')
			{
				if (middle.empty())
				{
					printf("F\n");
				}
				else
				{
					popL();
					printf("T\n");
				}
			}
			else if (param == 'R')
			{
				if (right.empty())
				{
					printf("F\n");
				}
				else
				{
					right.pop_back();
					printf("T\n");
				}
			}
		}
		else if (ins == 'R')
		{
			if (middle.empty())
			{
				printf("F\n");
			}
			else
			{
				tagReverse = !tagReverse;
				printf("T\n");
			}
		}
		else if (ins == 'S')
		{
			for (int i = 0; i < left.size(); i++)
			{
				putchar(left[i]);
			}
			if (!tagReverse)
			{
				for (int i = 0; i < middle.size(); i++)
				{
					putchar(middle[i]);
				}
			}
			else
			{
				for (int i = middle.size() - 1; i >= 0; i--)
				{
					putchar(middle[i]);
				}
			}
			for (int i = right.size() - 1; i >= 0; i--)
			{
				putchar(right[i]);
			}
			putchar('\n');
		}
	}
}

int main()
{
	run();
	return 0;
}
