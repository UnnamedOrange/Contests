#include<cstdio>
#include<iostream>
#define maxn 100010
#define maxm 200010
#define ll long long
#define mod 1000000007
#define max(x,y) (x)>(y)?(x):(y)
using namespace std;
int to[maxm],nxt[maxm],first[maxn];
int val[maxn],dis[maxn],ans[maxn];
int fa[maxn],sz[maxn],num[maxn];
int a[maxn],b[maxn],d[maxn];
int n,mx,sum,cnt;
void add(int x,int y)
{
	to[++cnt]=y;
	nxt[cnt]=first[x];
	first[x]=cnt;
}
int find(int x)
{
	if(fa[x]==x)
	return x;
	return fa[x]=find(fa[x]);
}
int qpow(int x,int y)
{
	int tmp=1;
	while(y)
	{
		if(y&1)
		tmp=(ll)tmp*x%mod;
		x=(ll)x*x%mod;
		y>>=1;
	}
	return tmp;
}
int inv(int x)
{
	return qpow(x,mod-2);
}
void dfs(int x,int fa)
{
	int x1=0,x2=0;
	for(int i=first[x];i;i=nxt[i])
	{
		int v=to[i];
		if(v!=fa)
		{
			dfs(v,x);
			if(dis[v]>x1)
			{
				x2=x1;
				x1=dis[v];
			}
			else if(dis[v]>x2)
			x2=dis[v];
		}
	}
	dis[x]=val[x]+x1;
	mx=max(mx,x1+x2+val[x]);
}
int main()
{
	freopen("forest.in","r",stdin);
	freopen("forest.out","w",stdout);
	int p,q,x,y;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	fa[i]=i,sz[i]=1;
	sum=1;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&val[i]);
		ans[i]=val[i];
		sum=(ll)sum*val[i]%mod;
	}
	for(int i=1;i<n;i++)
	scanf("%d %d\n",&a[i],&b[i]);
	for(int i=n-1;i;i--)
	scanf("%d",&d[i]);
	num[n]=sum;
	for(int i=1;i<n;i++)
	{
		x=a[d[i]];
		y=b[d[i]];
		add(x,y);
		add(y,x);
		p=find(x);
		q=find(y);
		if(sz[p]>sz[q])
		swap(p,q);	
		fa[p]=q;
		sz[q]+=sz[p];
		sum=(ll)sum*inv(ans[p])%mod*inv(ans[q])%mod;
		mx=0;
		dfs(q,0);
		ans[q]=mx;
		sum=(ll)sum*ans[q]%mod;
		num[n-i]=sum;
	}
	for(int i=1;i<=n;i++)
	printf("%d\n",num[i]);
	return 0;
}
		
		
		
			
	
	
