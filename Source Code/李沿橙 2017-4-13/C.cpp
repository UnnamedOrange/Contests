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

struct area
{
	int x;
	int y;

	area(int x,int y):x(x),y(y)
	{

	}

	friend std::istream& operator >>(std::istream& i,std::vector<area>& v)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		v.push_back(area(x,y));
		return i;
	}

	bool operator <(const area b) const
	{
		if(x==b.x) return y<b.y;
		return x<b.x;
	}
};
std::vector<area> areas;
int n;

int main()
{
	scanf("%d",&n);
	for(int i=0; i<n; i++)
	{
		cin>>areas;
	}
	std::sort(areas.begin(),areas.end());

	int maxright=areas[0].y;
	for(int i=0; i<n; i++)
	{
		if(areas[i].x>maxright)
		{
			printf("no");
			return 0;
		}
		maxright=std::max(maxright,areas[i].y);
	}
	printf("%d %d",areas[0].x,maxright);
	return 0;
}
