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

struct container
{
	int index;
	int before;
	int after;
	double rate;
	double sub;

	container()
	{
		index=before=after=0;
		sub=rate=0;
	}

	void input()
	{
		scanf("%d%d%d",&index,&before,&after);
		rate=(double)after/before;
	}
} c[105];
int n;

bool comp1(const container &a, const container &b)
{
	return a.rate>b.rate;
}

bool comp2(const container &a, const container &b)
{
	return a.sub>b.sub;
}

bool comp3(const container &a, const container &b)
{
	return a.rate<b.rate;
}

int main()
{
	scanf("%d",&n);
	for(int i=0; i<n; i++)
	{
		c[i].input();
	}
	std::sort(c,c+n,comp1);
	for(int i=1; i<n; i++)
	{
		c[i].sub=c[i-1].rate-c[i].rate;
	}
	std::sort(c,c+n,comp2);
	int maxindex = c[0].index;
	std::sort(c,c+n,comp3);

	int ans=0;
	for(int i=0; i<n; i++)
	{
		if(c[i].index==maxindex)
		{
			ans=i+1;
			printf("%d\n",n-ans);
		}
	}
	for(int i=ans; i<n; i++)
	{
		printf("%d\n",c[i].index);
	}
	printf("%d\n",ans);
	for(int i=0; i<ans; i++)
	{
		printf("%d\n",c[i].index);
	}
	return 0;
}
