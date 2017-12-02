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

int L;
int minDis,maxDis,nStone;
int stone[105];
int path[20000],f[20000];

namespace Regular
{
	void run()
	{
		int l=0;
		int maxInterval=minDis*maxDis/(maxDis-minDis)+minDis+maxDis+1;
		for(int i=1; i<=nStone; i++)
		{
			int temp=std::min(stone[i]-stone[i-1],maxInterval);
			l+=temp;
			path[l]=true;
		}
		memset(f,0x3f,sizeof(f));
		f[0]=0;
		for(int i=1; i<=l+maxDis; i++)
		{
			for(int j=i-maxDis; j<=i-minDis; j++)
			{
				if(j>=0) f[i]=std::min(f[i],f[j]+path[i]);
			}
		}

		int minx=0x7fffffff;
		for(int i=l; i<=l+maxDis; i++)
		{
			minx=std::min(f[i],minx);
		}
		printf("%d",minx);
	}
};

void input()
{
	scanf("%d",&L);
	scanf("%d%d%d",&minDis,&maxDis,&nStone);
	for(int i=1; i<=nStone; i++)
	{
		scanf("%d",&stone[i]);
	}
	std::sort(stone,stone+nStone+1);
}

int main()
{
	input();
	Regular::run();
	return 0;
}
