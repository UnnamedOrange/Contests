#include <bits/stdc++.h>
#define ysf (998244353)
#define inf (1LL<<60)
#define N (1000005)
#define ll long long

using namespace std;

struct edge{ int nt,to; }g[N];

int head[N],val[N],cov[N],num,n,m,k,T;
ll f[N],ans;

inline int gi(){
    int x=0,q=1; char ch=getchar();
    while (ch<'0' || ch>'9') q=ch=='-'?-1:1,ch=getchar();
    while (ch>='0' && ch<='9') x=x*10+ch-'0',ch=getchar();
    return q*x;
}

inline void insert(int from,int to){
    g[++num]=(edge){head[from],to},head[from]=num;
}

inline void dfs1(int x,int p,int o){
    ll w=cov[x]==o?val[x]:0;
    f[x]=cov[x]==o?val[x]:-inf,ans=max(ans,f[x]);
    for (int i=head[x],v;i;i=g[i].nt){
	v=g[i].to; if (v==p) continue;
	dfs1(v,x,o),ans=max(ans,f[x]+f[v]);
	f[x]=max(f[x],f[v]+w);
    }
}

inline void dfs2(int x,int p,int o){
    f[x]=cov[x]==o?val[x]:-inf;
    for (int i=head[x],v;i;i=g[i].nt){
	v=g[i].to; if (v==p) continue;
	dfs2(v,x,o),f[x]+=max(f[v],0LL);
    }
    ans=max(ans,f[x]);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("f.in","r",stdin);
    freopen("brute.out","w",stdout);
#endif
    n=gi(),m=gi(),k=gi(),T=gi(),gi();
    for (int i=1;i<=n;++i) val[i]=gi(),cov[i]=gi();
    for (int i=1,u,v;i<n;++i) u=gi(),v=gi(),insert(u,v),insert(v,u);
    while (m--){
	int op=gi();
	if (op==1){
	    int x=gi()^ans,v=gi()^ans; val[x]=v;
	} else if (op==2){
	    int x=gi()^ans,v=gi()^ans; cov[x]=v;
	} else if (op==3){
	    int o=gi()^ans; ans=-inf,dfs1(1,0,o);
	    printf("%lld\n",ans);
	    if (T) ans%=ysf,ans<0?ans+=ysf:0; else ans=0;
	} else{
	    int o=gi()^ans; ans=-inf,dfs2(1,0,o);
	    printf("%lld\n",ans);
	    if (T) ans%=ysf,ans<0?ans+=ysf:0; else ans=0;
	}
    }
    return 0;
}
