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

const int vecx[]= {1,-1,0,0};
const int vecy[]= {0,0,1,-1};
int n,m;
std::vector<std::vector<int> > rect;

namespace Regular
{
	std::vector<std::vector<bool> > vis;
	std::vector<std::vector<int> > able;
	std::vector<bool> t_able;
	void dfs(int x,int y)
	{
		if(vis[x][y]) return;
		vis[x][y]=true;
		for(int i=0; i<4; i++)
		{
			int newx=x+vecx[i];
			int newy=y+vecy[i];
			if(newx>0 && newx<=n && newy>0 && newy<=m && rect[newx][newy]<rect[x][y])
			{
				dfs(newx,newy);
			}
		}
	}

	void run()
	{
		vis.resize(n+1);
		able.resize(m+1);
		t_able.resize(m+1);
		for(int i=1; i<=m; i++)
		{
			for(int j=1; j<=n; j++)
			{
				vis.clear();
				vis.resize(m+1);
			}
			dfs(1,i);
			for(int j=1; j<=m; j++)
			{
				if(vis[n][j])
				{
					able[i].push_back(j);
					t_able[j]=true;
				}
			}
		}

		int disabled=0;
		for(int i=1; i<m; i++)
		{
			if(!t_able[i])
			{
				disabled++;
			}
		}

		if(disabled)
		{
			printf("0\n%d\n",disabled);
		}
		else
		{
			printf("1\n");
			printf("1\n");
		}
	}
}

namespace Init
{
	void input()
	{
		scanf("%d%d",&n,&m);
		rect.resize(n+1);
		for(int i=1; i<=n; i++)
		{
			rect[i].resize(m+1);
			for(int j=1; j<=m; j++)
			{
				scanf("%d",&rect[i][j]);
			}
		}
	}
}

int main()
{
	Init::input();
	Regular::run();
	return 0;
}
