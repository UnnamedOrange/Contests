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
inline void printOut(INT x)
{
	if (!x)
	{
		putchar('0');
	}
	else
	{
		char buffer[10];
		INT length = 0;
		while (x)
		{
			buffer[length++] = x % 10 + '0';
			x /= 10;
		}
		do
		{
			putchar(buffer[--length]);
		} while (length);
	}
	putchar('\n');
}

const INT maxn = 10005;
INT n, m;

#define RunInstance(x) delete new x
struct cheat
{
	std::vector<std::string> library;

	cheat()
	{
		for (int i = 1; i <= n; i++)
		{
			char buffer[105];
			scanf("%s", buffer);
			library.push_back(buffer);
		}
		while (m--)
		{
			INT ins = readIn();
			if (ins == 1)
			{
				char buffer[105];
				scanf("%s", buffer);
				library.push_back(buffer);
			}
			else if (ins == 2)
			{
				INT num = readIn();
				std::vector<INT> Index;
				INT minLength = 105;
				for (int i = 1; i <= num; i++)
				{
					Index.push_back(readIn() - 1);
					minLength = std::min(minLength, INT(library[Index.back()].length()));
				}

				INT ans = minLength;
				for (int i = 0; i < minLength; i++)
				{
					const std::string& s1 = library[Index[0]];
					char ch = s1[s1.length() - 1 - i];
					bool bOk = true;
					for (int j = 1; j < Index.size(); j++)
					{
						const std::string& s = library[Index[j]];
						if (s[s.length() - 1 - i] != ch)
						{
							bOk = false;
							break;
						}
					}
					if (!bOk)
					{
						ans = i;
						break;
					}
				}
				cout << ans << endl;
			}
		}
	}
};
struct work
{
	class Trie
	{
		static const INT maxx = 1000005;
		INT N;
		struct Node
		{
			INT ch[26];
			Node() : ch() {}
		} nodes[maxx];

		static const INT maxD = 15;
		struct JUMP
		{
			INT jump[maxD];
			JUMP() : jump() {}
			INT& operator[] (const size_t x)
			{
				return jump[x];
			}
		};

		INT depth[maxx];
		JUMP parent[maxx];

		std::vector<INT> library;

		INT CreateNode(INT p)
		{
			N++;
			depth[N] = depth[p] + 1;
			parent[N][0] = p;
			for (int i = 1; i < maxD; i++)
			{
				parent[N][i] = parent[parent[N][i - 1]][i - 1];
			}
			return N;
		}
		INT Insert(const char* str)
		{
			INT length = strlen(str);
			INT pos = 0;
			for (int i = length - 1; i >= 0; i--)
			{
				Node& node = nodes[pos];
				char ch = str[i] - 'a';
				if (!node.ch[ch])
				{
					pos = node.ch[ch] = CreateNode(pos);
				}
				else
				{
					pos = node.ch[ch];
				}
			}
			return pos;
		}
		INT LCA(INT u, INT v)
		{
			if (depth[u] < depth[v]) std::swap(u, v);
			if (v == 0) return 0;
			for (int i = maxD - 1; ~i; i--)
			{
				if (depth[parent[u][i]] < depth[v]) continue;
				u = parent[u][i];
			}
			if (u != v)
			{
				for (int i = maxD - 1; ~i; i--)
				{
					if (parent[u][i] == parent[v][i]) continue;
					u = parent[u][i];
					v = parent[v][i];
				}
				u = parent[u][0];
			}
			return u;
		}

	public:
		Trie() : N(), depth()
		{
		}
		void InsertIntoLibrary(const char* str)
		{
			library.push_back(Insert(str));
		}
		INT DepthLCA(const std::vector<INT>& s)
		{
			INT lca = LCA(library[s[0] - 1], library[s[1] - 1]);
			for (int i = 2; i < s.size(); i++)
			{
				lca = LCA(lca, library[s[i] - 1]);
			}
			return depth[lca];
		}
	};

	char buffer[maxn];
	Trie trie;

	work()
	{
		for (int i = 1; i <= n; i++)
		{
			scanf("%s", buffer);
			trie.InsertIntoLibrary(buffer);
		}
		while (m--)
		{
			INT ins = readIn();
			if (ins == 1)
			{
				scanf("%s", buffer);
				trie.InsertIntoLibrary(buffer);
			}
			else
			{
				INT num = readIn();
				std::vector<INT> s(num);
				for (int i = 0; i < num; i++) s[i] = readIn();
				printOut(trie.DepthLCA(s));
			}
		}
	}
};

void run()
{
	n = readIn();
	m = readIn();
	RunInstance(work);
}

int main()
{
#ifndef JUDGE
	freopen("biology.in", "r", stdin);
	freopen("biology.out", "w", stdout);
#endif
	run();
	return 0;
}