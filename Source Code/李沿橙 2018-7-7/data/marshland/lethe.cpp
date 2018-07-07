#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<vector>
#include<queue>
#define P puts("lala")
#define cp cerr<<"lala"<<endl
#define fi first
#define se second
#define ln putchar('\n')
#define pb push_back
using namespace std;
inline int read()
{
    char ch=getchar();int g=1,re=0;
    while(ch<'0'||ch>'9'){if(ch=='-')g=-1; ch=getchar();}
    while(ch<='9'&&ch>='0') re=(re<<1)+(re<<3)+(ch^48),ch=getchar();
    return re*g;
}
typedef long long ll;
typedef pair<int,int> pii;

const int N=55;
const int inf=0x3f3f3f3f;
int val[N][N],n,m,k;
const int M=(N*N+N*N*5)*2;
int head[N*N*2],cnt=1;
struct node
{
	int to,next,flow,w;
}e[M];
inline void add(int x,int y,int flow,int w)
{
	e[++cnt]=(node){y,head[x],flow,w};head[x]=cnt;
	e[++cnt]=(node){x,head[y],0,-w};head[y]=cnt;
}

int dis[N*N*2],pre[N*N*2],pree[N*N*2],S,T,ans=0;
bool vis[N*N*2];
queue<int>q;
bool spfa()
{
	while(!q.empty()) q.pop();
	for(int i=1;i<=T;++i) dis[i]=inf,pre[i]=pree[i]=0,vis[i]=0;
	q.push(S); dis[S]=0;
	while(!q.empty())
	{
		int u=q.front(); q.pop();
		vis[u]=0;
		for(int i=head[u];i;i=e[i].next)
		{
			int v=e[i].to;
			if(dis[v]>dis[u]+e[i].w&&e[i].flow>0)
			{
				dis[v]=dis[u]+e[i].w;
				pre[v]=u; pree[v]=i;
				if(!vis[v]) q.push(v),vis[v]=1;
			}
		}
	}
	if(dis[T]>0) return 0;
	ans+=dis[T];
	int minn=inf,u=T;
	while(u!=S)
	{
		minn=min(minn,e[pree[u]].flow);
		u=pre[u];
	}
	u=T;
	while(u!=S)
	{
		e[pree[u]].flow-=minn;
		e[pree[u]^1].flow+=minn;
		u=pre[u];
	}
	return 1;
}

bool ban[N][N];
int move1[5]={0,1,0,-1,0},move2[5]={0,0,1,0,-1};
int id[N][N],tot=0;

void wj()
{
#ifndef ONLINE_JUDGE
    freopen("lethe.in","r",stdin);
    freopen("lethe.out","w",stdout);
#endif
}
int main()
{
	wj();
	n=read(); m=read(); k=read();
	for(int i=1;i<=n;++i) for(int j=1;j<=n;++j) val[i][j]=read(),ans+=val[i][j];
	for(int i=1;i<=k;++i)
	{
		int x=read(),y=read();
		ban[x][y]=1;
	}
	S=n*n+n*n+1; T=S+1;
	for(int i=1;i<=n;++i) for(int j=1;j<=n;++j) id[i][j]=++tot;
	for(int i=1;i<=n;++i) for(int j=1;j<=n;++j)
	{
		if(ban[i][j]) continue;
		if(i+j&1)
		{
			add(id[i][j],id[i][j]+n*n,1,-val[i][j]);
			for(k=1;k<=4;++k)
			{
				int x=i+move1[k],y=j+move2[k];
				if(x<1||y<1||x>n||y>n) continue;
				if(!(x+y&1)&&!(y&1))
					add(id[i][j]+n*n,id[x][y],1,0);
			}
		}
		else
		{
			if(j&1)
			{
				add(S,id[i][j],1,0);
				for(k=1;k<=4;++k)
				{
					int x=i+move1[k],y=j+move2[k];
					if(x<1||y<1||x>n||y>n) continue;
					add(id[i][j],id[x][y],1,0);
				}
			}
			else add(id[i][j],T,1,0);
		}
	}
	while(spfa())
	{
		m--;
		if(!m) break;
	}
	printf("%d\n",ans);
    return 0;
}
