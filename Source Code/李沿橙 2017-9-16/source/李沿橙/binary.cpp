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

const INT maxn = 25;
INT n;

struct BST
{
	typedef struct Node
	{
		INT key;
		INT level;

		Node* lc;
		Node* rc;

		Node() : key(), level(), lc(), rc() {}
		Node(INT key, INT level) : key(key), level(level), lc(), rc() {}
	} *PNode;
	PNode root, null;
	INT levelCount[maxn];
	INT maxLevel;

	void insert(PNode& r, INT key, INT level)
	{
		if(r == null)
		{
			r = new Node(key, level);
			r->lc = r->rc = null;

			levelCount[level]++;
			maxLevel = std::max(maxLevel, level);
			return;
		}
		if(key < r->key) insert(r->lc, key, level + 1);
		else insert(r->rc, key, level + 1);
	}

public:
	BST() : levelCount(), maxLevel()
	{
		null = new Node();
		null->lc = null->rc = null;
		root = null;
	}
	void insert(INT key)
	{
		insert(root, key, 1);
	}
	bool BFS(std::vector<INT>& seq)
	{
		seq.clear();
		std::queue<PNode> q;
		if(root != null) q.push(root);

		std::vector<PNode> vec;

		while(!q.empty())
		{
			PNode from = q.front();
			q.pop();
			seq.push_back(from->key);

			if(from->level == maxLevel - 1)
			{
				vec.push_back(from);
			}

			if(from->lc != null) q.push(from->lc);
			if(from->rc != null) q.push(from->rc);
		}

		for(int i = 1; i < maxLevel; i++)
		{
			if(levelCount[i] != 1 << (i - 1))
			{
				return false;
			}
		}

		bool bSign = false;
		for(int i = 0; i < vec.size(); i++)
		{
			if(vec[i]->lc == null && vec[i]->rc != null) return false;
			else if(bSign && (vec[i]->lc != null || vec[i]->rc != null))
			{
				return false;
			}
			else if(vec[i]->lc != null && vec[i]->rc == null)
			{
				bSign = true;
			}
		}
		return true;
	}
};

void run()
{
	BST bst;
	n = readIn();
	for(int i = 1; i <= n; i++)
	{
		bst.insert(readIn());
	}
	std::vector<INT> seq;
	bool isCom = bst.BFS(seq);

	cout << seq[0];
	for(int i = 1; i < seq.size(); i++)
	{
		cout << ' ' << seq[i];
	}
	cout << endl;

	cout << (isCom ? "yes" : "no") << endl;
}

int main()
{
#ifndef JUDGE
	freopen("binary.in", "r", stdin);
	freopen("binary.out", "w", stdout);
#endif
	run();
	return 0;
}
