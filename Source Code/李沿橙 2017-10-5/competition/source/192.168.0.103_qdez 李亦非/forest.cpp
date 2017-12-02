#include<cstdio>
#include<iostream>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;
int a[101010],f[101010],g[101010],xx[101010],yy[101010],fa[101010];
vector <int> s[101010];
void dfs1(int x)
{
	int c,i,y;
	c=s[x].size();
	for(i=0;i<c;i++)
	{
		y=s[x][i];
		if(fa[x]==y)
			continue;
		fa[y]=x;
		dfs1(y);
	}
}
void query(int x)
{
	int c,i,y,tmp=0;
	c=s[x].size();
	g[x]=a[x];
	f[x]=a[x];
	for(i=0;i<c;i++)
	{
		y=s[x][i];
		if(fa[x]==y||fa[y]!=x)
			continue;
		query(y);
		if(g[y]+a[x]>g[x])
		{
			tmp=g[x];
			g[x]=g[y]+a[x];
		}
		else if(g[y]+a[x]>tmp)
			tmp=g[y]+a[x];
		f[x]=max(f[x],f[y]);
	}
	f[x]=max(f[x],g[x]+tmp-a[x]);
}
int main()
{
	int n,i,p,q,ans,x,j;
	freopen("forest.in","r",stdin);
	freopen("forest.out","w",stdout);
	scanf("%d",&n);
	for(i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(i=1;i<n;i++)
	{
		scanf("%d%d",&xx[i],&yy[i]);
		s[xx[i]].push_back(yy[i]);
		s[yy[i]].push_back(xx[i]);
	}
	dfs1(1);
	query(1);
	printf("%d\n",f[1]);
	for(i=1;i<n;i++)
	{
		scanf("%d",&x);
		p=xx[x];
		q=yy[x];
		if(fa[p]==q)
			swap(q,p);
		fa[q]=0;
		query(q);
		while(fa[p]!=0)
			p=fa[p];
		query(p);
		ans=1;
		for(j=1;j<=n;j++)
			if(fa[j]==0)
				ans=(long long)ans*f[j]%1000000007;
		printf("%d\n",ans);
	}
	return 0;
}
