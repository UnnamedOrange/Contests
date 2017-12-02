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
	scanf("%d",&a);
	return a;
}

const int maxn=200005;
int n, k, p;
std::vector<int> styleSet[55];

struct RMQ
{
	int f[19][maxn];

	RMQ()
	{
	}
	void input(int i)
	{
		f[0][i] = readIn();
	}
	void init()
	{
		for(int k = 1; 1 << k <= n; k++)
		{
			for(int i = 1; i + (1 << k) - 1 <= n; i++)
			{
				f[k][i] = std::min(f[k-1][i], f[k-1][i + (1 << (k - 1))]);
			}
		}
	}
	int query(int l, int r)
	{
		int length=r-l+1;
		int k = 0;

		while(1<<(k+1) <= length) k++;
		return std::min(f[k][l], f[k][r-(1<<k)+1]);
	}
} rmq;

void run()
{
	n=readIn();
	k=readIn();
	p=readIn();
	for(int i=1; i<=n; i++)
	{
		styleSet[readIn()].push_back(i);
		rmq.input(i);
	}
	rmq.init();

	long long ans = 0;
	for(int i=0; i<k; i++)
	{
		int size = styleSet[i].size();
		int right = size-1;
		int lastLeft = 0;
		for(int j = 0; j < size - 1; j++)
		{
			if(rmq.query(styleSet[i][j], styleSet[i][j+1]) <= p)
			{
				ans += (j - lastLeft + 1) * (right - j);
				lastLeft = j + 1;
			}
		}
	}
	cout<<ans;
}

int main()
{
	run();
	return 0;
}
