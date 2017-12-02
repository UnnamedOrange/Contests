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

const INT maxN = 131080;
INT n, K;
INT origin[maxN];

inline bool isOk(INT x, INT y)
{
	INT s = std::sqrt(x + y);
	s *= s;
	return x + y != s;
}

#define RunInstance(x) delete new x
struct cheat1
{
	static const INT maxn = 1030;

	cheat1()
	{
		std::vector<INT> ans;
		INT r = n;

		for(int i = n - 1; i >= 1; i--)
		{
			bool bOk = true;
			for(int j = i + 1; j <= r; j++)
			{
				if(!isOk(origin[i], origin[j]))
				{
					bOk = false;
					break;
				}
			}
			if(!bOk)
			{
				ans.push_back(i);
				r = i;
			}
		}
		cout << ans.size() + 1 << endl;
		for(int i = ans.size() - 1; i >= 0; i--)
		{
			cout << ans[i] << " ";
		}
	}
};
struct cheat2
{
	struct DS
	{
		INT size;
		std::vector<INT> parent;
		DS(INT N) : size(N + 1), parent(N + 1)
		{
			clear();
		}
		void clear()
		{
			for(int i = 1; i <= size; i++)
			{
				parent[i] = i;
			}
		}
		INT find(INT x)
		{
			if(x == parent[x]) return x;
			return parent[x] = find(parent[x]);
		}
		void unite(INT x, INT y)
		{
			parent[find(y)] = find(x);
		}
		bool judge(INT x, INT y)
		{
			return find(x) == find(y);
		}
	};

	cheat2()
	{
		std::vector<INT> ans;
		INT r = n;

		DS ds(n * 2);
		for(int i = n - 1; i >= 1; i--)
		{
			bool bOk = true;
			for(int j = i + 1; j <= r; j++)
			{
				if(!isOk(origin[i], origin[j]))
				{
					ds.unite(i, j + n);
					ds.unite(j, i + n);
				}
				if(ds.judge(i, i + n))
				{
					bOk = false;
					break;
				}
			}
			if(!bOk)
			{
				ans.push_back(i);
				r = i;
				ds.clear();
			}
		}
		cout << ans.size() + 1 << endl;
		for(int i = ans.size() - 1; i >= 0; i--)
		{
			cout << ans[i] << " ";
		}
	}
};
struct work
{
	work()
	{
		if(K == 1) RunInstance(cheat1);
		else if(K == 2) RunInstance(cheat2);
	}
};

void run()
{
	n = readIn();
	K = readIn();
	for(int i = 1; i <= n; i++)
	{
		origin[i] = readIn();
	}

	if(K == 1 && n <= 1024) RunInstance(cheat1);
	else if(K == 2 && n <= 1024) RunInstance(cheat2);
	else RunInstance(work);

}

int main()
{
#ifndef JUDGE
	freopen("division.in", "r", stdin);
	freopen("division.out", "w", stdout);
#endif
	run();
	return 0;
}
