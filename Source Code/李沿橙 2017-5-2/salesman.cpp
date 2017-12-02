#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <set>
using std::cin;
using std::cout;
using std::endl;

int n;
std::vector<int> distance;
std::vector<int> tireness;
std::vector<std::vector<int> > f;

void input()
{
	scanf("%d",&n);
	distance.resize(n+1);
	tireness.resize(n+1);
	for(int i=1; i<=n; i++)
	{
		scanf("%d",&distance[i]);
	}
	for(int i=1; i<=n; i++)
	{
		scanf("%d",&tireness[i]);
	}
	f.resize(n+1);
	for(int i=1; i<=n; i++)
	{
		f[i].resize(n+1);
	}
}

void run()
{
	//f[i][j]推销了i家，走到了j深的那一家
	for(int i=1; i<=n; i++)
	{
		f[1][i]=tireness[i]+2*distance[i];
	}

	for(int i=2; i<=n; i++)
	{
		for(int j=2; j<=i; j++)
		{
			for(int k=j-1; k<i; k++)
			{
				f[j][i]=std::max(f[j][i],f[j-1][k]+2*(distance[i]-distance[k])+tireness[i]);
			}
		}
	}

	for(int i=1; i<=n; i++)
	{
		printf("%d\n",*max_element(f[i].begin(),f[i].end()));
	}
}

int main()
{
#ifndef DEBUG
	freopen("salesman.in","r",stdin);
	freopen("salesman.out","w",stdout);
#endif
	input();
	run();
	return 0;
}
