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
	int a=0;
	scanf("%d",&a);
	return a;
}

int n;

namespace Regular
{
	void run()
	{
		std::multiset<int> Set;
		for(int i=1; i<=n; i++)
		{
			Set.insert(readIn());
		}
		std::multiset<int>::iterator t;
		int last=-1;
		for(t=Set.begin(); t!=Set.end(); t++)
		{
			if(*t!=last)
			{
				printf("%d %d\n",*t,Set.count(*t));
				last=*t;
			}
		}
	}
	void input()
	{
		n=readIn();
	}
}

int main()
{
	Regular::input();
	Regular::run();
	return 0;
}
