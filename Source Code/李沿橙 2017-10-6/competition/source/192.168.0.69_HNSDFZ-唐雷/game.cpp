#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define N 50005
#define mo 1000000007
using namespace std;
typedef long long ll;
struct node
{
	ll sum,klk;
	ll lazy1,lazy2;
}d[N*4];
ll n,m;
void pd1(ll pos,ll l,ll r,ll num)
{
	d[pos].klk=(d[pos].klk+2*num%mo*d[pos].sum%mo+(r-l+1)*num%mo*num%mo)%mo;
	d[pos].sum=(d[pos].sum+(r-l+1)*num%mo)%mo;
}
void pud(ll pos,ll l,ll r)
{
	if(d[pos].lazy2)
	{
		d[pos<<1].sum*=-1;d[pos<<1].lazy2^=1;
		d[pos<<1|1].sum*=-1;d[pos<<1|1].lazy2^=1;
		d[pos].lazy2=0;
	}
	if(d[pos].lazy1)
	{
		ll mid=(l+r)>>1;
		pd1(pos<<1,l,mid,d[pos].lazy1);d[pos<<1].lazy1+=d[pos].lazy1;
		pd1(pos<<1|1,mid+1,r,d[pos].lazy1);d[pos<<1|1].lazy1+=d[pos].lazy1;
		d[pos].lazy1=0;
	}
}
void tag(ll pos,ll l,ll r,ll num,ll typ)
{
	if(typ==1)
	{
		pd1(pos,l,r,num);
		d[pos].lazy1+=num;
	}
	if(typ==2)
	{
		if(d[pos].lazy1)
		{
			ll mid=(l+r)>>1;
			pd1(pos<<1,l,mid,d[pos].lazy1);d[pos<<1].lazy1+=d[pos].lazy1;
			pd1(pos<<1|1,mid+1,r,d[pos].lazy1);d[pos<<1|1].lazy1+=d[pos].lazy1;
			d[pos].lazy1=0;
		}
		d[pos].sum*=-1;
		d[pos].lazy2^=1;
	}
}
void add(ll pos,ll l,ll r,ll le,ll ri,ll num)
{
	if(le<=l&&r<=ri){tag(pos,l,r,num,1);return;}
	pud(pos,l,r);
	ll mid=(l+r)>>1;
	if(ri<=mid)add(pos<<1,l,mid,le,ri,num);
	else if(le>mid)add(pos<<1|1,mid+1,r,le,ri,num);
	else
	{
		add(pos<<1,l,mid,le,ri,num);
		add(pos<<1|1,mid+1,r,le,ri,num);
	}
	d[pos].klk=d[pos<<1].klk+d[pos<<1|1].klk;
	d[pos].sum=d[pos<<1].sum+d[pos<<1|1].sum;
}
void rev(ll pos,ll l,ll r,ll le,ll ri)
{
	if(le<=l&&r<=ri){tag(pos,l,r,0,2);return;}
	pud(pos,l,r);
	ll mid=(l+r)>>1;
	if(ri<=mid)rev(pos<<1,l,mid,le,ri);
	else if(le>mid)rev(pos<<1|1,mid+1,r,le,ri);
	else
	{
		rev(pos<<1,l,mid,le,ri);
		rev(pos<<1|1,mid+1,r,le,ri);
	}
	d[pos].klk=d[pos<<1].klk+d[pos<<1|1].klk;
	d[pos].sum=d[pos<<1].sum+d[pos<<1|1].sum;
}
ll getsum(ll pos,ll l,ll r,ll le,ll ri)
{
	if(le<=l&&r<=ri){return d[pos].sum;}
	pud(pos,l,r);
	ll mid=(l+r)>>1;
	if(ri<=mid)return getsum(pos<<1,l,mid,le,ri);
	else if(le>mid)return getsum(pos<<1|1,mid+1,r,le,ri);
	else
	{
		return getsum(pos<<1,l,mid,le,ri)+getsum(pos<<1|1,mid+1,r,le,ri);
	}
}
ll getklk(ll pos,ll l,ll r,ll le,ll ri)
{
	if(le<=l&&r<=ri){return d[pos].klk;}
	pud(pos,l,r);
	ll mid=(l+r)>>1;
	if(ri<=mid)return getklk(pos<<1,l,mid,le,ri);
	else if(le>mid)return getklk(pos<<1|1,mid+1,r,le,ri);
	else
	{
		return getklk(pos<<1,l,mid,le,ri)+getklk(pos<<1|1,mid+1,r,le,ri);
	}
}
ll dp[50005][15],a[N];
ll p(ll x,ll y)
{
	return x+y>=mo?x+y-mo:(x+y<0?x+y+mo:x+y);
}
void work();
int main()
{
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	scanf("%lld%lld",&n,&m);
	if(n*m<=10000000)work();
	ll t1,t2,t3,typ;
	for(ll i=1;i<=n;++i){scanf("%lld",&t1);add(1,1,n,i,i,t1);}
	for(ll i=1;i<=m;++i)
	{
		scanf("%lld",&typ);
		if(typ==1)
		{
			scanf("%lld%lld%lld",&t1,&t2,&t3);
			add(1,1,n,t1,t2,t3);
		}
		if(typ==2)
		{
			scanf("%lld%lld",&t1,&t2);
			rev(1,1,n,t1,t2);
		}
		if(typ==3)
		{
			scanf("%lld%lld%lld",&t1,&t2,&t3);
			if(t3==1)
			{
				ll ans=getsum(1,1,n,t1,t2);
				printf("%lld\n",ans<0?ans+mo:ans);
			}
			else if(t3==2)
			{
				ll S=getsum(1,1,n,t1,t2),H=getklk(1,1,n,t1,t2);	
				ll ans=((S*S%mo-H)%mo)/2;
				printf("%lld\n",ans<0?ans+mo:ans);
			}
		}
	}
	return 0;
}
void work()
{
	for(int i=1;i<=n;++i){scanf("%lld",&a[i]);}
	ll t1,t2,t3,typ;
	for(int i=1;i<=m;++i)
	{
		scanf("%lld",&typ);
		if(typ==1)
		{
			scanf("%lld%lld%lld",&t1,&t2,&t3);
			for(int j=t1;j<=t2;++j)a[j]=p(a[j],t3);
		}
		if(typ==2)
		{
			scanf("%lld%lld",&t1,&t2);
			for(int j=t1;j<=t2;++j)a[j]=p(-a[j],0);
		}
		if(typ==3)
		{
			scanf("%lld%lld%lld",&t1,&t2,&t3);
			for(int j=1;j<=n;++j)
			for(int l=0;l<=10;++l)
			dp[j][l]=0;
			dp[0][0]=1;
			for(int j=1;j<=t2-t1+1;++j)
			{
				for(int k=0;k<=t3;++k)
				{
					if(k)dp[j][k]=(dp[j][k]+dp[j-1][k-1]*a[j+t1-1]%mo)%mo;
					dp[j][k]=(dp[j][k]+dp[j-1][k])%mo;
				}
			}
			printf("%lld\n",dp[t2-t1+1][t3]<0?dp[t2-t1+1][t3]+mo:dp[t2-t1+1][t3]);
		}
	}
}
