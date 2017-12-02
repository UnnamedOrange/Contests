#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstring>
using namespace std;
int i,j,k;
int n,m,x,y;
int mp[205][7];
int d[205][6];
bool bb[205][6];
int mw=0;
void search(int x,int y,int b,int w)
{
	if(b>=0 && x<=n)
	{
		if(d[x][y]==0 && y+1<6 && bb[x][y+1]) 
		{
			if(mp[x][y+1]<0)  bb[x][y]=false,search(x,y+1,b+mp[x][y+1],w-mp[x][y+1]),bb[x][y]=true;
			if(mp[x][y+1]>=0) bb[x][y]=false,search(x,y+1,b+mp[x][y+1],w),bb[x][y]=true;
		}
		if(d[x][y-1]==0 && y-1>0 && bb[x][y-1]) 
		{
			if(mp[x][y-1]<0)  bb[x][y]=0,search(x,y-1,b+mp[x][y-1],w-mp[x][y-1]),bb[x][y]=true;
			if(mp[x][y-1]>=0) bb[x][y]=0,search(x,y-1,b+mp[x][y-1],w),bb[x][y]=true;
		}
		if(mp[x+1][y]<0)search(x+1,y,b+mp[x+1][y],w-mp[x+1][y]);
		if(mp[x+1][y]>=0)search(x+1,y,b+mp[x+1][y],w);
	}
	else 
	{
		if(mp[x][y]<0 && w+mp[x][y]>mw) mw=w+mp[x][y];
		if(mp[x][y]>=0 && w>mw) mw=w; 
	}

	
}
int main()
{
	freopen("snakevsblock.in","r",stdin);
	freopen("snakevsblock.out","w",stdout);
    cin>>n;
    for(i=1;i<=n;i++)
    	for(j=1;j<=5;j++) cin>>mp[i][j];
	cin>>m;
	for(i=1;i<=m;i++)
	{
		cin>>x>>y;
		d[x][y]=1;
	}
	for(i=1;i<=20;i++)
	for(j=1;j<=5;j++) bb[i][j]=1;
	search(1,3,4,0);
    cout<<mw;
	return 0;
}
