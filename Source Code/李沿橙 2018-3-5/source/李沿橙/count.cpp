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
	INT_PUT a = 0;
	bool minus = false;
	char ch = getchar();
	while (!(ch == '-' || isdigit(ch))) ch = getchar();
	if (ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while (isdigit(ch))
	{
		a = a * 10 + (ch - '0');
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}
void printOut(INT_PUT x)
{
	char buffer[20];
	int length = 0;
	if(x < 0)
	{
		putchar('-');
		x = -x;
	}
	do
	{
		buffer[length++] = x % 10 + '0';
		x /= 10;
	} while(x);
	do
	{
		putchar(buffer[--length]);
	} while(length);
}

const int mod = 998244353;
const int maxn = 305;
int n, m;
int rect[maxn][maxn];

#define RunInstance(x) delete new x
struct brute
{
	int ans;
	void DFS(int node, int count, int accu, int pre)
	{
		if(count == m)
		{
			ans = (ans + accu) % mod;
			return;
		}
		for(int i = 1; i <= n; i++)
		{
			if(rect[node][i])
			{
				int t = rect[node][i];
				rect[node][i] = 0;
				DFS(i, count + 1, accu + (pre == t), t);
				rect[node][i] = t;
			}
		}
	}
	
	brute() : ans()
	{
		for(int i = 1; i <= n; i++)
			DFS(i, 0, 0, 0);
		printOut(ans / (m - 1));
	}
};

void run()
{
	n = readIn();
	m = readIn();
	for(int i = 1; i <= m; i++)
	{
		int color = readIn();
		int from = readIn();
		int to = readIn();
		rect[from][to] = color;
	}
	
	if(n <= 10 && m <= 16)
		RunInstance(brute);
}

int main()
{
#ifndef LOCAL
	freopen("count.in", "r", stdin);
	freopen("count.out", "w", stdout);
#endif
	run();
	return 0;
}
