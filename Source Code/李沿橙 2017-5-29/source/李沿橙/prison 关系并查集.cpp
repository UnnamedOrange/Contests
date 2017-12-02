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

INT n, m;

struct ufs
{
	std::vector<int> parent;
	std::vector<int> relation; //只能定义为是否不同监狱，不能定义为是否同一监狱

	ufs(int size) : parent(size + 1), relation(size + 1)
	{
		for(int i = 1; i <= size; i++)
		{
			parent[i] = i;
			relation[i] = false;
		}
	}

	int find(int x)
	{
		if(parent[x] == x) return parent[x];
		int Ancestor = find(parent[x]);
		relation[x] = relation[x] ^ relation[parent[x]];
		return parent[x] = Ancestor;
	}

	bool unite(int x,int y)
	{
		int px = find(x), py = find(y);
		if(px == py && relation[x] == relation[y])
		{
			return false; //矛盾
		}
		parent[py] = px;
		relation[py] = !(relation[x] ^ relation[y]);
		return true;
	}
};

struct edge
{
	int from;
	int to;
	int dis;

	void input()
	{
		from = readIn();
		to = readIn();
		dis = readIn();
	}

	bool operator <(const edge &b) const
	{
		return dis > b.dis;
	}
};

void run()
{
	n = readIn();
	m = readIn();
	std::vector<edge> edges(m);
	for(int i = 0; i < m; i++)
	{
		edges[i].input();
	}
	std::sort(edges.begin(),edges.end());

	ufs u(n);
	for(int i = 0; i < m; i++)
	{
		bool result = u.unite(edges[i].from, edges[i].to);
		if(!result)
		{
			cout << edges[i].dis << endl;
			return;
		}
	}
	cout << 0 << endl;
}

int main()
{
	run();
	return 0;
}
