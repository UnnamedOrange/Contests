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
char getchar_()
{
	char ch = getchar();
	while (!(ch == '?' || (ch >= 'a' && ch <= 'z'))) ch = getchar();
	return ch == '?' ? 26 : ch - 'a';
}

const INT maxn = INT(6e5);
INT n, m;
unsigned long long k;
INT str[maxn];

struct DS
{
	INT parent[maxn];
	INT size;
	void resize(INT size)
	{
		this->size = size;
		for (int i = 0; i <= size; i++)
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
struct work
{
	class Splay
	{
		struct Node
		{
			INT v;
			INT s;
			bool flip;
			Node* ch[2];
			Node() : v(), s(), flip(), ch() {}
			void maintain() { s = ch[0]->s + ch[1]->s + 1; }
			INT comp(INT k)
			{
				if (ch[0]->s + 1 == k) return -1;
				return ch[0]->s + 1 < k;
			}
			void pushdown()
			{
				if (flip)
				{
					std::swap(ch[0], ch[1]);
					ch[0]->flip ^= 1;
					ch[1]->flip ^= 1;
					flip = false;
				}
			}
		};
		Node* null;
		Node* root;

	public:
		Splay()
		{
			null = new Node;
			root = null->ch[0] = null->ch[1] = null;
		}

	public:
		void build(const INT* l, const INT* r)
		{
			build(root, l, 0, r - l - 1);
		}
	private:
		void build(Node* &node, const INT* arr, INT l, INT r)
		{
			node = new Node;
			node->ch[0] = node->ch[1] = null;
			INT mid = (l + r) >> 1;
			node->v = arr[mid];

			if (l < mid) build(node->ch[0], arr, l, mid - 1);
			if (r > mid) build(node->ch[1], arr, mid + 1, r);
			node->maintain();
		}

	private:
		void rotate(Node* &r, INT d)
		{
			Node* k = r->ch[d ^ 1];
			r->ch[d ^ 1] = k->ch[d];
			k->ch[d] = r;
			r->maintain();
			k->maintain();
			r = k;
		}
		void select(Node* &r, INT k)
		{
			r->pushdown();
			INT d = r->comp(k);
			if (d == -1) return;
			INT k1 = k - d * (r->ch[0]->s + 1);
			Node* &p = r->ch[d];
			p->pushdown();
			INT d2 = p->comp(k1);
			INT k2 = k1 - d2 * (p->ch[0]->s + 1);
			if (d2 != -1)
			{
				select(p->ch[d2], k2);
				if (d == d2)
					rotate(r, d ^ 1);
				else
					rotate(p, d2 ^ 1);
			}
			rotate(r, d ^ 1);
		}

	private:
		Node* merge(Node* &r, Node* right)
		{
			select(r, r->s);
			r->ch[1] = right;
			r->maintain();
			return r;
		}
		Node* split(Node* &r, INT k)
		{
			select(r, k);
			Node* ret = r->ch[1];
			r->ch[1] = null;
			r->maintain();
			return ret;
		}

	public:
		void flip(INT l, INT r)
		{
			Node* mid = split(root, l);
			Node* right = split(mid, r - l + 1);
			mid->flip ^= 1;
			merge(root, merge(mid, right));
		}

	private:
		void wander(Node* &r, INT* ret)
		{
			if (r == null) return;
			r->pushdown();
			wander(r->ch[0], ret);
			ret[++ret[0]] = r->v;
			wander(r->ch[1], ret);
		}
	public:
		void wander(INT* ret) { wander(root, ret); }
	};

	INT after[maxn];
	DS ds;

	work()
	{
		INT code = 26;
		for (int i = 1; i <= n; i++)
			if (str[i] == 26)
				str[i] = code++;
		Splay splay;
		splay.build(str, str + 1 + n);

		while (m--)
		{
			INT l = readIn();
			INT r = readIn();
			splay.flip(l, r);
		}
		after[0] = 0;
		splay.wander(after);
		for (int i = 1; i < after[0]; i++)
			after[i] = after[i + 1];
		after[0]--;

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

		INT count_ = 0;
		std::vector<INT> map(maxn);
		for (int i = 1; i <= n; i++)
		{
			if (str[i] > 26)
			{
				if (map[str[i]]) str[i] = map[str[i]];
				else str[i] = map[str[i]] = count_++ + 26;
			}
		}
		std::vector<INT> idx(count_);
		k--;
		for (int i = idx.size() - 1; ~i; i--) //greedy
		{
			idx[i] = k % 26;
			k /= 26;
		}
		for (int i = 1; i <= n; i++)
		{
			if (str[i] < 26) putchar(str[i] + 'a');
			else putchar(idx[str[i] - 26] + 'a');
		}
		putchar('\n');
	}
};

void run()
{
	n = readIn();
	m = readIn();
	cin >> k;
	for (int i = 1; i <= n; i++)
		str[i] = getchar_();

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