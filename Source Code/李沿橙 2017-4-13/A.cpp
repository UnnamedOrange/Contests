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
using std::cin;
using std::cout;

int main()
{
	int a;
	scanf("%d",&a);
	while(a--)
	{
		int times=0;
		scanf("%d",&times);
		int ans=0;
		int t=1;
		int dead=0;
		for(int i=0; i<times; i++)
		{
			int num=0;
			scanf("%d",&num);
			for(; ans<num && t<=60; t++)
			{
				if(dead)
				{
					dead--;
				}
				else
				{
					ans++;
				}
			}
			dead=3;
			for(; dead && t<=60; t++)
			{
				if(dead)
				{
					dead--;
				}
				else
				{
					ans++;
				}
			}
		}
		for(; t<=60; t++)
		{
			if(dead)
			{
				dead--;
			}
			else
			{
				ans++;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
