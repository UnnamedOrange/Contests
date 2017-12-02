#include<iostream>
#include<cstdio>
#include<cstring>

#define N 201

using namespace std;
int map[N][6],d[N][N][N],vis[N][N];
int n,m,ans,cnt;
int dx[3]={0,0,1};
int dy[3]={1,-1,0} ;

void dfs(int x,int y,int tot,int len)
{
	if(x>n)
	{
		int tmp=max(tmp,tot);
		ans=max(ans,tmp);
		return;
	}
	if(len<0) return;
	if(!vis[x][y]) vis[x][y]=1;
	for(int i=0;i<3;i++)
	{
		int xx=x+dx[i],yy=y+dy[i];
		if(vis[xx][yy]) continue;
		if(xx>n+1 || xx<1 || yy>5 || yy<1 || d[xx][y][yy]) continue;
		if(len+map[xx][yy]<0) ans=tot,dfs(xx,yy,tot,len+map[xx][yy]),vis[xx][yy]=0;
		else if(map[xx][yy]<0) dfs(xx,yy,tot-map[xx][yy],len+map[xx][yy]),vis[xx][yy]=0;
		else if(map[xx][yy]>=0)dfs(xx,yy,tot,len+map[xx][yy]),vis[xx][yy]=0; 
		
	}
}

int main()
{
	freopen("snakevsblock.in","r",stdin);
	freopen("snakevsblock.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	  for(int j=1;j<=5;j++)
	    scanf("%d",&map[i][j]);
	scanf("%d",&m);int x,y;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&x,&y);
		d[x][y][y+1]=1;
	}
	dfs(1,3,0,4);
	printf("%d\n",ans);
	return 0;
}
