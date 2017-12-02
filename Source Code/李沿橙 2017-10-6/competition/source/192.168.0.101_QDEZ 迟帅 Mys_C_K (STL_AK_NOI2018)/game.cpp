#include<iostream>
#include<cstdio>
#include<cstring>
#define mod 1000000007
#define N 50010
#define K 11
#define lint long long
#define inv(x) fast_pow(x,mod-2)
#define push_up(rt) merge_ans(rt->c,rt->ch[0]->c,rt->ch[1]->c,K-1);
using namespace std;
int fac[N],facinv[N],ans[K],mi[K];
struct segment{
	int l,r,pt,c[K];
	bool rt;
	segment *ch[2];
}*rt;
int fast_pow(int b,int k)
{
	if(k==0) return 1;
	if(k==1) return b;
	int ans=fast_pow(b,k>>1);
	ans=(lint)ans*ans%mod;
	if(k&1) ans=(lint)ans*b%mod;
	return ans;
}
inline int C(int n,int m)
{
	if(m>n) return 0;
	return (lint)fac[n]*facinv[n-m]%mod*facinv[m]%mod;
}
inline int update_rtags(segment* &rt)
{
	for(int i=1;i<K;i+=2)
		rt->c[i]=(mod-rt->c[i])%mod;
	return rt->rt=(!rt->rt);
}
inline int push_down_rt(segment* &rt)
{
	update_rtags(rt->ch[0]);
	update_rtags(rt->ch[1]);
	return rt->rt=false;
}
inline int update_ptags(segment* &rt,int v)
{
	int n=rt->r-rt->l+1;
	rt->pt+=v;mi[0]=1;
	for(int i=1;i<K;i++)
		mi[i]=(lint)mi[i-1]*v%mod;
	for(int i=K-1;i;i--)
	{
		(rt->c[i]+=(lint)C(n,i)*mi[i]%mod)%=mod;
		for(int j=1;j<i;j++)
			(rt->c[i]+=(lint)mi[j]*C(n-i+j,j)%mod*rt->c[i-j]%mod)%=mod;
	}
	return 0;
}
inline int push_down_pt(segment* &rt)
{
	update_ptags(rt->ch[0],rt->pt);
	update_ptags(rt->ch[1],rt->pt);
	return rt->pt=0;
}
inline int merge_ans(int *ans,int *a,int *b,int k)
{
	for(int i=k;i;i--)
	{
		ans[i]=(a[i]+b[i])%mod;
		for(int j=1;j<i;j++)
			(ans[i]+=(lint)a[j]*b[i-j]%mod)%=mod;
	}
	return 0;
}
int build(segment* &rt,int l,int r)
{
	rt=new segment;
	rt->l=l,rt->r=r;
	rt->pt=0,rt->rt=false;
	rt->ch[0]=rt->ch[1]=NULL;
	memset(rt->c,0,sizeof(rt->c));
	if(l==r)
	{
		scanf("%d",&rt->c[1]);
		(rt->c[1]+=mod)%=mod;
		return 0;
	}
	int mid=(l+r)>>1;
	build(rt->ch[0],l,mid);
	build(rt->ch[1],mid+1,r);
	return push_up(rt);
}
int update(segment* &rt,int s,int t,int v)
{
	int l=rt->l,r=rt->r;
	if(s<=l&&r<=t) return update_ptags(rt,v);
	int mid=(l+r)>>1;
	if(rt->pt) push_down_pt(rt);
	if(rt->rt) push_down_rt(rt);
	if(s<=mid) update(rt->ch[0],s,t,v);
	if(mid<t) update(rt->ch[1],s,t,v);
	return push_up(rt);
}
int reverse(segment* &rt,int s,int t)
{
	int l=rt->l,r=rt->r;
	if(s<=l&&r<=t) return update_rtags(rt);
	int mid=(l+r)>>1;
	if(rt->pt) push_down_pt(rt);
	if(rt->rt) push_down_rt(rt);
	if(s<=mid) reverse(rt->ch[0],s,t);
	if(mid<t) reverse(rt->ch[1],s,t);
	return push_up(rt);
}
int query(segment* &rt,int s,int t,int k)
{
	int l=rt->l,r=rt->r;
	if(s<=l&&r<=t) return merge_ans(ans,ans,rt->c,k);
	int mid=(l+r)>>1;
	if(rt->pt) push_down_pt(rt);
	if(rt->rt) push_down_rt(rt);
	if(s<=mid) query(rt->ch[0],s,t,k);
	if(mid<t) query(rt->ch[1],s,t,k);
	return push_up(rt);
}
inline int getinv(int n)
{
	fac[0]=1;
	for(int i=1;i<=n;i++)
		fac[i]=(lint)fac[i-1]*i%mod;
	facinv[n]=inv(fac[n]);
	for(int i=n-1;i>=0;i--)
		facinv[i]=(lint)facinv[i+1]*(i+1)%mod;
	return 0;
}
int main()
{
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	int n,m;
	scanf("%d%d",&n,&m);
	build(rt,1,n);
	getinv(n);
	while(m--)
	{
		int opt;scanf("%d",&opt);
		if(opt==1)
		{
			int s,t,v;
			scanf("%d%d%d",&s,&t,&v);
			if(v<0) (v+=mod)%=mod;
			update(rt,s,t,v);
		}
		else if(opt==2){
			int s,t;scanf("%d%d",&s,&t);
			reverse(rt,s,t);
		}
		else{
			int s,t,k;
			scanf("%d%d%d",&s,&t,&k);
			memset(ans,0,sizeof(ans));
			query(rt,s,t,k);
			printf("%d\n",ans[k]);
		}
	}
	return 0;
}
