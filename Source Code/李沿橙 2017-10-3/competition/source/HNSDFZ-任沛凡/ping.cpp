#include<cstdio>
#include<iostream>
#define maxn 100010
#define maxm 200010
#define maxk 500010
using namespace std;
int to[maxm],nxt[maxm],first[maxn];
int a[maxk],b[maxk],c[maxk];
int d[maxn],f[maxn],g[maxn];
int fa[maxn][20],num[maxn];
int bin[20];
int n,m,k,mx,id,tot,cnt;
void add(int x,int y)
{
	to[++cnt]=y;
	nxt[cnt]=first[x];
	first[x]=cnt;
}
void pre(int x)
{
	for(int i=1;bin[i]<=d[x];i++)
	fa[x][i]=fa[fa[x][i-1]][i-1];
	for(int i=first[x];i;i=nxt[i])
	{
		int v=to[i];
		if(v!=fa[x][0])
		{
			fa[v][0]=x;
			d[v]=d[x]+1;
			pre(v);
		}
	}
}
int lca(int x,int y)
{
	if(d[x]<d[y])
	swap(x,y);
	int t=d[x]-d[y];
	for(int i=0;bin[i]<=t;i++)
	if(bin[i]&t)
	x=fa[x][i];
	for(int i=15;i>=0;i--)
	if(fa[x][i]!=fa[y][i])
	x=fa[x][i],y=fa[y][i];
	if(x==y)
	return x;
	return fa[x][0];
}
void dfs(int x)
{
	g[x]=f[x];
	for(int i=first[x];i;i=nxt[i])
	{
		int v=to[i];
		if(v!=fa[x][0])
		{
			dfs(v);
			g[x]+=g[v];
		}
	}
	if(g[x]>mx)
	{
		mx=g[x];
		id=x;
	}
}
int main()
{
	freopen("ping.in","r",stdin);
	freopen("ping.out","w",stdout);
	int x,y;
	bin[0]=1;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y);
		add(y,x);
	}
	pre(1);
	scanf("%d",&k);
	for(int i=1;i<=k;i++)
	{
		scanf("%d%d",&a[i],&b[i]);
		c[i]=lca(a[i],b[i]);
		f[a[i]]++;
		f[b[i]]++;
		f[c[i]]--;
		f[fa[c[i]][0]]--;
	}
	while(k)
	{
		mx=0;
		dfs(1);
		num[++tot]=id;
		for(int i=1;i<=k;i++)
		{
			if((lca(a[i],id)==c[i]&&lca(b[i],id)==id)||(lca(b[i],id)==c[i]&&lca(a[i],id)==id))
			{
				f[a[i]]--;
				f[b[i]]--;
				f[c[i]]++;
				f[fa[c[i]][0]]++;
				a[i]=a[k];
				b[i]=b[k];
				c[i]=c[k];
				k--;
				i--;
			}
		}
	}
	printf("%d\n",tot);
	for(int i=1;i<=tot;i++)
	printf("%d\n",num[i]);
	return 0;
}	
			
		
