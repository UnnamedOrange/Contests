#include<iostream>
#include<cstdio>
#include<cstring>

#define N 100007
#define mod 100000007

using namespace std;
int head[N<<1],val[N],b[N];
int siz[N],ans[N],fa[N],sum[N];
int n,m,cnt;
struct edge
{
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
	e[++cnt].v=v;e[cnt].u=u;e[cnt].net=head[u];head[u]=cnt;
}

inline int find(int x)
{
	if(x==fa[x]) return x;
	else return fa[x]=find(fa[x]);
}

int main()
{
	freopen("forest.in","r",stdin);
	freopen("forest.out","w",stdout);
	int x,y;
	n=read();ans[0]=1;
	for(int i=1;i<=n;i++) 
	  sum[i]=val[i]=read()%mod,ans[i]=ans[i-1]*val[i]%mod,fa[i]=i,siz[i]=1;
	for(int i=1;i<n;i++)
	{
	  	x=read();y=read();
	  	add(x,y);add(y,x);
	}
	for(int i=n-1;i>=1;i--) b[i]=read();ans[1]=ans[n];
	
	for(int i=2;i<=n;i++)
	{
		int u=find(e[2*b[i-1]-1].u),v=find(e[2*b[i-1]-1].v);
		fa[u]=v;
		ans[i]=(ans[i-1]%mod/(sum[u]*sum[v])%mod*(sum[u]+sum[v])%mod)%mod;
		sum[u]+=sum[v];
	}
	for(int i=1;i<=n;i++) printf("%d\n",ans[i]);
	return 0;
}
