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
#include <cctype>
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

const INT maxn = 1005;
INT n, m, q;
struct STRING_POOL
{
	INT pos;
	char pool[11000005];

	STRING_POOL() : pos(0)
	{
	}

	INT read()
	{
		INT ret = pos;
		char ch = getchar();
		while (!isalpha(ch)) ch = getchar();
		while (isalpha(ch))
		{
			pool[pos++] = ch;
			ch = getchar();
		}
		pool[pos++] = '\0';
		return ret;
	}

	const char& operator[] (INT Index)
	{
		return pool[Index];
	}
} strPool;
INT str[maxn][maxn];

struct node
{
	static INT getCode(INT x, INT y)
	{
		return x * (m + 1) + y;
	}

	INT x;
	INT y;
	INT right;
	INT bottom;

} nodes[maxn * maxn];

void run()
{
	n = readIn();
	m = readIn();
	q = readIn();
	for (int i = 0; i <= n; i++)
	{
		nodes[i * (m + 1)].right = i * (m + 1) + 1;
		if (i != n) nodes[i * (m + 1)].bottom = (i + 1) * (m + 1);
	}
	for (int i = 0; i <= m; i++)
	{
		if (i != m) nodes[i].right = i + 1;
		nodes[i].bottom = m + 1 + i;
	}

	for (int x = 1; x <= n; x++)
	{
		for (int y = 1; y <= m; y++)
		{
			INT code = node::getCode(x, y);
			str[x][y] = strPool.read();
			nodes[code].x = x;
			nodes[code].y = y;
			if (y != m) nodes[code].right = code + 1;
			if (x != n) nodes[code].bottom = code + m + 1;
		}
	}

	while (q--)
	{
		INT x1 = readIn();
		INT y1 = readIn();
		INT x2 = readIn();
		INT y2 = readIn();
		INT height = readIn();
		INT width = readIn();

		INT pos[8];
		pos[0] = node::getCode(x1 - 1, 0);
		pos[1] = node::getCode(x2 - 1, 0);
		pos[2] = node::getCode(x1 + height - 1, 0);
		pos[3] = node::getCode(x2 + height - 1, 0);
		pos[4] = node::getCode(0, y1 - 1);
		pos[5] = node::getCode(0, y2 - 1);
		pos[6] = node::getCode(0, y1 + width - 1);
		pos[7] = node::getCode(0, y2 + width - 1);
		for (int i = 1; i <= y1; i++)
		{
			pos[0] = nodes[pos[0]].right;
			pos[2] = nodes[pos[2]].right;
		}
		for (int i = 1; i <= y2; i++)
		{
			pos[1] = nodes[pos[1]].right;
			pos[3] = nodes[pos[3]].right;
		}
		for (int i = 1; i <= x1; i++)
		{
			pos[4] = nodes[pos[4]].bottom;
			pos[6] = nodes[pos[6]].bottom;
		}
		for (int i = 1; i <= x2; i++)
		{
			pos[5] = nodes[pos[5]].bottom;
			pos[7] = nodes[pos[7]].bottom;
		}

		for (int i = 1; i <= width; i++)
		{
			std::swap(nodes[pos[0]].bottom, nodes[pos[1]].bottom);
			std::swap(nodes[pos[2]].bottom, nodes[pos[3]].bottom);
			pos[0] = nodes[pos[0]].right;
			pos[1] = nodes[pos[1]].right;
			pos[2] = nodes[pos[2]].right;
			pos[3] = nodes[pos[3]].right;
		}
		for (int i = 1; i <= height; i++)
		{
			std::swap(nodes[pos[4]].right, nodes[pos[5]].right);
			std::swap(nodes[pos[6]].right, nodes[pos[7]].right);
			pos[4] = nodes[pos[4]].bottom;
			pos[5] = nodes[pos[5]].bottom;
			pos[6] = nodes[pos[6]].bottom;
			pos[7] = nodes[pos[7]].bottom;
		}
	}

	for (int x = 1; x <= n; x++)
	{
		INT code = node::getCode(x, 0);
		for (int y = 1; y <= m; y++)
		{
			code = nodes[code].right;
			printf("%s ", &strPool[str[nodes[code].x][nodes[code].y]]);
		}
		puts("");
	}
}

int main()
{
	run();
	return 0;
}