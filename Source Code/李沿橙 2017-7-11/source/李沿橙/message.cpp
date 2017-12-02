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
using std::cin;
using std::cout;
using std::endl;
inline int readIn()
{
	int a = 0;
	char ch = getchar();
	while(!(ch >= '0' && ch <= '9')) ch=getchar();
	while(ch>='0' && ch<='9')
	{
		a = a * 10 + ch - '0';
		ch = getchar();
	}
	return a;
}

const int maxn = 200005;
int n;
int G[maxn];
int step[maxn];
int Index[maxn]; //只有当index相等时才能说明是在同一次搜索中搜到的，这时才能判断是不是找到了环
//若index不相等，则只是相当于重复访问了结点
int count_;
int ans = -1;

int length;

void dfs(int from)
{
	step[from] = 1;
	while(true)
	{
		Index[from] = count_;
		if(Index[G[from]] == count_ && step[G[from]]) //找到环
		{
			length = step[from] - step[G[from]] + 1;
			if(ans == -1 || ans > length)
			{
				ans = length;
			}
			return;
		}
		else if(Index[G[from]]) return;
		else
		{
			step[G[from]] = step[from] + 1;
			from = G[from];
		}
	}
}

void run()
{
	n = readIn();
	for(int i = 1; i <= n; i++)
	{
		G[i] = readIn();
	}

	for(int i = 1; i <= n; i++)
	{
		if(!Index[i])
		{
			count_++;
			dfs(i);
		}
	}
	printf("%d\n", ans);
}

int main()
{
	run();
	return 0;
}
