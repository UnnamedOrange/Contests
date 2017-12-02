#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 100010
#define K 22
#define INF N
#define debug(x) cerr<<#x<<"="<<x
#define sp <<" "
#define ln <<endl
using namespace std;
vector<int> to[N];
int f[N][K],g[N][K],k;
int f1[N][K],mind[N][K];
int getdp(int x,int fa)
{
	f[x][k]=1;
	for(int i=0;i<k;i++) mind[x][i]=INF;
	for(int i=0;i<to[x].size();i++)
		if(to[x][i]^fa)
		{
			int y=to[x][i];getdp(y,x);
			for(int j=0;j<=k;j++)
			{
				g[x][j]+=min(j?g[y][j-1]:INF,f1[y][j]);
				if(j==k) break;
				int a=(j?g[y][j-1]:INF),b=f[y][j+1],c=f1[y][j],e;
				f[x][j]+=(e=min(a,min(b,c)));
				mind[x][j]=min(mind[x][j],b-e);
			}	
			f[x][k]+=min(g[y][k-1],f1[y][k]);
		}
	for(int i=0;i<=k;i++)
		g[x][i]=min(g[x][i],INF),
		f[x][i]=min(f[x][i],INF);
	for(int i=0;i<k;i++)
		f[x][i]+=mind[x][i];
	f1[x][0]=f[x][0];
	for(int i=1;i<=k;i++)
		f1[x][i]=min(f1[x][i-1],f[x][i]);
	return 0;
}
int main()
{
	freopen("general.in","r",stdin);
	freopen("general.out","w",stdout);
	int n,type;scanf("%d%d%d",&n,&k,&type);
	for(int i=1;i<n;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		to[u].push_back(v);
		to[v].push_back(u);
	}
	int rt=1;getdp(rt,0);
//	for(int i=1;i<=n;i++)
//		for(int j=0;j<=k;j++)
//			debug(i)sp,debug(j)sp,debug(g[i][j])sp,debug(f[i][j])ln;
	printf("%d\n",f1[rt][k]);
	return 0;
}
