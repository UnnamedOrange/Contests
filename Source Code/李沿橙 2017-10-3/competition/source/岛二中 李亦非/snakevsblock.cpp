#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int f[205][6][10005];
int vis[15];
int p[202][202],a[202][202];
int ans;
void dfs(int x,int y,int l,int s)
{
	f[x][y][l]=max(f[x][y][l],s);
	ans=max(ans,f[x][y][l]);
	//if(x==2&&l<=20000)
	//printf("%d %d %d %d##\n",x,y,l,s);
	vis[y]++;
	if(vis[y]>=4)
	{
		vis[y]--;
		return;
	}
	if(y<5&&p[x][y]==0)
	{
		if(vis[y+1]==0)
		{
			int ll=l+a[x][y+1];
			if(ll>=0)
			{
				if(a[x][y+1]>0)
					dfs(x,y+1,ll,s);	
				else
					dfs(x,y+1,ll,s-a[x][y+1]);
			}
		}
		else
			dfs(x,y+1,l,s);
	}
	if(y>1&&p[x][y]==0)
	{
		if(vis[y-1]==0)
		{
			int ll=l+a[x][y-1];
			if(ll>=0)
			{	
				if(a[x][y-1]>0)
					dfs(x,y-1,ll,s);	
				else
					dfs(x,y-1,ll,s-a[x][y-1]);
			}
		}
		else
			dfs(x,y-1,l,s);
	}
	
}
int main()
{
	freopen("snakevsblock.in","r",stdin);
	freopen("snakevsblock.out","w",stdout);
	int i,j,k,n,x,y;
	scanf("%d",&n);
	for(i=1;i<=n;i++)
		for(j=1;j<=5;j++)
			scanf("%d",&a[i][j]);
	scanf("%d",&k);
	for(i=1;i<=k;i++)
	{
		scanf("%d%d",&x,&y);
		p[x][y]=1;
	}
	f[1][3][4]=0;
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=5;j++)
		{
			for(k=0;k<=7000;k++)
			{
				if(i!=1||j!=3||k!=4)f[i][j][k]=-1;
				if(i!=1&&k-a[i][j]>=0&&f[i-1][j][k-a[i][j]]>=0)
				{
					if(k-a[i][j]<=7000)
					if(a[i][j]<0)
						f[i][j][k]=f[i-1][j][k-a[i][j]]-a[i][j];
					else
						f[i][j][k]=f[i-1][j][k-a[i][j]];
				}
				//if(i==5&&j==1&&k==2)
				//	printf("*%d*",f[i][j][k]);
				if(f[i][j][k]>=0)
				dfs(i,j,k,f[i][j][k]);
				memset(vis,0,sizeof(vis));
				//if(k<=5&&k>=2)
				//printf("\n");
			}	
		}	
	}
	printf("%d",ans);
	return 0;
}
