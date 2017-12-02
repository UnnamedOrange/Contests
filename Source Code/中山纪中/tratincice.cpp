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

const INT maxn = 100005;
const INT maxx = 400005;
const INT delta = 200000;
INT n, m;
std::vector<INT> horizontal[maxx];
std::vector<INT> vertical[maxx];
bool visH[maxx];
bool visV[maxx];
std::vector<INT> seqH;
std::vector<INT> seqV;

void init()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= n; i++)
	{
		INT x = readIn() + delta;
		INT y = readIn() + delta;
		horizontal[y].push_back(x);
		vertical[x].push_back(y);
		if (!visH[y])
		{
			seqH.push_back(y);
			visH[y] = true;
		}
		if (!visV[x])
		{
			seqV.push_back(x);
			visV[x] = true;
		}
	}

	INT size;
	size = seqH.size();
	for (int i = 0; i < size; i++)
	{
		std::sort(horizontal[seqH[i]].begin(), horizontal[seqH[i]].end());
	}
	size = seqV.size();
	for (int i = 0; i < size; i++)
	{
		std::sort(vertical[seqV[i]].begin(), vertical[seqV[i]].end());
	}
}

inline INT getPos(std::vector<INT>& v, INT val)
{
	return std::lower_bound(v.begin(), v.end(), val) - v.begin();
}

void run()
{
	init();

	INT x = 0 + delta, y = 0 + delta;
	for (int i = 1; i <= m; i++)
	{
		char ins;
		scanf(" %c ", &ins);
		switch (ins)
		{
		case 'R':
		{
			INT pos = getPos(horizontal[y], x);
			if (x == horizontal[y][pos]) x = horizontal[y][pos + 1];
			else x = horizontal[y][pos];
			break;
		}
		case 'U':
		{
			INT pos = getPos(vertical[x], y);
			if (y == vertical[x][pos]) y = vertical[x][pos + 1];
			else y = vertical[x][pos];
			break;
		}
		case 'D':
		{
			INT pos = getPos(vertical[x], y);
			y = vertical[x][pos - 1]; //no need to judge
			break;
		}
		case 'L':
		{
			INT pos = getPos(horizontal[y], x);
			x = horizontal[y][pos - 1]; //no need to judge
			break;
		}
		default:
			break;
		}
	}
	cout << x - delta << " " << y - delta << endl;

}

int main()
{
#ifndef JUDGE
	freopen("tratincice.in", "r", stdin);
	freopen("tratincice.out", "w", stdout);
#endif
	run();
	return 0;
}
