#include<cstdio>
#include<iostream>

using namespace std;
bool edge[10004][10004];
int n,m,k;
bool book[10004],found;
int fa[10004];
int cnt=0;
void input()
{
	int u,v;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i)
	{
		scanf("%d%d",&u,&v);
		edge[u][v]=edge[v][u]=1;
	}
	return;
}

int findf(int x)
{
	if(fa[x]==x)	return x;
	return fa[x]=findf(fa[x]);
}

void search(int now,int to)
{
	if(now==to)
	{
		found=true;
		for(int i=1;i<=n;++i)
			if(book[i]==true)
			{
				fa[findf(i)]=fa[to];
				book[i]=false;
			}
		return;
	}
	for(int i=1;i<=n;++i)
	{
		if(edge[now][i]&&book[i]==false)
		{
			book[i]=true;
			search(i,to);
			if(found)	return;
			book[i]=false;
		}
	}
}

int main()
{
	freopen("ping.in","r",stdin);
	freopen("ping.out","w",stdout);
	input();
	scanf("%d",&k);
	int u,v;
	for(int i=1;i<=n;++i)
		fa[i]=i;
	for(int i=1;i<=k;++i)
	{
		scanf("%d%d",&u,&v);
		found=false;
		book[u]=true;
		if(findf(u)==findf(v))
			continue;
		fa[findf(u)]=findf(v);
		search(u,v);
		book[u]=false;
	}
	for(int i=1;i<=n;++i)
	{
		if(book[findf(i)]==false&&fa[i]!=i)
		{
			++cnt;
			book[fa[i]]=true;
		}
	}
	printf("%d\n",cnt);
	for(int i=1;i<=n;++i)
		if(book[i]==true)
			printf("%d ",i);
	return 0;
}
