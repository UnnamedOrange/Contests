#include<cstdio>
#include<iostream>
#define M 1000000007
using namespace std;

int n,m,k;
int color[2004][2004];
bool co1[2004],co2[2004];
int ans=0;
bool check()
{
	int cmp=0,cnt;
	for(int i=1;i<m;++i)
	{
		for(int j=1;j<=k;++j)
			co1[j]=co2[j]=false;
		cnt=0;
		for(int p=1;p<=n;++p)
		{
			for(int q=1;q<=i;++q)
			{
				co1[color[p][q]]=true;
			}
			
		}
		
		for(int z=1;z<=n;++z)
		{
			for(int r=i+1;r<=m;++r)
			{
				co2[color[z][r]]=true;
			}
		}
		for(int j=1;j<=k;++j)
		{
			if(co1[j]!=co2[j])
				++cnt;
		}
		if(i==1)	{cmp=cnt;continue;}
		if(cnt!=cmp)	return false;
	}
	return true;
}

void dfs(int x,int y)
{
	for(int i=1;i<=k;++i)
	{
		color[x][y]=i;
		if(x==n&&y==m)
		{
			if(check())	++ans;
			return;
		}
		if(y==m)
			dfs(x+1,1);
		else
			dfs(x,y+1);
	}
	return;
}

int main()
{
	freopen("photo.in","r",stdin);
	freopen("photo.out","w",stdout);
	
	scanf("%d%d%d",&n,&m,&k);
	
	dfs(1,1);
	printf("%d",ans);
	return 0;
}

//我们可以打暴力！ 
