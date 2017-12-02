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
#define FOR(x, f, t) for(int x = (f); x <= (t); x++)
inline int readIn()
{
	int a;
	scanf("%d", &a);
	return a;
}

const int maxn = 1000005;
int n, m;
int start[maxn];
int cost[maxn];
int from[maxn];
int to[maxn];

int temp[maxn];
bool check(int t)
{
	//Note:离线前缀和算法：
	memset(temp, 0, sizeof(int) * (n + 1));
	for (int i = 1; i <= t; i++)
	{
		temp[from[i]] += cost[i];
		temp[to[i] + 1] -= cost[i];
	}
	for (int i = 1; i <= n; i++)
	{
		temp[i] += temp[i - 1];
	}
	for (int i = 1; i <= n; i++)
	{
		if (start[i] - temp[i] < 0) return false;
	}
	return true;
}

void run()
{
	n = readIn();
	m = readIn();
	FOR(i, 1, n)
	{
		start[i] = readIn();
	}
	FOR(i, 1, m)
	{
		cost[i] = readIn();
		from[i] = readIn();
		to[i] = readIn();
	}
	int left = 1, right = n + 1;
	while (right - left > 1)
	{
		int mid = (left + right) >> 1;
		if (check(mid))
		{
			left = mid;
		}
		else
		{
			right = mid;
		}
	}
	if (check(left)) left++;
	if (left != n + 1)
	{
		printf("-1\n%d\n", left);
	}
	else
	{
		printf("0\n");
	}
}

int main()
{
	run();
	return 0;
}
