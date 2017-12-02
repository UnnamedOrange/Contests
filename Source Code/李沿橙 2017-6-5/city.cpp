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

const int maxn=155;
int n,r;
int rect[maxn][maxn];
int dis[maxn][maxn];
int ans[maxn][maxn];

namespace BFS
{
	const int vecx[]= {1,-1,0,0};
	const int vecy[]= {0,0,1,-1};
	struct node
	{
		int x,y;
		int length;
		node(int x,int y,int length):x(x),y(y),length(length)
		{
		}
	};
	int bfs(int bx,int by)
	{
		std::vector<std::vector<bool> > vis(n+1);
		for(int i=1; i<=n; i++)
		{
			vis[i].resize(n+1);
		}
		std::queue<node> Queue;
		Queue.push(node(bx,by,0));
		vis[bx][by]=true;
		while(Queue.size())
		{
			node cnt=Queue.front();
			Queue.pop();

			for(int i=0; i<4; i++)
			{
				int newx=cnt.x+vecx[i];
				int newy=cnt.y+vecy[i];
				int newLen=cnt.length+1;
				if(newx>0 && newx<=n && newy>0 && newy<=n && !vis[newx][newy])
				{
					Queue.push(node(newx,newy,newLen));
					vis[newx][newy]=true;

					if(rect[newx][newy])
					{
						return newLen;
					}
				}
			}
		}
		return 0;
	}

	void run()
	{
		int a;
		scanf("%d",&a);
		while(a--)
		{
			memset(ans,0,sizeof(ans));
			memset(dis,0,sizeof(dis));

			scanf("%d%d",&n,&r);
			for(int i=1; i<=n; i++)
			{
				for(int j=1; j<=n; j++)
				{
					scanf("%d",&rect[i][j]);
				}
			}

			for(int i=1; i<=n; i++)
			{
				for(int j=1; j<=n; j++)
				{
					if(!rect[i][j])
					{
						dis[i][j]=bfs(i,j);
					}
				}
			}

			for(int i=1; i<=n; i++)
			{
				for(int j=1; j<=n; j++)
				{
					for(int x=std::max(1,i-r); x<=std::min(n,i+r); x++)
					{
						for(int y=std::max(1,j-r); y<=std::min(n,j+r); y++)
						{
//						if(x>0 && y>0 && x<=n && y<=n)
//						{
							ans[x][y]+=dis[i][j];
//						}
						}
					}
				}
			}

			for(int i=1; i<=n; i++)
			{
				for(int j=1; j<=n; j++)
				{
					printf("%d ",ans[i][j]);
				}
				puts("");
			}
		}
	}
}

namespace Regular
{
	void run()
	{

	}
	void input()
	{

	}
}

int main()
{
#ifndef DEBUG
	freopen("city.in","r",stdin);
	freopen("city.out","w",stdout);
#endif
	Regular::input();
	BFS::run();
	return 0;
}
