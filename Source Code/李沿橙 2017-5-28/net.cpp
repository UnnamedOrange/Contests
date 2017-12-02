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

struct ufs
{
	std::vector<int> parent;
	int size;

	ufs(int size):size(size),parent(size+1)
	{
		for(int i=1; i<=size; i++)
		{
			parent[i]=i;
		}
	}

	int find(int x)
	{
		if(parent[x]==x) return x;
		return parent[x]=find(parent[x]);
	}

	void unite(int x,int y)
	{
		int px=find(x);
		int py=find(y);
		parent[py]=px;
	}

	bool judge(int x,int y)
	{
		int px=find(x);
		int py=find(y);
		return px==py;
	}
};

const char* result[]=
{
	"FAIL","SUCCESS"
};
int n,d;
std::vector<std::vector<int> > table;

namespace Regular
{
	void save(int index, ufs &u, std::vector<bool> &status)
	{
		status[index]=true;
		for(int i=0; i<table[index].size(); i++)
		{
			if(status[table[index][i]])
			{
				u.unite(index,table[index][i]);
			}
		}
	}

	bool link(int x, int y, ufs &u, std::vector<bool> &status)
	{
		return status[x] && status[y] && u.judge(x,y);
	}

	void run()
	{
		ufs u(n);
		std::vector<bool> status(n+1,false);
		char ins;
		while(~scanf(" %c ",&ins))
		{
			if(ins=='O')
			{
				int param;
				scanf("%d",&param);
				save(param,u,status);
			}
			else if(ins=='S')
			{
				int param1,param2;
				scanf("%d%d",&param1,&param2);
				printf("%s\n",result[link(param1,param2,u,status)]);
			}
		}
	}
}

namespace init
{
	struct Point
	{
		int x;
		int y;
		Point(int x=0,int y=0):x(x),y(y)
		{

		}

		friend bool is_friend(const Point a,const Point b)
		{
#define SQUARE(x) (((long long)(x))*((long long)(x)))
			long long dis=SQUARE(a.x-b.x)+SQUARE(a.y-b.y);
			return dis<=(long long)d;
#undef SQUARE
		}

		void input()
		{
			scanf("%d%d",&x,&y);
		}
	};
	void input()
	{
		scanf("%d%d",&n,&d);
		d*=d; //d为距离平方（最大4亿）

		table.resize(n+1);
		std::vector<Point> computer(n+1);
		for(int i=1; i<=n; i++)
		{
			computer[i].input();
		}

		//建图
		for(int i=1; i<=n; i++)
		{
			for(int j=i+1; j<=n; j++)
			{
				if(is_friend(computer[i],computer[j]))
				{
					table[i].push_back(j);
					table[j].push_back(i);
				}
			}
		}
	}
}

int main()
{
	init::input();
	Regular::run();
	return 0;
}
