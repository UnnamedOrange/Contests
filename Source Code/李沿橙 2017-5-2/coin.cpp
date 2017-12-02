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

int k;
int ans;

void input()
{
	scanf("%d",&k);
}

void run()
{
	for(int i=1,day=0; day<k; i++)
	{
		if(day+i<=k)
		{
			ans+=i*i;
			day+=i;
		}
		else
		{
			ans+=i*(k-day);
			day=k;
		}
	}

	printf("%d",ans);
}

int main()
{
#ifndef DEBUG
	freopen("coin.in","r",stdin);
	freopen("coin.out","w",stdout);
#endif
	input();
	run();
	return 0;
}
