#include<algorithm>
#include<iostream>
#include<cstring>
#include<string>
#include<cctype>
#include<vector>
#include<cstdio>
#include<cmath>

using namespace std;
const int L=205;
int n,m,p[L][L],b[L][L]={0},dp[L][L]={0},ans=-1,s=0,f[L][L]={0};
void F(int x,int y,int l)
{
	if(l<0||x>n) return;
	if(s>ans) ans=s;
  	if(x-1>=1&&f[x-1][y]==0) 
	{
		s+=fabs(p[x-1][y]);
		f[x-1][y]=1;
		F(x-1,y,l+p[x-1][y]);
		s-=fabs(p[x-1][y]);
	}
	if(x+1<=n&&f[x+1][y]==0)
	{
		s+=fabs(p[x+1][y]);
		f[x+1][y]=1;
		F(x+1,y,l+p[x+1][y]);
		s-=fabs(p[x+1][y]);	
	}
	if(y-1>=1&&f[x][y-1]==0) 
	{
		s+=fabs(p[x][y-1]);
		f[x][y-1]=1;
		F(x,y-1,l+p[x][y-1]);
		s-=fabs(p[x][y-1]);	
	}
	if(y+1<=5&&f[x][y+1]==0) 
	{
		s+=fabs(p[x][y+1]);
		f[x][y+1]=1;
		F(x,y+1,l+p[x][y+1]);
		s-=fabs(p[x][y+1]);	
	}
	return;
}
int main()
{
	freopen("snakevsblock .in","r",stdin);
	freopen("snakevsblock .out","w",stdout);
	int x,y;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=5;j++)
			cin>>p[i][j];		
	}
	cin>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>x>>y;
		b[x][y]=b[y][x]=1;
	}
	F(1,3,4);
	cout<<ans;
	fclose(stdin);
	fclose(stdout);
	return 0;
}
