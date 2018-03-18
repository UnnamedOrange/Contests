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
	INT_PUT a = 0; bool positive = true;
	char ch = getchar();
	while (!(ch == '-' || std::isdigit(ch))) ch = getchar();
	if (ch == '-') { positive = false; ch = getchar(); }
	while (std::isdigit(ch)) { a = a * 10 - (ch - '0'); ch = getchar(); }
	return positive ? -a : a;
}
void printOut(INT_PUT x)
{
	char buffer[20]; int length = 0;
	if (x < 0) putchar('-'); else x = -x;
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
	putchar('\n');
}

const int maxn = int(3e4) + 5;
const int maxs = 180;
int n, q;
int a[maxn];
int l, r, d;

struct Trie
{
	struct Node
	{
		Node* ch[2];
		Node() : ch() {}
	};
	static class Pool
	{
		int size;
		Node* stack[maxn * 30 * 2];
	public:
		Pool() : size()
		{
			Node* p = (Node*)calloc(maxn * 30, sizeof(Node));
			for(int i = 0; i < maxn * 30; i++, p++)
				stack[size++] = p;
		}
		Node* alloc()
		{
			if(!size) return (Node*)calloc(1, sizeof(Node));
			return new(stack[--size]) Node();
		}
		void release(Node* p)
		{
			stack[size++] = p;
		}
	} pool;
	
	static const int digit = 30;
	Node* root;
	Trie()
	{
		root = pool.alloc();
	}
	void clear(Node* &node)
	{
		if(!node) return;
		clear(node->ch[0]);
		clear(node->ch[1]);
		pool.release(node);
		node = NULL;
	}
	~Trie()
	{
		clear(root);
	}
	void insert(int num)
	{
		Node* cnt = root;
		for(int i = digit - 1; ~i; i--)
		{
			bool c = num & (1 << i);
			if(!cnt->ch[c]) cnt->ch[c] = pool.alloc();
			cnt = cnt->ch[c];
		}
	}
	int run(int num)
	{
		Node* cnt = root;
		int ret = 0;
		for(int i = digit - 1; ~i; i--)
		{
			bool c = num & (1 << i);
			if(cnt->ch[!c])
			{
				cnt = cnt->ch[!c];
				ret |= (1 << i);
			}
			else
			{
				cnt = cnt->ch[c];
			}
		}
		return ret;
	}
} tries[maxs];
Trie::Pool Trie::pool;

int sqrtN;
int N;
int inBlock[maxn];
int lBegin[maxn];
int rEnd[maxn];
void initBlocks()
{
	sqrtN = std::sqrt(n);
	N = (n + sqrtN - 1) / sqrtN;
	for(int i = 1; i <= n; i++)
	{
		int t = inBlock[i] = (i - 1) / sqrtN;
		if(!lBegin[t])
		{
			tries[t].insert(0);
			lBegin[t] = i;
		}
		rEnd[t] = i;
		tries[t].insert(a[i]);
	}
}

void handle()
{
	if(inBlock[l] == inBlock[r])
	{
		Trie trie;
		trie.insert(0);
		for(int i = l; i <= r; i++)
			trie.insert(a[i]);
		for(int i = l; i <= r; i++)
			d = trie.run(d);
		printOut(d);
	}
	else
	{
		for(int i = inBlock[l] + 1, to = inBlock[r]; i < to; i++)
			for(int j = lBegin[i]; j <= rEnd[i]; j++)
				d = tries[i].run(d);
		Trie trie;
		trie.insert(0);
		for(int i = l, to = rEnd[inBlock[l]]; i <= to; i++)
			trie.insert(a[i]);
		for(int i = lBegin[inBlock[r]]; i <= r; i++)
			trie.insert(a[i]);
		for(int i = 1, to = rEnd[inBlock[l]] - l + 1 + r - lBegin[inBlock[r]] + 1 + 1; i <= to; i++)
			d = trie.run(d);
		printOut(d);
	}
}

void run()
{
	n = readIn();
	for(int i = 1; i <= n; i++)
		a[i] = readIn();
	initBlocks();
	
	q = readIn();
	while(q--)
	{
		l = readIn();
		r = readIn();
		d = readIn();
		handle();
	}
}

int main()
{
#ifndef LOCAL
	freopen("xor.in", "r", stdin);
	freopen("xor.out", "w", stdout);
#endif
	run();
	return 0;
}
