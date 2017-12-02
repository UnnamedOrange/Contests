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

const INT maxn = 100005;
INT n, m;
long long ans;
struct hash_table
{
	static const INT size = 11229331;
	struct node
	{
		INT key;
		INT num;
		INT next;

		node(INT key = 0) : key(key), num(), next()
		{

		}
	} nodes[3000005];
	INT head[size];
	INT used;

	hash_table() : head(), used()
	{
	}

	INT& operator[] (INT key)
	{
		INT hashVal = key % size;
		for (int i = head[hashVal]; i; i = nodes[i].next)
		{
			if (nodes[i].key == key)
			{
				return nodes[i].num;
			}
		}
		used++;
		nodes[used].key = key;
		nodes[used].next = head[hashVal];
		head[hashVal] = used;
		return nodes[used].num;
	}

	INT query(INT key)
	{
		INT hashVal = key % size;
		for (int i = head[hashVal]; i; i = nodes[i].next)
		{
			if (nodes[i].key == key)
			{
				return nodes[i].num;
			}
		}
		return 0;
	}
}xorTable, originTable;

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= n; i++)
	{
		INT A = readIn();
		originTable[A]++;
		for (int j = 0; j < 30; j++)
		{
			xorTable[A ^ (1 << j)]++;
		}
	}
	for (int i = 1; i <= m; i++)
	{
		INT B = readIn();
		ans -= originTable.query(B) * 30;
		for (int j = 0; j < 30; j++)
		{
			ans += xorTable.query(B ^ (1 << j));
		}
	}
	cout << ans / 2 << endl;
}

int main()
{
	run();
	return 0;
}
