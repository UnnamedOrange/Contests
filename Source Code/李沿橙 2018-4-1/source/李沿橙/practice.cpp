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
typedef LL INT_PUT;
INT_PUT readIn()
{
	INT_PUT a = 0;
	bool positive = true;
	char ch = getchar();
	while (!(ch == '-' || std::isdigit(ch))) ch = getchar();
	if (ch == '-')
	{
		positive = false;
		ch = getchar();
	}
	while (std::isdigit(ch))
	{
		a = a * 10 - (ch - '0');
		ch = getchar();
	}
	if (positive) a = -a;
	return a;
}
void printOut(INT_PUT x)
{
	char buffer[20];
	int length = 0;
	if (x < 0) putchar('-');
	else x = -x;
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
	putchar('\n');
}

const int maxn = int(1e5) + 5;
int task;
int n;
LL c, d;
struct Tool
{
	int d;
	LL p, g, r;
	void read()
	{
		d = readIn();
		p = readIn();
		r = readIn();
		g = readIn();
	}
	bool operator<(const Tool& b) const
	{
		return d < b.d;
	}
} tools[maxn];

#define RunInstance(x) delete new x
struct brute
{
	static const int maxN = 1005;
	LL f[maxN];
	
	brute()
	{
		int T = readIn();
		while (T--)
		{
			n = readIn();
			c = readIn();
			d = readIn();
			for (int i = 1; i <= n; i++)
				tools[i].read();
			std::sort(tools + 1, tools + 1 + n);
			tools[0].r = c;
			
			memset(f, -1, sizeof(f));
			f[0] = 0;
			for(int i = 1; i <= n; i++)
			{
				for(int j = 0;j < i; j++)
				{
					if(f[j] == -1) continue;
					LL temp;
					if((temp = f[j] + tools[j].r + tools[j].g * (tools[i].d - tools[j].d - 1) - tools[i].p) >= 0)
						f[i] = std::max(f[i], temp);
				}
			}
			
			LL ans = 0;
			for(int j = 0; j <= n; j++)
			{
				if(f[j] == -1) continue;
				ans = std::max(ans, f[j] + tools[j].r + tools[j].g * (d - tools[j].d));
			}
			printOut(ans);
		}
	}
};
struct work
{
	LL f[maxn];
	LL y[maxn];
	
	inline LL cy(int t) { return f[t] + t; }
	inline LL cx(int t) { return ts[t].g; }
	inline LL deltay(int cnt, int pre) { return cy(cnt) - cy(pre); }
	inline LL deltax(int cnt, int pre) { return cx(cnt) - cx(pre); }
	inline double slope(int cnt, int pre) { return (double)deltay(cnt, pre) / deltax(cnt, pre); }
	
	Tool ts[maxn];
	
	struct deque : public std::deque<int>
	{
		int back2() { return std::deque<int>::operator[](std::deque<int>::size() - 2); }
		int front2() { return std::deque<int>::operator[](1); }
	};
	
	work()
	{
		int T = readIn();
		while (T--)
		{
			n = readIn();
			c = readIn();
			d = readIn();
			for (int i = 1; i <= n; i++)
				tools[i].read();
			std::sort(tools + 1, tools + 1 + n);
			
			ts[0].r = c;
			y[0] = c;
			int top = 0;
			for(int i = 1; i <= n; i++)
			{
				LL Y = tools[i].r - tools[i].g * tools[i].d - tools[i].g - tools[i].p;
				while(top && (tools[i].g < ts[top].g || tools[i].g == ts[top].g && Y - y[top] >= 0)) top--;
				ts[++top] = tools[i];
				y[top] = Y;
			}
			n = top;
			
			f[0] = 0;
			deque q;
			q.push_back(0);
			for(int i = 1; i <= n; i++)
			{
				while(q.size() > 1 && slope(q.front2(), q.front()) < ts[i].d) q.pop_front();
				int j = q.front();
				LL temp = f[j] + ts[j].r + ts[j].g * (ts[i].d - ts[j].d - 1) - ts[i].p;
				if(temp >= 0)
					f[i] = temp;
				
				if(f[i] != -1)
				{
					while(q.size() > 1 && slope(q.back(), q.back2()) >= slope(i, q.back())) q.pop_back();
					q.push_back(i);
				}
			}
			
			LL ans = 0;
			for(int j = 0; j <= n; j++)
			{
				if(f[j] == -1) continue;
				ans = std::max(ans, f[j] + tools[j].r + tools[j].g * (d - tools[j].d));
			}
			printOut(ans);
		}
	}
};

void run()
{
	task = readIn();

//	if(task <= 3)
//		RunInstance(brute);
//	else
		RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("practice.in", "r", stdin);
	freopen("practice.out", "w", stdout);
#endif
	run();
	return 0;
}
