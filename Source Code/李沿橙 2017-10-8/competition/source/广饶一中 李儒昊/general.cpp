#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>

#define N 1001

using namespace std;
int n,m,k,ans,cnt,pre,pos;
int vis[N],son[N],head[N],deep[N],fa[N];
struct edge{
	int u,v,net;
}e[N<<1];

inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f; 
}

inline void add(int u,int v)
{
	e[++cnt].v=v;e[cnt].net=head[u];head[u]=cnt;
}

void dfs(int u,int f,int c)
{
	fa[u]=f;deep[u]=c;son[u]=1;
	for(int i=head[u];i;i=e[i].net)
	{
		int v=e[i].v;
		if(v==fa[u])continue;
		dfs(v,u,c+1);son[u]+=son[v];
	}return;
}

void dfs1(int u)
{
	for(int i=head[u];i;i=e[i].net)
	{
		int v=e[i].v;
		if(v!=fa[u]) dfs1(v);
		if(son[v]==1) pos=v;
		if(deep[pos]-deep[u]>k && !vis[u]) vis[u]=1,ans++,pos=u;
		
	}
}

int main()
{
	freopen("general.in","r",stdin);
	freopen("general.out","w",stdout);
	int x,y,t;
	n=read();k=read();t=read();
	if(k==0)
	{
		printf("%d\n",n);
		return 0;
	}
	for(int i=1;i<n;i++)
	{
		x=read();y=read();
		add(x,y);add(y,x);
	}
	dfs(1,0,0);ans=1;
	if(k==1 && t!=2)
	{
		ans=0;
		for(int i=1;i<=n;i++)
		{
			if(deep[i]%2==0) ans++;
		}
		int tmp=ans;ans=0;
		for(int i=1;i<=n;i++)
		{
			if(deep[i]%2==1) ans++;
		} ans=min(ans,tmp);
	}
	if(t==2)
	{
		if(k==1)
		{
			for(int i=1;i<=n;i++)
		  	  if(deep[i]==1) ans++;
		}
		if(k==2)
		{
			ans=1;
		}
	}
	else dfs1(1);
	printf("%d\n",ans);
	fclose(stdin);fclose(stdout);
	return 0;
}
