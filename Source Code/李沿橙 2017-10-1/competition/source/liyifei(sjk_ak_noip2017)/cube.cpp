#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int fa[30303],re[30303],sz[30303];
int find_set(int x)
{
	int y=x,z=y,tmp=0,t;
	while(fa[x]!=x)
	{
		tmp+=re[x];
		x=fa[x];
	}
	while(fa[y]!=x)
	{
		t=tmp;
		tmp-=re[y];
		re[y]=t;
		y=fa[y];
		fa[z]=x;
		z=y;
	}
	return x;
}
void union_set(int x,int y)
{
	int xx=find_set(x),yy=find_set(y);
	fa[xx]=yy;
	sz[yy]+=sz[xx];
	re[xx]=sz[xx];
}
int getit(int x)
{
	int tmp=0,tmp2,y=x,z=y,t;
	while(fa[x]!=x)
	{
		tmp+=re[x];
		x=fa[x];
	}
	tmp2=tmp;
	while(fa[y]!=x)
	{
		t=tmp;
		tmp-=re[y];
		re[y]=t;
		y=fa[y];
		fa[z]=x;
		z=y;
	}
	return tmp2;
}
int main()
{
	freopen("cube.in","r",stdin);
	freopen("cube.out","w",stdout);
	int n,p,i,x,y,ans;
	char a[10];
	scanf("%d%d",&n,&p);
	for(i=1;i<=n;i++)
		fa[i]=i,sz[i]=1;
	for(i=1;i<=p;i++)
	{
		scanf("%s",a+1);
		if(a[1]=='M')
		{
			scanf("%d%d",&x,&y);
			union_set(x,y);
			//printf("%d",re[1]);
		}
		else
		{
			scanf("%d",&x);
			ans=getit(x);
			printf("%d\n",ans);
		}
	}
	return 0;
}
