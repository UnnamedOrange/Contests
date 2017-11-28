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
	putchar(' ');
}

const INT maxn = 100005;
INT n;
struct Person
{
	INT height;
	INT num;
	Person() {}
	Person(INT height, INT num) : height(height), num(num) {}

	bool operator< (const Person& b) const
	{
		return height < b.height;
	}
} persons[maxn];
INT disc[maxn];

#define RunInstance(x) delete new x
struct cheat1
{
	static const INT maxN = 15;
	struct BIT
	{
		INT bit[maxN];
		BIT() : bit() {}
#define lowbit(x) ((x) & -(x))
		inline void add(INT x, INT val)
		{
			while (x <= n)
			{
				bit[x] += val;
				x += lowbit(x);
			}
		}
		inline INT query(INT x)
		{
			INT ret = 0;
			while (x > 0)
			{
				ret += bit[x];
				x -= lowbit(x);
			}
			return ret;
		}
		inline void clear()
		{
			memset(bit, 0, sizeof(bit));
		}
	} b1, b2, b3;

	cheat1()
	{
		for (int i = 1; i <= n; i++)
		{
			b3.add(persons[i].height, 1);
		}
		do
		{
			b1.clear();
			b2 = b3;
			bool bOk = true;
			for (int i = 1; i <= n; i++)
			{
				b2.add(persons[i].height, -1);
				INT h = persons[i].height;
				INT q = persons[i].num;
				if (!(b1.query(n) - b1.query(h) == q || b2.query(n) - b2.query(h) == q))
				{
					bOk = false;
					break;
				}
				b1.add(persons[i].height, 1);
			}
			if (bOk)
			{
				for (int i = 1; i <= n; i++)
				{
					cout << disc[persons[i].height] << " ";
				}
				cout << endl;
				return;
			}
		} while (std::next_permutation(persons + 1, persons + 1 + n));
		cout << "impossible" << endl;
	}
};
struct cheat2
{
	cheat2()
	{
		for (int i = 1; i <= (n >> 1); i++)
		{
			std::swap(persons[i], persons[n - i + 1]);
		}

		std::vector<INT> ans;
		for (int i = 1; i <= n; i++)
		{
			if (persons[i].num >= i)
			{
				cout << "impossible" << endl;
				return;
			}
			INT t = std::max(persons[i].num, i - 1 - persons[i].num);
			ans.insert(ans.begin() + (i - 1 - t), persons[i].height);
		}
		for (int i = 0; i < n; i++)
		{
			printOut(disc[ans[i]]);
		}
		putchar('\n');
	}
};
struct work
{
	class SegTree
	{
		INT tree[262150];

#define PARAM INT node, INT l, INT r
#define DEF INT mid = (l + r) >> 1; INT lc = node << 1; INT rc = lc | 1;

		INT g_Pos;

		INT modify_()
		{
			INT cnt = 0;
			INT node = 1;
			INT l = 1;
			INT r = n;
			while (r - l > 0)
			{
				DEF;
				tree[node]--;
				if (cnt + tree[lc] >= g_Pos)
				{
					r = mid;
					node = lc;
				}
				else
				{
					cnt += tree[lc];
					l = mid + 1;
					node = rc;
				}
			}
			tree[node]--;
			return l;
		}

	public:
		SegTree() : tree()
		{
			build(1, 1, n);
		}

		void build(PARAM)
		{
			if (l == r)
			{
				tree[node] = 1;
				return;
			}
			DEF;
			build(lc, l, mid);
			build(rc, mid + 1, r);
			tree[node] = tree[lc] + tree[rc];
		}

		INT modify(INT pos)
		{
			g_Pos = pos;
			return modify_();
		}
	} st;

	INT ans[maxn];

	work() : ans()
	{
		for (int i = 1; i <= n; i++)
		{
			if (persons[i].num > n - i)
			{
				cout << "impossible" << endl;
				return;
			}
			INT t = std::min(persons[i].num + 1, n - i + 1 - persons[i].num);
			ans[st.modify(t)] = persons[i].height;
		}
		for (int i = 1; i <= n; i++)
		{
			printOut(disc[ans[i]]);
		}
	}
};

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
	{
		persons[i].height = readIn();
		persons[i].num = readIn();
	}
	std::sort(persons + 1, persons + 1 + n);
	for (int i = 1; i <= n; i++)
	{
		disc[i] = persons[i].height;
		persons[i].height = i;
	}

	//	if (n <= 10)
	//		RunInstance(cheat1);
	//	else if (n <= 1000)
	//		RunInstance(cheat2);
	//	else
	RunInstance(work);
}

int main()
{
#ifndef JUDGE
	freopen("E.in", "r", stdin);
	freopen("E.out", "w", stdout);
#endif
	run();
	return 0;
}
