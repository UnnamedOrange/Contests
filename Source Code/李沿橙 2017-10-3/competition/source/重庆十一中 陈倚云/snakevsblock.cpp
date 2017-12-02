#include <iostream> 
#include <cstdio> 
#include <fstream> 
#include <algorithm> 
#include <cmath> 
#include <deque> 
#include <vector> 
#include <queue> 
#include <string> 
#include <cstring> 
#include <map> 
#include <stack> 
#include <set> 
using namespace std;
inline int read(){
    int X=0,w=1; char ch=0;
    while(ch<'0' || ch>'9') {if(ch=='-') w=-1;ch=getchar();}
    while(ch>='0' && ch<='9') X=(X<<3)+(X<<1)+ch-'0',ch=getchar();
    return X*w;
}
int sx[4]={0,0,1,-1};
int sy[4]={1,-1,0,0};
int maps[205][10],n,m,x,y,ans;
bool vis[205][10][2];
bool isu[205][10];
void dfs(int x,int y,int life,int point){
	if(x==n+1){
		ans=max(ans,point);
		return ;
	} 
	if(life+maps[x][y]<0){
		ans=max(ans,point);
		return;
	}
	isu[x][y]=1;
	for(int i=0;i<4;i++){
		if(sy[i]==1 && vis[x][y][1]==1) continue;
		if(sy[i]==-1 && vis[x][y][0] ==1 ) continue;
		int nx=x+sx[i],ny=y+sy[i];
		if(nx<=n+1&& nx>0 && ny<=5 &&ny>0 && isu[nx][ny]==0 ){
			if(maps[x][y]>0)	dfs(nx,ny,life+maps[x][y],point);
			else 	dfs(nx,ny,life+maps[x][y],point-maps[x][y]);
		} 
	}
	isu[x][y]=0;
}
int main(){
	freopen("snakevsblock.in","r",stdin);
	freopen("snakevsblock.out","w",stdout);
	memset(vis,0,sizeof(vis));
	memset(isu,0,sizeof(isu));
	n=read();
	for(int i=1;i<=n;i++)for(int j=1;j<=5;j++) maps[i][j]=read();
	m=read();
	for(int i=1;i<=m;i++){
		x=read();
		y=read();
		vis[x][y][1]=1;
		vis[x][y+1][0]=1;
	}
	dfs(1,3,4,0);
	printf("%d",ans);
	return 0;
}
