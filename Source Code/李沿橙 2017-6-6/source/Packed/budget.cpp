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

int limit;
int n;
struct object_base
{
	int cost;
	int value;
	bool child;

	object_base(int cost=0, int value=0, bool child=false):cost(cost),value(value),child(child)
	{
	}
};

struct object:public object_base
{
	object_base child1;
	object_base child2;

	object(int cost=0, int value=0): object_base(cost,value)
	{
	}
} objects[65];

namespace Regular
{
	void run()
	{
		std::vector<int> f(limit+1);
		for(int i=1; i<=n; i++)
		{
			if(objects[i].child==true) continue; //如果是子件，就不管
			std::vector<int> temp(limit+1);
			int cost;
			int value;

			cost=objects[i].cost;
			value=objects[i].value;
			for(int j=limit; j>=cost; j--)
			{
				temp[j]=std::max(temp[j],f[j-cost]+value);
			}

			cost=objects[i].cost+objects[i].child1.cost;
			value=objects[i].value+objects[i].child1.value;
			for(int j=limit; j>=cost; j--)
			{
				temp[j]=std::max(temp[j],f[j-cost]+value);
			}

			cost=objects[i].cost+objects[i].child2.cost;
			value=objects[i].value+objects[i].child2.value;
			for(int j=limit; j>=cost; j--)
			{
				temp[j]=std::max(temp[j],f[j-cost]+value);
			}

			cost=objects[i].cost+objects[i].child1.cost+objects[i].child2.cost;
			value=objects[i].value+objects[i].child1.value+objects[i].child2.value;
			for(int j=limit; j>=cost; j--)
			{
				temp[j]=std::max(temp[j],f[j-cost]+value);
			}

			for(int i=0; i<=limit; i++)
			{
				f[i]=std::max(f[i],temp[i]);
			}
		}
		printf("%d\n",f[limit]);
	}
	void input()
	{
		scanf("%d%d",&limit,&n);
		limit/=10; //优化：10的整数倍
		for(int i=1; i<=n; i++)
		{
			int cost;
			int importance;
			int parent;
			scanf("%d%d%d",&cost,&importance,&parent);
			objects[i].cost=cost/10;
			objects[i].value=cost*importance;
			objects[i].child=parent;
			if(parent)
			{
				if(!objects[parent].child1.cost)
				{
					objects[parent].child1=objects[i];
				}
				else if(!objects[parent].child2.cost)
				{
					objects[parent].child2=objects[i];
				}
			}
		}
	}
}

int main()
{
	Regular::input();
	Regular::run();
	return 0;
}
