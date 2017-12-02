#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<ctime>
#include<map>
#include<queue>
#include<vector>
#define rint register int
#define debug(x) cerr<<#x<<"="<<x<<endl
#define fgx cerr<<"-------------"<<endl
typedef long long ll;
using namespace std;
struct lsh
{	int x,id;
}c[2000001];
int d[2000001],e[2000001],f[2000001],g[2000001],h[2000001];
struct node
{	int l,r,maxn;
}a[6000001],b[6000001];
inline int max(int x,int y){return x>y?x:y;}
inline void build(int ll,int rr,int o)
{	a[o].l=ll; a[o].r=rr;
	if(ll==rr){a[o].maxn=0;return;}
	int mid=(ll+rr)>>1;
	build(ll,mid,o+o);
	build(mid+1,rr,o+o+1);
}
inline void build1(int ll,int rr,int o)
{	b[o].l=ll; b[o].r=rr;
	if(ll==rr){b[o].maxn=0;return;}
	int mid=(ll+rr)>>1;
	build1(ll,mid,o+o);
	build1(mid+1,rr,o+o+1);
}
inline void update(int o){a[o].maxn=max(a[o+o].maxn,a[o+o+1].maxn);}
inline void update1(int o){b[o].maxn=max(b[o+o].maxn,b[o+o+1].maxn);}
inline void modify(int k,int o)
{	a[o].maxn=max(a[o].maxn,k);
	while(o>>=1) update(o);
}
inline void modify1(int k,int o)
{	b[o].maxn=max(b[o].maxn,k);
	while(o>>=1) update1(o);
}
inline int query(int ll,int rr)
{	int ans=0;ll--;rr++;
	for(;ll^rr^1;ll>>=1,rr>>=1)
	{	if(!(ll&1)) ans=max(ans,a[ll^1].maxn);	
		if(rr&1) ans=max(ans,a[rr^1].maxn);
	}
	return ans;
}
inline int query1(int ll,int rr)
{	int ans=0; ll--;rr++;
	for(;ll^rr^1;ll>>=1,rr>>=1)
	{	if(!(ll&1)) ans=max(ans,b[ll^1].maxn);
		if(rr&1) ans=max(ans,b[rr^1].maxn);
	}
	return ans;
}
inline bool cmp(lsh xx,lsh yy){return xx.x<yy.x;}
inline int read()
{	char c=getchar(); int x=0;
	for(;c>'9'||c<'0';c=getchar());
	for(;c<='9'&&c>='0';c=getchar()) x=(x<<3)+(x<<1)+(c-'0');
	return x;
}
inline int bound(int k,int n)
{	int l=1,r=n,ans;
	while(l<=r)
	{	int mid=(l+r)>>1;
		if(h[mid]<=k) ans=mid,l=mid+1;
		else r=mid-1;
	}
	return ans;
}
inline int lbound(int k,int n)
{	int l=1,r=n,ans;
	while(l<=r)
	{	int mid=(l+r)>>1;
		if(h[mid]>=k) ans=mid,r=mid-1;
		else l=mid+1;
	}
	return ans;
}
int main()
{	freopen("wave.in","r",stdin);
	freopen("wave.out","w",stdout);
	int n,k;
	n=read(),k=read();
	for(rint i=1;i<=n;i++) c[i].x=read(),c[i].id=i,e[i]=c[i].x;
	sort(c+1,c+n+1,cmp);
	d[c[1].id]=1; int tot=1;
	for(rint i=1;i<=n;i++) h[i]=c[i].x;
	for(rint i=2;i<=n;i++) if(c[i].x!=c[i-1].x) d[c[i].id]=++tot;else d[c[i].id]=tot;
	build(1,262144,1);build1(1,262144,1);
	f[1]=1; modify(1,262144+d[1]-1);
	for(rint i=2;i<=n;i++)
	{	f[i]=1;
		if(e[i]+k<=c[n].x)
		{	int kk=lbound(e[i]+k,n);
			kk=d[c[kk].id];
			f[i]=query1(262144+kk-1,524287)+1;
			modify(f[i],262144+d[i]-1);
		}
		if(e[i]-k>=c[1].x)
		{	int kk=bound(e[i]-k,n);
			kk=d[c[kk].id]; int now=max(a[262144].maxn,query(262144,262144+kk-1));
			if(now) g[i]=now+1,modify1(g[i],262144+d[i]-1);
		}
	}
	int ans=0;
	for(rint i=1;i<=n;i++) ans=max(ans,f[i]),ans=max(ans,g[i]);
	printf("%d\n",ans);
	return 0;
}

