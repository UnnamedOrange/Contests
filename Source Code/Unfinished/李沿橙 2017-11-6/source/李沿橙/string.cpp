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
typedef int INT;
using std::cin;
using std::cout;
using std::endl;
INT readIn()
{
	INT a = 0;
	bool minus = false;
	char ch = getchar();
	while (!(ch == '-' || (ch >= '0' && ch <= '9'))) ch = getchar();
	if (ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		a = a * 10 + (ch - '0');
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}
void printOut(INT x)
{
	char buffer[20];
	INT length = 0;
	bool minus = x < 0;
	if (minus) x = -x;
	do
	{
		buffer[length++] = x % 10 + '0';
		x /= 10;
	} while (x);
	if (minus) buffer[length++] = '-';
	do
	{
		putchar(buffer[--length]);
	} while (length);
	putchar('\n');
}
char getchar_()
{
	char ch = getchar();
	while (!(ch == '?' || (ch >= 'a' && ch <= 'z'))) ch = getchar();
	return ch == '?' ? 26 : ch - 'a';
}

const INT maxn = INT(5e5) + 5;
INT n, m, k;
INT str[maxn];

struct DS
{
	INT parent[maxn];
	INT size;
	void resize(INT size)
	{
		this->size = size;
		for (int i = 1; i <= size; i++)
			parent[i] = i;
	}
	INT find(INT x)
	{
		if (x == parent[x]) return x;
		return parent[x] = find(parent[x]);
	}
	void unite(INT x, INT y)
	{
		INT px = find(x);
		INT py = find(y);
		if (px != py)
		{
			size--;
			parent[py] = px;
		}
	}
	bool judge(INT x, INT y)
	{
		return find(x) == find(y);
	}
};

#define RunInstance(x) delete new x
struct brute
{
	static const INT maxN = 5005;
	INT after[maxN];
	DS ds;

	brute()
	{
		INT code = 26;
		for (int i = 1; i <= n; i++)
			if (str[i] == 26)
				str[i] = code++;

		memcpy(after, str, sizeof(after));
		while (m--)
		{
			INT l = readIn();
			INT r = readIn();
			std::reverse(after + l, after + r + 1);
		}

		ds.resize(n + 26);
		for (int i = 1; i <= n; i++)
		{
			if (ds.find(str[i]) < 26)
				ds.unite(str[i], after[i]);
			else
				ds.unite(after[i], str[i]);
		}

		for (int i = 1; i <= n; i++)
		{
			if (ds.find(after[i]) < 26 || ds.find(str[i]) < 26)
			{
				INT val = std::min(ds.find(after[i]), ds.find(str[i]));
				after[i] = str[i] = val;
			}
			else
			{
				after[i] = str[i] = ds.find(after[i]);
			}
		}

		std::map<INT, INT> map;
		for (int i = 1; i <= n; i++)
		{
			if (str[i] > 26)
			{
				if (map.count(str[i])) str[i] = map[str[i]];
				else str[i] = map[str[i]] = map.size() + 26;
			}
		}
		std::vector<INT> idx(map.size());
		k--;
		for (int i = idx.size() - 1; ~i; i--)
		{
			idx[i] = k % 26;
			k /= 26;
		}
		for (int i = 1; i <= n; i++)
		{
			if (str[i] < 26) putchar(str[i] + 'a');
			else putchar(idx[str[i] - 27] + 'a');
		}
		putchar('\n');
	}
};
struct work
{
	work()
	{

	}
};

void run()
{
	n = readIn();
	m = readIn();
	k = readIn();
	for (int i = 1; i <= n; i++)
		str[i] = getchar_();

	if (n <= 5000 && m <= 5000)
		RunInstance(brute);
	else
		RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("string.in", "r", stdin);
	freopen("string.out", "w", stdout);
#endif
	run();
	return 0;
}