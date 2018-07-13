#include <bits/stdc++.h>
#define ysf (998244353)
#define inf (1LL<<60)
#define M (1000005)
#define N (100005)
#define ll long long

using namespace std;

int head[M],top[N],son[N],fa[N],sz[N],dep[N],dfn[N],pos[N],ed[N];
int flg[M],tid[M],val[N],cov[N],id[N],st[M],ans,cnt,num,n,m,k,T;

set<int> S[N];
set<int>::iterator it;
map<int,int> mp[N];

struct edge{ int nt,to; }g[M];

struct heap{
    
    priority_queue<ll> A,B;
    
    inline void push(ll v){ A.push(v); }
    
    inline void del(ll v){ B.push(v); }
    
    inline void pop(){
	while (!A.empty() && !B.empty() && A.top()==B.top()) A.pop(),B.pop();
	if (!A.empty()) A.pop();
    }
    
    inline ll top(){
	while (!A.empty() && !B.empty() && A.top()==B.top()) A.pop(),B.pop();
	return A.empty() ? -inf : A.top();
    }

    inline ll second(){
	while (!A.empty() && !B.empty() && A.top()==B.top()) A.pop(),B.pop();
	if (A.size()<2) return -inf; ll tmp=A.top(),res; A.pop();
	while (!A.empty() && !B.empty() && A.top()==B.top()) A.pop(),B.pop();
	res=A.empty() ? -inf : A.top(),A.push(tmp); return res;
    }
    
}Q1[M],A1[M],A2[M];

struct tree{
    
    ll ans1[M],ans2[M],sum[N],s1[M],s2[M],l1[M],l2[M],r1[M],r2[M];
    int ch[M][2],fa[M],dis[M];
    
    inline int isroot(int x){
	return ch[fa[x]][0]!=x && ch[fa[x]][1]!=x;
    }
    
    inline void pushup(int x){
	int &ls=ch[x][0],&rs=ch[x][1]; ll w1=max(Q1[x].top(),0LL);
	ll v1=flg[x]?val[tid[x]]:0,v2=flg[x]?val[tid[x]]:-inf;
	ans1[x]=max(A1[x].top(),max(ans1[ls],ans1[rs]));
	ans1[x]=max(ans1[x],v1+Q1[x].top()+Q1[x].second());
	ans1[x]=max(ans1[x],v1+l1[rs]+r1[ls]),s1[x]=v1+s1[ls]+s1[rs];
	ans2[x]=max(A2[x].top(),max(ans2[ls],ans2[rs]));
	ans2[x]=max(ans2[x],sum[x]+max(l2[rs],0LL)+max(r2[ls],0LL)+v2);
	l2[x]=max(l2[ls],s2[ls]+v2+sum[x]+max(l2[rs],0LL));
	r2[x]=max(r2[rs],s2[rs]+v2+sum[x]+max(r2[ls],0LL));
	s2[x]=max(-inf,v2+s2[ls]+s2[rs]+sum[x]);
	if (flg[x]){
	    ans1[x]=max(ans1[x],v1+max(w1,max(l1[rs],r1[ls])));
	    ans1[x]=max(ans1[x],v1+w1+max(l1[rs],r1[ls]));
	    l1[x]=max(l1[ls],s1[ls]+v1+max(w1,l1[rs]));
	    r1[x]=max(r1[rs],s1[rs]+v1+max(w1,r1[ls]));
	} else{
	    ans1[x]=max(ans1[x],v1+max(Q1[x].top(),max(l1[rs],r1[ls])));
	    ans1[x]=max(ans1[x],v1+Q1[x].top()+max(l1[rs],r1[ls]));
	    l1[x]=max(l1[ls],s1[ls]+v1+max(Q1[x].top(),l1[rs]));
	    r1[x]=max(r1[rs],s1[rs]+v1+max(Q1[x].top(),r1[ls]));
	}
	dis[x]=max(dep[tid[x]],max(dis[ls],dis[rs]));
    }
    
    inline void add(int x,int y){
	Q1[x].push(l1[y]),sum[x]+=max(l2[y],0LL);
	A1[x].push(ans1[y]),A2[x].push(ans2[y]);
    }
    
    inline void del(int x,int y){
	Q1[x].del(l1[y]),sum[x]-=max(l2[y],0LL);
	A1[x].del(ans1[y]),A2[x].del(ans2[y]);
    }
    
    inline void rotate(int x){
	int y=fa[x],z=fa[y],k=ch[y][0]==x;
	if (!isroot(y)) ch[z][ch[z][1]==y]=x;
	fa[x]=z,ch[y][k^1]=ch[x][k],fa[ch[x][k]]=y;
	ch[x][k]=y,fa[y]=x,pushup(y),pushup(x);
    }
    
    inline void splay(int x){
	while (!isroot(x)){
	    int y=fa[x],z=fa[y];
	    if (!isroot(y)) rotate((ch[z][0]==y)^(ch[y][0]==x)?x:y);
	    rotate(x);
	}
    }
    
    inline void access(int x){
	int t=0;
	while (x){
	    splay(x); if (t) del(x,t);
	    if (ch[x][1]) add(x,ch[x][1]);
	    ch[x][1]=t,pushup(t=x),x=fa[x];
	}
    }
    
    inline void link(int x,int y){
	if (!y) return; access(x),splay(x);
	access(y),splay(y),add(fa[x]=y,x),pushup(y);
    }
    
    inline void cut(int x){
	access(x),splay(x),fa[ch[x][0]]=0,ch[x][0]=0,pushup(x);
    }
    
    inline int findmin(int x,int d){
	access(x),splay(x);
	if (dis[ch[x][0]]<=d) return x; x=ch[x][0];
	while (1){
	    if (dis[ch[x][0]]>d) x=ch[x][0];
	    else if (dep[tid[x]]>d) return x;
	    else x=ch[x][1];
	}
	return 0;
    }
    
    inline int findpa(int x){
	access(x),splay(x),x=ch[x][0];
	while (ch[x][1]) x=ch[x][1]; return x;
    }
    
}lct;

inline int gi(){
    int x=0,q=1; char ch=getchar();
    while (ch<'0' || ch>'9') q=ch=='-'?-1:1,ch=getchar();
    while (ch>='0' && ch<='9') x=x*10+ch-'0',ch=getchar();
    return q*x;
}

inline void insert(int from,int to){
    g[++num]=(edge){head[from],to},head[from]=num;
}

inline void dfs(int x){
    for (int i=head[x],v;i;i=g[i].nt)
	dfs(v=g[i].to),lct.add(lct.fa[v]=x,v);
    lct.pushup(x);
}

inline void dfs1(int x,int p){
    fa[x]=p,sz[x]=1,dep[x]=dep[p]+1;
    for (int i=head[x],v;i;i=g[i].nt){
	v=g[i].to; if (v==p) continue;
	dfs1(v,x),sz[x]+=sz[v];
	if (sz[son[x]]<=sz[v]) son[x]=v;
    }
}

inline void dfs2(int x,int p,int anc){
    top[x]=anc,dfn[x]=++cnt,pos[cnt]=x;
    if (son[x]) dfs2(son[x],x,anc);
    for (int i=head[x],v;i;i=g[i].nt)
	if ((v=g[i].to)!=p && v!=son[x]) dfs2(v,x,v);
    ed[x]=cnt,S[cov[x]].insert(dfn[x]);
}

inline int lca(int u,int v){
    while (top[u]!=top[v]){
	if (dep[top[u]]<dep[top[v]]) swap(u,v);
	u=fa[top[u]];
    }
    return dep[u]<dep[v] ? u : v;
}

inline void add(int o,int x,int fg){
    if (mp[o].count(x)){
	int u=mp[o][x];
	lct.access(u),lct.splay(u);
	flg[u]=fg,lct.pushup(u); return;
    }
    int u,v,G,P,pa,idv; mp[o][x]=u=++cnt,flg[u]=fg;
    tid[u]=x,it=S[o].insert(dfn[x]).first;
    if (it!=S[o].begin()){
	v=pos[*--it];
	if (ed[v]>=dfn[x]) lct.link(u,mp[o][v]);
	else if (mp[o].count(G=lca(x,v))) lct.link(u,mp[o][G]); else{
	    S[o].insert(dfn[G]),mp[o][G]=++cnt,tid[cnt]=G;
	    P=lct.findmin(mp[o][v],dep[G]),pa=lct.findpa(P);
	    lct.cut(P),lct.link(P,cnt),lct.link(u,cnt),lct.link(cnt,pa);
	}
    }
    it=S[o].find(dfn[x]);
    if (++it!=S[o].end()){
	v=pos[*it],lct.cut(idv=mp[o][v]);
	if (ed[x]>=dfn[v]) lct.link(idv,u);
	else if (mp[o].count(G=lca(x,v))) lct.link(idv,mp[o][G]); else{
	    S[o].insert(dfn[G]),mp[o][G]=++cnt,tid[cnt]=G;
	    P=lct.findmin(u,dep[G]),pa=lct.findpa(P);
	    lct.cut(P),lct.link(P,cnt),lct.link(idv,cnt),lct.link(cnt,pa);
	}
    }
    lct.pushup(u);
}

inline void del(int x){
    lct.access(x),lct.splay(x),flg[x]=0,lct.pushup(x);
}

inline int cmp(const int &a,const int &b){ return dfn[a]<dfn[b]; }

int main(){
#ifndef ONLINE_JUDGE
    freopen("f.in","r",stdin);
    freopen("f.out","w",stdout);
#endif
    n=gi(),m=gi(),k=gi(),T=gi(),gi();
    for (int i=1;i<=n;++i) val[i]=gi(),cov[i]=gi();
    for (int i=1,u,v;i<n;++i) u=gi(),v=gi(),insert(u,v),insert(v,u);
    lct.ans1[0]=lct.ans2[0]=lct.l1[0]=lct.l2[0]=lct.r1[0]=lct.r2[0]=-inf;
    dfs1(1,0),dfs2(1,0,1),memset(head,0,sizeof(head)),num=cnt=0;
    for (int o=1,tot;tot=0,o<=k;++o){
	for (it=S[o].begin();it!=S[o].end();st[++tot]=pos[*it++])
	    if (fa[pos[*it]]) st[++tot]=fa[pos[*it]];
	sort(st+1,st+tot+1,cmp),tot=unique(st+1,st+tot+1)-st-1;
	for (int i=2,lim=tot;i<=lim;++i)
	    if (ed[st[i-1]]<dfn[st[i]]) st[++tot]=lca(st[i-1],st[i]);
	sort(st+1,st+tot+1,cmp),tot=unique(st+1,st+tot+1)-st-1;
	for (int i=1;i<=tot;++i){
	    S[o].insert(dfn[st[i]]),mp[o][st[i]]=id[st[i]]=++cnt;
	    flg[cnt]=cov[st[i]]==o,tid[cnt]=st[i];
	}
	for (int i=2,lim=1;i<=tot;++i){
	    while (ed[st[lim]]<dfn[st[i]]) --lim;
	    insert(id[st[lim]],id[st[i]]),st[++lim]=st[i];
	}
	if (tot) dfs(id[st[1]]); num=0;
	for (it=S[o].begin();it!=S[o].end();++it) head[mp[o][pos[*it]]]=0;
    }
    while (m--){
	int op=gi();
	if (op==1){
	    int x=gi()^ans,v=gi()^ans,u=mp[cov[x]][x];
	    lct.access(u),lct.splay(u),val[x]=v,lct.pushup(u);
	} else if (op==2){
	    int x=gi()^ans,v=gi()^ans;
	    del(mp[cov[x]][x]),add(cov[x]=v,x,1);
	    if (fa[x] && cov[fa[x]]!=v) add(v,fa[x],0);
	} else if (op==3){
	    int o=gi()^ans,x=mp[o][pos[*S[o].begin()]];
	    lct.splay(x),printf("%lld\n",lct.ans1[x]);
	    if (T) ans=lct.ans1[x]%ysf,ans<0?ans+=ysf:0;
	} else{
	    int o=gi()^ans,x=mp[o][pos[*S[o].begin()]];
	    lct.splay(x),printf("%lld\n",lct.ans2[x]);
	    if (T) ans=lct.ans2[x]%ysf,ans<0?ans+=ysf:0;
	}
    }
    return 0;
}
