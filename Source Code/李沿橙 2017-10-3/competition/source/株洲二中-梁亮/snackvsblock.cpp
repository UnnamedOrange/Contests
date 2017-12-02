#include<cstdio>
#include<iostream>
#include<cmath>
#include<cstdlib>
using namespace std;

int area[204][10];//actually 200 5
int n,m;
int banx[204],bany[204];
bool noway[204][10];
bool vis[204][10];
int len=4,sum=0;
int maxs=0;
int bani;
void input()
{
	bool point=false,block=false;
	bool foundep=false,foundsb=false;
	int endp,stab;
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=5;++j)
		{
			scanf("%d",&area[i][j]);
		}
	}
	scanf("%d",&m);
	for(int i=1;i<=m;++i)
	{
		scanf("%d",&banx[i],&bany[i]);
		noway[banx[i]][bany[i]]=true;
	}
	return ;
}

bool ban(int x)
{
	for(int i=1;i<=m;++i)
		if(banx[i]==x)
			{bani=i;return true;}
	return false;
}

void move(int aa,int bb)
{
	len+=area[aa][bb];
	if(area[aa][bb]<0)
		sum-=area[aa][bb];
	return;
}

void remove(int aa,int bb)
{
	len-=area[aa][bb];
	if(area[aa][bb]<0)
		sum+=area[aa][bb];
	return;
}

void dfs(int x,int y)
{
	if(len<0)	return;
	if(sum>maxs)
	{
		maxs=sum;
	}
	if(y>1&&noway[x][y-1]==false&&vis[x][y-1]==false)
	{
		int t=area[x][y-1];
		vis[x][y-1]=true;
		len+=area[x][y-1];
		if(area[x][y-1]<0)
			sum-=area[x][y-1];
		area[x][y-1]=0;
		dfs(x,y-1);
		area[x][y-1]=t;
		vis[x][y-1]=false;
		len-=area[x][y-1];
		if(area[x][y-1]<0)
			sum+=area[x][y-1];
	}
	if(y<5&&noway[x][y]==false&&vis[x][y+1]==false)
	{
		int t=area[x][y+1];
		vis[x][y+1]=true;
		len+=area[x][y+1];
		if(area[x][y+1]<0)
			sum-=area[x][y+1];
		area[x][y+1]=0;
		dfs(x,y+1);
		area[x][y+1]=t;
		vis[x][y+1]=false;
		len-=area[x][y+1];
		if(area[x][y+1]<0)
			sum+=area[x][y+1];
	}
	if(x<n)
	{
		int t=area[x+1][y];
		len+=area[x+1][y];
		if(area[x+1][y]<0)
			sum-=area[x+1][y];
		area[x+1][y]=0;
		dfs(x+1,y);
		area[x+1][y]=t;
		len-=area[x+1][y];
		if(area[x+1][y]<0)
			sum+=area[x+1][y];
	}
	return;
}

int main()
{
	freopen("snackvsblock.in","r",stdin);
	freopen("snackvsblock.out","w",stdout);
	input();
	if(n>=12)
	{
		int happy=4;
		for(int i=1;i<=n;++i)
			for(int j=1;j<=5;++j)
				if(area[i][j]>0)
					happy+=area[i][j];
		printf("%d",happy);
	}
	dfs(1,3);
	printf("%d",maxs);
	return 0;
}
