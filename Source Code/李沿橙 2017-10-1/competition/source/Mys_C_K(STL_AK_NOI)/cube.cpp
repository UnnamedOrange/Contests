#include<cstdio>
#include<cstring>
#include<iostream>
#define N 30010
using namespace std;
int fa[N],sz[N],pos[N];
inline int findf(int x)
{
	int fx=x,y,s=0,savs;
	while(fx^fa[fx]) s+=pos[fx],fx=fa[fx];
	while(x^fx) savs=s,s-=pos[x],pos[x]=savs,
				y=fa[x],fa[x]=fx,x=y;
	return fx;
}
inline int merge_union(int y,int x)
{
	return fa[y]=x,pos[y]=sz[x],sz[x]+=sz[y];
}
inline int solve(int x,int fx)
{
	return sz[fx]-pos[x]-1;
}
int main()
{
	freopen("cube.in","r",stdin);
	freopen("cube.out","w",stdout);
	int n=30000,q;scanf("%d",&q);
	for(int i=1;i<=n;i++)
		fa[i]=i,sz[i]=1,pos[i]=0;
	while(q--)
	{
		char opt;while((opt=getchar())!='C'&&opt!='M');
		if(opt=='M')
		{
			int x,y;scanf("%d%d",&x,&y);
			int fx=findf(x),fy=findf(y);
			if(fx^fy) merge_union(fy,fx);
		}
		else{
			int x;scanf("%d",&x);
			int fx=findf(x);
			printf("%d\n",solve(x,fx));
		}
	}
	return 0;
}
