#include<bits/stdc++.h>
using namespace std;
int a[10000][6],vis[1000][6],n,ans;
int read()
{
	char c;
	int x=0,w=1;
	c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')w=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=x*10+c-'0';
		c=getchar();
	}
	return x*w;
}
void dfs(int x,int y,int d,int s)
{
	for(int i=1;i<=5;i++)
	{
		if(a[x][i]&&!vis[x][i]&&d+a[x][i]>=0)
		{
			vis[x][i]=1;
			dfs(x,i,d+a[x][i],s-min(0,a[x][i]));
			vis[x][i]=0;
		}
		else if(x+1<=n)dfs(x+1,i,d,s);
	}
	if(x+1<=n)dfs(x+1,y,d,s);
	else if(s>ans)ans=s;
}
int main()
{
	freopen("snakevsblock.in","r",stdin);
	freopen("snakevsblock.out","w",stdout);
	cin>>n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=5;j++)a[i][j]=read();
	dfs(1,3,4,0);
	cout<<ans<<endl;
}
