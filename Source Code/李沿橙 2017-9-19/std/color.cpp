#include<iostream>
#include<stdio.h>
using namespace std;

const int N=100010;
const int M=100010;
const int C=100010;
struct node
{
	int v,next;
}g[N*2];
int hd[N],tot=1;
struct Query
{
	int k,next;
}q[M];
int ind[N],itot=1;

int n,m,c[N],ans[M];
int fa[N],num[N];
int color[C],sum[N];

void ine(int u,int v)
{
	g[tot].v=v;g[tot].next=hd[u];hd[u]=tot++;
	g[tot].v=u;g[tot].next=hd[v];hd[v]=tot++;
}

void ine2(int u,int k)
{
	q[itot].k=k;q[itot].next=ind[u];ind[u]=itot++;
}

void dfs(int r)
{
	num[r]=1;
	for (int i=hd[r];i>=1;i=g[i].next)
		if (g[i].v!=fa[r])
		{
			fa[g[i].v]=r;
			dfs(g[i].v);
			num[r]+=num[g[i].v];
		} 
}

void add_del(int r,int ch)
{
	if (ch)
		sum[color[c[r]]--]--;
	else sum[++color[c[r]]]++;
	for (int i=hd[r];i>=1;i=g[i].next)
		if (g[i].v!=fa[r])
			add_del(g[i].v,ch);
}

void work(int r)
{
	int i,last=0,now=0;
	for (i=hd[r];i>=1;i=g[i].next)
		if (g[i].v!=fa[r]&&num[g[i].v]>now)
		{now=num[g[i].v];last=g[i].v;}
	for (i=hd[r];i>=1;i=g[i].next)
		if (g[i].v!=fa[r]&&g[i].v!=last)
		{
			work(g[i].v);
			add_del(g[i].v,1);
		}
	if (last!=0)work(last);
	for (i=hd[r];i>=1;i=g[i].next)
		if (g[i].v!=fa[r]&&g[i].v!=last)
			add_del(g[i].v,0);
	sum[++color[c[r]]]++;
	for (i=ind[r];i>=1;i=q[i].next)
		ans[i]=sum[q[i].k];
}

int main()
{
	freopen("color.in","r",stdin);
	freopen("color.out","w",stdout);
	int i,x,y;
	cin>>n>>m;
	for (i=1;i<=n;i++)
		scanf("%d",c+i);
	for (i=1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		ine(x,y);
	}
	for (i=1;i<=m;i++)
	{
		scanf("%d%d",&x,&y);
		ine2(x,y);
	}
	dfs(1);
	work(1);
	for (i=1;i<=m;i++)
		printf("%d\n",ans[i]);
	return 0;
}
