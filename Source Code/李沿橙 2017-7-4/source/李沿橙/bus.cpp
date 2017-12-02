#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
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
	int a;
	scanf("%d", &a);
	return a;
}

const int maxn = 1005;
const int maxm = 10005;
int n, m, k;
int d[maxn];
int start[maxm];
int from[maxm];
int to[maxm];
int earliest[maxn]; //每个点最早的出发时间（最晚乘客的到达时间）
int arrival[maxn];
int getOff[maxn];

void run()
{
	n = readIn();
	m = readIn();
	k = readIn();
	for (int i = 1; i <= n - 1; i++)
	{
		d[i] = readIn();
	}
	for (int i = 1; i <= m; i++)
	{
		start[i] = readIn();
		from[i] = readIn();
		to[i] = readIn();
		earliest[from[i]] = std::max(earliest[from[i]], start[i]);
		getOff[to[i]]++;
	}
	for (int i = 2; i <= n; i++)
	{
		arrival[i] = std::max(arrival[i - 1], earliest[i - 1]) + d[i - 1];
	}

	while (k--)
	{
		int sum = 0;
		int maxi = 0;
		int maxindex = 0;
		for (int i = n; i >= 2; i--) //由于要求出连续的人等车的前一段路，因此倒着统计 
		{
			if (earliest[i] >= arrival[i]) //车等人，清零 
				sum = 0;
			sum += getOff[i]; //根据分析，应该后写这句代码 
			if (d[i - 1] > 0 && sum > maxi)
			{
				maxi = sum;
				maxindex = i - 1;
			}
		}
		if (!maxindex) break; //没有任何一段路可以加速 
		d[maxindex]--;
		for (int i = 2; i <= n; i++) //维护 
		{
			arrival[i] = std::max(arrival[i - 1], earliest[i - 1]) + d[i - 1];
		}
	}

	for (int i = 2; i <= n; i++)
	{
		arrival[i] = std::max(arrival[i - 1], earliest[i - 1]) + d[i - 1];
	}
	int ans = 0;
	for (int i = 1; i <= m; i++)
	{
		ans += arrival[to[i]] - start[i];
	}
	printf("%d", ans);
}

int main()
{
	run();
	return 0;
}
