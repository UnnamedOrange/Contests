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

int r,c;
int ex,ey;
int rect[205][205];
bool vis[205][205];
const int vecx[]= {1,-1,0,0};
const int vecy[]= {0,0,1,-1};

void dfs(int x,int y)
{
	if(vis[x][y]) return;
	vis[x][y]=true;
	for(int i=0; i<4; i++)
	{
		int newx=x+vecx[i];
		int newy=y+vecy[i];
		if(newx>0 && newx<=r && newy>0 && newy<=c && rect[newx][newy]<=rect[x][y])
		{
			dfs(newx,newy);
		}
	}
}

void work()
{
	scanf("%d%d",&r,&c);
	for(int i=1; i<=r; i++)
	{
		for(int j=1; j<=c; j++)
		{
			scanf("%d",&rect[i][j]);
		}
	}
	scanf("%d%d",&ex,&ey);
	int n=0;
	scanf("%d",&n);
	while(n--)
	{
		int sx=0,sy=0;
		scanf("%d%d",&sx,&sy);
		if(!vis[sx][sy] && !vis[ex][ey])
		{
			dfs(sx,sy);
		}
	}
	printf("%s\n",vis[ex][ey]?"Yes":"No");
}

int main()
{
	int a;
	scanf("%d",&a);
	while(a--)
	{
		memset(vis,0,sizeof(vis));
		work();
	}
	return 0;
}
