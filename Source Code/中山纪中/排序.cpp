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
	char str[7];
	INT length = 0;
	while (x)
	{
		str[length++] = x % 10 + '0';
		x /= 10;
	}
	do
	{
		putchar(str[--length]);
	} while (length);
	putchar(' ');
}

const INT maxn = 1e6 + 5;
INT n;
struct stack
{
	INT container[maxn];
	INT size;

	bool empty()
	{
		return !size;
	}
	INT& top()
	{
		return container[size - 1];
	}
	void push(INT x)
	{
		container[size++] = x;
	}
	void pop()
	{
		size--;
	}
} s;
bool inStack[maxn];
bool havePrinted[maxn];

void run()
{
	n = readIn();
	INT countIn = n;
	for (int i = n; i >= 1; i--)
	{
		if (inStack[i] && s.top() == i)
		{
			INT t = s.top();
			printOut(t);
			inStack[t] = false;
			havePrinted[t] = true;
			s.pop();
		}
		else if (!inStack[i] && !havePrinted[i])
		{
			while (countIn)
			{
				INT in = readIn();
				countIn--;
				if (in == i)
				{
					while (!s.empty() && s.top() > i)
					{
						INT t = s.top();
						s.pop();
						printOut(t);
					}
					printOut(in);
					break;
				}
				else
				{
					s.push(in);
					inStack[in] = true;
				}
			}
		}
	}
	while (!s.empty())
	{
		printOut(s.top());
		s.pop();
	}
}

int main()
{
	run();
	return 0;
}
