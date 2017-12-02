#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;
int fa[1000005][22];
int deep[1000005];
int tot,m;
int lca(int x,int y)
{
	if(deep[x]<deep[y])swap(x,y);
	for(int i=20;i>=0;--i)
	{
		if(deep[fa[x][i]]>=deep[y])
		{
			x=fa[x][i];
		}
	}
	if(x==y)return x;
	for(int i=20;i>=0;--i)
	{
		if(fa[x][i]!=fa[y][i])
		{
			x=fa[x][i];
			y=fa[y][i];
		}
	}
	return fa[x][0];
}
int main()
{
	freopen("fibonacci.in","r",stdin);
	freopen("fibonacci.out","w",stdout);
	int t1=1,t2=1;
	fa[1][0]=0;deep[1]=1;
	fa[2][0]=1;deep[2]=2;
	fa[3][0]=1;deep[3]=2;
	tot=4;
	while(tot<=1000000)
	{
		t1=t1+t2;
		swap(t1,t2);
		for(int i=1;i<=t2&&tot<=1000000;++i,++tot)
		fa[tot][0]=i,deep[tot]=deep[i]+1;
	}
	for(int i=1;i<=20;++i)
	for(int j=1;j<=1000000;++j)
	fa[j][i]=fa[fa[j][i-1]][i-1];
	scanf("%d",&m);
	for(int i=1;i<=m;++i)
	{
		scanf("%d%d",&t1,&t2);
		printf("%d\n",lca(t1,t2));
	}
	return 0;
}
