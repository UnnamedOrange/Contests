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

const int maxn = 55;
int n, k, p;

void run()
{
	n = readIn();
	k = readIn();
	p = readIn();

	int bestPos = 0; //咖啡店应尽量靠右，保存咖啡店的最佳地址
	int times[maxn] = { 0 }; //保存同色客栈出现的次数
	int lastAppear[maxn] = { 0 }; //保存某种颜色客栈上一次出现的位置
	int availableTimes[maxn] = { 0 }; //保存某种颜色客栈可形成一对的个数
	long long ans = 0;
	for (int i = 1; i <= n; i++)
	{
		int style = readIn();
		int cost = readIn();
		if (cost <= p)
		{
			bestPos = i; //维护咖啡店位置
		}

		if (bestPos >= lastAppear[style]) //若bestPos在上一次这个颜色的客栈还要后面一点，就可以保证有times[style]个客栈可配对(此时times还没有更新)
			availableTimes[style] = times[style];

		lastAppear[style] = i; //维护上一次出现的位置
		times[style]++; //维护出现的次数
		ans += availableTimes[style]; //计算答案
	}
	cout << ans << endl;
}

int main()
{
	run();
	return 0;
}
