#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cassert>
#include <cctype>
#include <climits>
#include <ctime>
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
#include <functional>
typedef long long LL;
typedef unsigned long long ULL;
using std::cin;
using std::cout;
using std::endl;
typedef int INT_PUT;
INT_PUT readIn()
{
	INT_PUT a = 0;
	bool positive = true;
	char ch = getchar();
	while (!(ch == '-' || std::isdigit(ch))) ch = getchar();
	if (ch == '-')
	{
		positive = false;
		ch = getchar();
	}
	while (std::isdigit(ch))
	{
		a = a * 10 - (ch - '0');
		ch = getchar();
	}
	if (positive) a = -a;
	return a;
}
void printOut(INT_PUT x)
{
	char buffer[20];
	int length = 0;
	if (x < 0) putchar('-');
	else x = -x;
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
}

const int mod = int(1e9) + 7;
const int maxl = int(1e4) + 5;

enum
{
	NUM, ADD, SUB, MUL, LEFT, RIGHT
};
struct Element
{
	int type;
	int num;
	Element() {}
	Element(int type, int num) : type(type), num(num) {}
};
struct Expression
{
	int size;
	int countNum;
	Element elements[maxl];
	Expression() : size(), countNum() {}
	int calc(int* val)
	{
		std::vector<int> ovs;
		ovs.reserve(25);
		for (int i = 0; i < size; i++)
		{
			if (elements[i].type == NUM)
				ovs.push_back(val[elements[i].num]);
			else
			{
				int reg2 = ovs.back();
				ovs.pop_back();
				int reg1 = ovs.back();
				ovs.pop_back();
				int op = elements[i].type;
				LL temp;
				switch (op)
				{
				case ADD:
					reg1 = (temp = reg1 + reg2) >= mod ? temp - mod : temp;
					break;
				case SUB:
					reg1 = (temp = reg1 - reg2) < 0 ? temp + mod : temp;
					break;
				case MUL:
					reg1 = (LL)reg1 * reg2 % mod;
					break;
				}
				ovs.push_back(reg1);
			}
		}
		return ovs.back();
	}
	void analyze(char* str)
	{
		std::stack<int> ops;
		ops.push(LEFT);
		strcat(str, ")");
		for (char ch = *str; ch != '\0'; str++, ch = *str)
		{
			if (ch == '_')
			{
				countNum++;
				elements[size++] = Element(NUM, countNum);
			}
			else if (ch == '(')
			{
				ops.push(LEFT);
			}
			else if (ch == ')')
			{
				while (!ops.empty() && ops.top() != LEFT)
				{
					elements[size++] = Element(ops.top(), 0);
					ops.pop();
				}
				ops.pop();
			}
			else if (ch == '*')
			{
				ops.push(MUL);
			}
			else if (ch == '+' || ch == '-')
			{
				while (!ops.empty() && ops.top() == MUL)
				{
					elements[size++] = Element(ops.top(), 0);
					ops.pop();
				}
				ops.push(ch == '+' ? ADD : SUB);
			}
		}
	}
} expression;
int n;
char str[maxl];

int nExp;
int sum;
bool vis[15];
int buf[15];
void search(int depth)
{
	if (depth > expression.countNum)
	{
		int temp;
		nExp = (temp = nExp + 1) >= mod ? temp - mod : temp;
		sum = (temp = sum + expression.calc(buf)) >= mod ? temp - mod : temp;
		return;
	}
	for (int i = 1; i <= n; i++)
	{
		if (vis[i]) continue;
		vis[i] = true;
		buf[depth] = i;
		search(depth + 1);
		vis[i] = false;
	}
}

LL power(LL x, int y)
{
	LL ret = 1;
	while (y)
	{
		if (y & 1) ret = ret * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return ret;
}

void run()
{
	n = readIn();
	scanf("%s", str);
	expression.analyze(str);
	if (n <= 10)
	{
		search(1);
		printOut((LL)sum * power(nExp, mod - 2) % mod);
	}
}

int main()
{
#ifndef LOCAL
	freopen("expr.in", "r", stdin);
	freopen("expr.out", "w", stdout);
#endif
	run();
	return 0;
}