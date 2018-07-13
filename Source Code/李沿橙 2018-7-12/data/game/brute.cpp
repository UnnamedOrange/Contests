#include <bits/stdc++.h>
#define ll long long
#define inf (1LL<<60)
#define N (205)

int ch[N][2],sz[N],a[N],b[N],c[N],n;
ll f[N][N][45][45];

using namespace std;

inline int gi(){
    int x=0,q=1; char ch=getchar();
    while (ch<'0' || ch>'9') q=ch=='-'?-1:1,ch=getchar();
    while (ch>='0' && ch<='9') x=x*10+ch-'0',ch=getchar();
    return q*x;
}

inline void dfs(int x,int A,int B){
    if (x<0){ x=-x,a[x]+=A,b[x]+=B; return; }
    dfs(ch[x][0],A+1,B),dfs(ch[x][1],A,B+1);
    if (ch[x][0]<0) ++sz[x];
    else sz[x]+=sz[ch[x][0]];
    if (ch[x][1]<0) ++sz[x];
    else sz[x]+=sz[ch[x][1]];
    ++sz[x];
}

inline ll dp(int x,int y,int A,int B){
    if (x<0){
	if (y) return inf; x=-x;
	return 1LL*c[x]*(a[x]-A)*(b[x]-B);
    }
    if (sz[x]<=y) return inf;
    if (f[x][y][A][B]!=-1) return f[x][y][A][B];
    ll res=inf;
    for (int i=0;i<=y;++i){
	res=min(res,dp(ch[x][0],i,A,B)+dp(ch[x][1],y-i,A,B));
	if (i) res=min(res,dp(ch[x][0],i-1,A+1,B)+dp(ch[x][1],y-i,A,B));
	if (i<y) res=min(res,dp(ch[x][0],i,A,B)+dp(ch[x][1],y-i-1,A,B+1));
	if (i && i<y) res=min(res,dp(ch[x][0],i-1,A+1,B)+dp(ch[x][1],y-i-1,A,B+1));
    }
    return f[x][y][A][B]=res;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("y.in","r",stdin);
    freopen("brute.out","w",stdout);
#endif
    memset(f,-1,sizeof(f));
    n=gi(); for (int i=1;i<n;++i) ch[i][0]=gi(),ch[i][1]=gi();
    for (int i=1;i<=n;++i) a[i]=gi(),b[i]=gi(),c[i]=gi();
    dfs(1,0,0),cout<<dp(1,n-1,0,0); return 0;
}
