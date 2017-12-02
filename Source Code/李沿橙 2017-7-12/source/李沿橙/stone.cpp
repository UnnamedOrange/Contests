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
	int a;
	scanf("%d",&a);
	return a;
}

const int maxn = 50005;
int l, n, m;
int river[maxn];

bool check(int interval)
{
	int count_ = 0;
	int lastPos = 0;
	for(int i = 0; i <= n; i++)
	{
		if(river[i] - lastPos >= interval)
		{
			lastPos = river[i];
		}
		else
		{
			count_++;
		}
	}
	return count_ <= m;
}

void run()
{
	l = readIn();
	n = readIn();
	m = readIn();
	for(int i = 0; i < n; i++)
	{
		river[i] = readIn();
	}
	river[n] = l;

	int left = 0, right = l;
	while(right - left > 1)
	{
		int mid = left + (right - left) / 2;
		if(check(mid))
		{
			left = mid;
		}
		else
		{
			right = mid;
		}
	}
	if(check(right)) left++;
	printf("%d\n", left);
}

int main()
{
	run();
	return 0;
}
