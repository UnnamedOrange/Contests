#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <map>
#include <set>
using std::cin;
using std::cout;
using std::endl;
inline int readIn()
{
	int a;
	scanf("%d", &a);
	return a;
}

const int size = 250005;
int n, m;
int nCount;
struct Trie
{
	static int toInt(char ch)
	{
		if(ch>='A' && ch<='Z') return ch-'A';
		else return ch-'a'+26;
	}
	struct node
	{
		int key;
		int child[52];

		node()
		{
			memset(this, 0, sizeof(this));
		}
	} nodes[size];
	int nodeCount;

	Trie()
	{
		nodeCount = 0;
	}

	int insert(char* str)
	{
		int length = strlen(str);
		int parent = 0;
		for (int i = 0; i < length; i++)
		{
			int index = toInt(str[i]);
			if(!nodes[parent].child[index])
			{
				nodes[parent].child[index] = ++nodeCount;
			}
			parent = nodes[parent].child[index];
		}
		if (nodes[parent].key) return nodes[parent].key;
		return nodes[parent].key = ++nCount;
	}
} mapSI;
//std::map<std::string, int> mapSI;
int getIndex(char* name)
{
	return mapSI.insert(name);
}

const char* szText[] =
{
	"parallel",
	"intersect",
	"unknown"
};
const int PARALLEL = 0;
const int INTERSECT = 1;
const int UNKNOWN = 2;
class Disjiont
{
	std::vector<int> parent;
	std::vector<int> relation;

	int find(int x)
	{
		if (x == parent[x]) return x;
		int root = find(parent[x]);
		relation[x] = (relation[x] + relation[parent[x]]) % 2;
		return parent[x] = root;
	}

public:
	Disjiont() :parent(size), relation(size)
	{
		for (int i = 0; i < size; i++)
		{
			parent[i] = i;
			relation[i] = 0;
		}
	}
	bool unite(int x, int y, int rel)
	{
		int rootX = find(x);
		int rootY = find(y);
		if (rootX == rootY)
		{
			if (rel == PARALLEL)
			{
				if (relation[x] != relation[y]) return false;
			}
			else
			{
				if (relation[x] == relation[y]) return false;
			}
		}
		parent[rootY] = rootX;
		if (rel == PARALLEL)
			relation[rootY] = (relation[x] + relation[y]) % 2;
		else
			relation[rootY] = (relation[x] + relation[y] + 1) % 2;
		return true;
	}
	int judge(int x, int y)
	{
		int rootX = find(x);
		int rootY = find(y);
		if (rootX != rootY) return UNKNOWN;
		return relation[x] != relation[y];
	}
};

int main()
{
	n = readIn();
	m = readIn();
	Disjiont dis;
	bool bOk = true;
	for (int i = 1; i <= n; i++)
	{
		char input[3][105] = { 0 };
		scanf("%s%s%s", input[0], input[1], input[2]);
		int x = getIndex(input[0]);
		int y = getIndex(input[1]);
		bOk = dis.unite(x, y, strcmp(input[2], szText[PARALLEL]) != 0);
		if (!bOk) break;
	}
	if (!bOk)
	{
		printf("Waterloo\n");
		return 0;
	}
	for (int i = 1; i <= m; i++)
	{
		char input[2][105] = { 0 };
		scanf("%s%s", input[0], input[1]);
		int x = getIndex(input[0]);
		int y = getIndex(input[1]);
		printf("%s\n", szText[dis.judge(x, y)]);
	}
	return 0;
}
