#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
#define pl puts("lala")
#define cp cerr<<"lala"<<endl
#define ln putchar('\n')
#define pb push_back
#define fi first
#define se second
using namespace std;
inline int read()
{
    char ch=getchar();int g=1,re=0;
    while(ch<'0'||ch>'9') {if(ch=='-')g=-1;ch=getchar();}
    while(ch<='9'&&ch>='0') re=(re<<1)+(re<<3)+(ch^48),ch=getchar();
    return re*g;
}
typedef long long ll;
typedef pair<int,int> pii;

const int N=55;
const int inf=0x3f3f3f3f;
int n,m,K,val[N][N];
bool vis[N][N],ban[N][N];
int move1[4]={-1,0,1,0},move2[4]={0,1,0,-1};

int minn=inf,last[N][N];

void dfs(int x,int y,int cnt,int sum)
{
	if(x==n+1) {minn=min(minn,sum); return ;}
	int nxx=x,nxy=y+1;
	if(y==n) nxx=x+1,nxy=1;
	if(sum-last[x][y]>=minn) return ;
	
	if(!(x+y&1)) {dfs(nxx,nxy,cnt,sum); return ;}
	dfs(nxx,nxy,cnt,sum);
	if(cnt==m||vis[x][y]) return ;
	for(int g=0;g<=3;++g)
	{
		int h=(g+1)%4;
		if(!vis[x+move1[g]][y+move2[g]] && !vis[x+move1[h]][y+move2[h]])
		{
			vis[x+move1[g]][y+move2[g]]=1;
			vis[x+move1[h]][y+move2[h]]=1;
			dfs(nxx,nxy,cnt+1,sum-val[x][y]);
			vis[x+move1[g]][y+move2[g]]=0;
			vis[x+move1[h]][y+move2[h]]=0;
		}
	}
}

void wj()
{
	freopen("lethe2.in","r",stdin);
	//freopen("lethe.out","w",stdout);
}
int main()
{
	wj();
	n=read(); m=read(); K=read();
	int sum=0;
	for(int i=1;i<=n;++i) for(int j=1;j<=n;++j) val[i][j]=read(),sum+=val[i][j];
	for(int i=1;i<=K;++i)
	{
		int x=read(),y=read();
		vis[x][y]=1;
	}
	for(int i=0;i<=n+1;++i) vis[0][i]=vis[n+1][i]=1;
	for(int i=0;i<=n+1;++i) vis[i][0]=vis[i][n+1]=1;
	for(int i=n;i;--i) for(int j=n;j;--j)
	{
		int nx=i,ny=j+1;
		if(j==n) nx=i+1,ny=1;
		last[i][j]=last[nx][ny]+val[i][j];
	}
	dfs(1,1,0,sum);
	cerr<<minn<<endl;
	return 0;
}
