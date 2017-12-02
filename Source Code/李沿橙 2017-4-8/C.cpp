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

struct area
{
	int x1;
	int x2;
	bool operator <(const area &b) const
	{
		if(x1==b.x1) return x2<b.x2;
		return x1<b.x1;
	}
} areas[1005];
int n;
int ans;

void input(int i,char *buffer,bool x1)
{
	if(!buffer || buffer==(char*)1) return;
	if(!x1) sscanf(buffer,"%d",&areas[i].x1);
	else sscanf(buffer,"%d",&areas[i].x2);
	n=i+1;
	input(i+1,strchr(buffer,',')+1,x1);
}

int main()
{
	char buffer[16384]= {0};
	std::cin.getline(buffer,16384);
	input(0,buffer,false);
	std::cin.getline(buffer,16384);
	input(0,buffer,true);
	printf("%d ",n);

	std::sort(areas,areas+n);
	int count_=0;
	std::priority_queue<int,std::vector<int>,std::greater<int> > pq;
	for(int i=0; i<n; i++)
	{
		int in=areas[i].x1;
		int out=areas[i].x2;
		while(!pq.empty())
		{
			if(pq.top()<=in)
			{
				pq.pop();
				count_--;
			}
			else
			{
				break;
			}
		}
		count_++;
		ans=std::max(ans,count_);
		pq.push(out);
	}
	printf("%d",ans);
	return 0;
}
