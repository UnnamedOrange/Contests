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
#include <map>
#include <set>
using std::cin;
using std::cout;
using std::endl;

int n;
struct ship
{
	int Time;
	int people;
	std::vector<int> country;

	ship(int Time,int people):Time(Time),people(people)
	{}
	void input()
	{
		for(int i=0; i<people; i++)
		{
			int in;
			scanf("%d",&in);
			country.push_back(in);
		}
	}
};
std::vector<ship> ships;

const int day=86400;
int count_country[100005];
int count_all;
int oldest;

void Increase(int country)
{
	if(!count_country[country]) count_all++;
	count_country[country]++;
}
void Decrease(int country)
{
	count_country[country]--;
	if(!count_country[country]) count_all--;
}

void run_Regular()
{
	for(int i=0; i<n; i++)
	{
		while(!(ships[i].Time - day < ships[oldest].Time))
		{
			for(int j=0; j<ships[oldest].people; j++)
			{
				Decrease(ships[oldest].country[j]);
			}
			oldest++;
		}

		for(int j=0; j<ships[i].people; j++)
		{
			Increase(ships[i].country[j]);
		}
		printf("%d\n",count_all);
	}
}

void input()
{
	scanf("%d",&n);
	for(int i=0; i<n; i++)
	{
		int Time,people;
		scanf("%d%d",&Time,&people);
		ships.push_back(ship(Time,people));
		ships[i].input();
	}

//	for(int i=0; i<n; i++)
//	{
//		printf("ship %d %d people at %d time\n",i,ships[i].people,ships[i].Time);
//		for(int j=0; j<ships[i].country.size(); j++)
//		{
//			printf("%d ",ships[i].country[j]);
//		}
//		puts("");
//	}
}

int main()
{
#ifndef DEBUG
	freopen("port.in","r",stdin);
	freopen("port.out","w",stdout);
#endif
	input();
	run_Regular();
	return 0;
}
