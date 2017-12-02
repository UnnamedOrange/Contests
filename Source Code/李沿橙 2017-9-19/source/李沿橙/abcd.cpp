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

const INT maxn = 205;
INT n;
INT a[maxn], b[maxn], c[maxn], d[maxn];

#define RunInstance(x) delete new x
struct work
{
	INT *cost;
	INT *value;
	INT num[maxn];
	INT f[100005];
	INT Limit;
	INT Base;

	class Mono
	{
		struct Pair
		{
			INT val;
			INT Index;

			Pair(INT val, INT Index) : val(val), Index(Index) {}
		};
		std::deque<Pair> mono;
		INT head;
		INT tail;

	public:
		Mono() : head(), tail() {}

		void push(INT val)
		{
			while(!mono.empty() && mono.back().val <= val) mono.pop_back();
			mono.push_back(Pair(val, ++tail));
		}
		void pop()
		{
			head++;
			if(mono.front().Index == head) mono.pop_front();
		}
		
		INT size()
		{
			return tail - head;
		}
		INT front()
		{
			return mono.front().val;
		}
	};

	work() : Limit(), Base(), f()
	{
		cost = c;
		value = d;
		for(int i = 1; i <= n; i++)
		{
			Limit -= a[i] * c[i];
			Base += a[i] * d[i];
			num[i] = b[i] - a[i];
		}
		
		for(int i = 1; i <= n; i++)
		{
			for(int j = 0; j < cost[i]; j++)
			{
				Mono mono;
				INT delta = 0;
				INT sumCost = j;
				for(int k = 0; sumCost <= Limit; k++)
				{
					mono.push(f[sumCost] - delta);
					while(mono.size() > num[i] + 1) mono.pop();
					f[sumCost] = mono.front() + delta;
					
					sumCost += cost[i];
					delta += value[i];
				}
			}
		}
		
		cout << f[Limit] + Base << endl;
	}
};
struct cheat
{
#define s(x) ((x) + 100001)
	INT f[2][200005];
	bool g[2][200005];
	INT change[2][200005];

	cheat()
	{
		g[0][s(0)] = true;
		change[0][0] = 1;
		change[0][1] = 0;
		for(int i = 1; i <= n; i++)
		{
			INT cnt = i & 1;
			INT pre = cnt ^ 1;
			memset(f[cnt], 0, sizeof(f[cnt]));
			memset(g[cnt], 0, sizeof(g[cnt]));
			change[cnt][0] = 0;
			for(int j = a[i]; j <= b[i]; j++)
			{
				for(int k = 1; k <= change[pre][0]; k++)
				{
					INT from = change[pre][k];
					INT to = from + j * c[i];
					INT& ans = f[cnt][s(to)];

					if(!g[cnt][s(to)])
					{
						ans = f[pre][s(from)] + j * d[i];
						g[cnt][s(to)] = true;
						change[cnt][++change[cnt][0]] = to;
					}
					else
					{
						ans = std::max(ans, f[pre][s(from)] + j * d[i]);
					}
				}
			}
		}

		INT stage = n & 1;
		cout << f[stage][s(0)] << endl;
	}
#undef s
};

void run()
{
	n = readIn();
	for(int i = 1; i <= n; i++)
	{
		a[i] = readIn();
		b[i] = readIn();
		c[i] = readIn();
		d[i] = readIn();
	}
	if(n <= 50) RunInstance(cheat);
	else RunInstance(work);
}

int main()
{
#ifndef JUDGE
	freopen("abcd.in", "r", stdin);
	freopen("abcd.out", "w", stdout);
#endif
	run();
	return 0;
}
