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

int limit,nGroup;

namespace Regular
{
	void run()
	{
		std::vector<int> f(limit+1);
		std::vector<int> pre(limit+1);

		f[0]=pre[0]=true;

		for(int i=1; i<=nGroup; i++)
		{
			int num;
			scanf("%d",&num);
			std::vector<int> cost(num+1);
			for(int j=1; j<=num; j++)
			{
				scanf("%d",&cost[j]);
				cost[j]+=cost[j-1];
			}

			for(int start=0; start<num; start++)
			{
				for(int end=start+1; end<=num; end++)
				{
					int t=cost[end]-cost[start];
					for(int k=limit; k>=t; k--)
					{
						f[k]=f[k] || pre[k] || pre[k-t];
					}
				}
			}

			for(int i=0; i<=limit; i++)
			{
				pre[i]=pre[i]||f[i];
			}
		}

		int ans=0;
		for(int i=limit; i>=0; i--)
		{
			if(f[i])
				break;
			else
				ans++;
		}
		printf("%d",ans);
	}
}

void input()
{
	scanf("%d%d",&limit,&nGroup);
}

int main()
{
	input();
	Regular::run();
	return 0;
}
