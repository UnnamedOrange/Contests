#include<cstdio>
#define max(x,y) (x)>(y)?(x):(y)
using namespace std;
int u[10]={0,1,0,0};
int v[10]={0,0,1,-1};
int a[300][10];
bool b[300][10],c[300][10];
int ans,n,m;
void dfs(int x,int y,int len,int sum)
{
	if(y<0||y>5)
	return;
	if(x==n+1)
	{
		ans=max(ans,sum);
		return;
	}
	c[x][y]=1;
	for(int i=1;i<=3;i++)
	{
		int p=x+u[i],q=y+v[i];
		if(c[p][q])
		continue;
		if(i==2&&b[x][y]==1)
		continue;
		if(i==3&&b[p][q]==1)
		continue;
		if(a[p][q]<0)
		{
			if(len+a[p][q]>=0)
			dfs(p,q,len+a[p][q],sum-a[p][q]);
			else 
			ans=max(ans,sum);
		}
		else
		dfs(p,q,len+a[p][q],sum);
	}
	c[x][y]=0;
}
int main()
{
	freopen("snakevsblock.in","r",stdin);
	freopen("snakevsblock.out","w",stdout);
	int x,y;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=5;j++)
	scanf("%d",&a[i][j]);
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&x,&y);
		b[x][y]=1;
	}
	dfs(1,3,4,0);
	printf("%d\n",ans);
	return 0;
}
	
	
