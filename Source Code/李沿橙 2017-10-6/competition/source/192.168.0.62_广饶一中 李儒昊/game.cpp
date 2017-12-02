#include<iostream>
#include<cstdio>
#include<cstring>

#define N 500007
#define mod 100000007
#define ll long long

using namespace std;
ll n,m,ans;
ll fac[N]={1,1},inv[N]={1,1},f[N]={1,1},sum[N],a[N];
struct tree
{
	ll l,r,sum,flag,opt,dis;
}tr[N<<2];

inline ll read()
{
	ll x=0,f=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}

inline void pushup(int k)
{
	tr[k].sum=((tr[k<<1].sum+mod)%mod*(tr[k<<1|1].sum+mod)%mod)%mod;
	tr[k].dis=(tr[k<<1].dis+tr[k<<1|1].dis+mod)%mod;
}

inline void pushdown(int k,int opt)
{
	if(opt)
	{
		tr[k<<1].flag=(tr[k<<1].flag+tr[k].flag)%mod;
		tr[k<<1].sum=(tr[k<<1].sum+(tr[k<<1].r-tr[k<<1].l+1)*tr[k].flag%mod)%mod;
		tr[k<<1].dis
		tr[k<<1|1].flag=(tr[k<<1|1].flag+tr[k].flag)%mod;
		tr[k<<1|1].sum=(tr[k<<1|1].sum+(tr[k<<1|1].r-tr[k<<1|1].l+1)*tr[k].flag%mod)%mod;
		tr[k].flag=0;
	}
	else
	{
		tr[k<<1].opt^=1;tr[k<<1|1].opt^=1;
		tr[k<<1].sum=(-tr[k<<1].sum+mod)%mod;
		tr[k<<1|1].sum=(-tr[k<<1|1].sum+mod)%mod;
		tr[k].opt=0;
	}
}

void build(int k,int l,int r)
{
	tr[k].l=l;tr[k].r=r;tr[k].sum=1;tr[k].opt=tr[k].flag=0;
	if(l==r)
	{
		tr[k].sum=a[l];
		return;
	}
	int mid=l+r>>1;
	build(k<<1,l,mid);build(k<<1|1,mid+1,r);
	pushup(k);
}

void change(int k,int l,int r,int c)
{
	if(l>r) return;
	if(tr[k].l==l && tr[k].r==r) 
	{
		tr[k].sum=(tr[k].sum+(tr[k].r-tr[k].l+1)*c%mod)%mod;
		tr[k].flag+=c%mod;
		return;
	}
	if(tr[k].flag) pushdown(k,1);
	if(tr[k].opt ) pushdown(k,0);
	int mid=tr[k].l+tr[k].r>>1;
	if(r<=mid) change(k<<1,l,r,c);
	else if(l>mid) change(k<<1|1,l,r,c);
	else change(k<<1,l,mid,c),change(k<<1|1,mid+1,r,c);
	pushup(k);
}

void change1(int k,int l,int r)
{
	if(l>r) return;
	if(tr[k].l==tr[k].r)
	{
		tr[k].sum=-tr[k].sum;
		tr[k].sum=(tr[k].sum+mod)%mod;
		tr[k].opt=-tr[k].opt;
		return;
	}
	if(tr[k].flag) pushdown(k,1);
	if(tr[k].opt ) pushdown(k,0);
	int mid=tr[k].l+tr[k].r>>1;
	if(r<=mid) change1(k<<1,l,r);
	else if(l>mid) change1(k<<1|1,l,r);
	else change1(k<<1,l,mid),change1(k<<1|1,mid+1,r);
	pushup(k);
}

ll query(int k,int l,int r)
{
	if(l>r) return 0;
	if(tr[k].l==l && tr[k].r==r) 
	return tr[k].sum%mod;
	if(tr[k].flag) pushdown(k,1);
	if(tr[k].opt ) pushdown(k,0);
	pushup(k);
	int mid=tr[k].l+tr[k].r>>1;
	if(r<=mid) return (query(k<<1,l,r)+mod)%mod;
	else if(l>mid) return (query(k<<1|1,l,r)+mod)%mod;
	else return (query(k<<1,l,mid)+mod)%mod*(query(k<<1|1,mid+1,r)+mod)%mod;
}

inline void init()
{
	for(int i=2;i<N;i++)
	{
		fac[i]=fac[i-1]*i%mod;
		f[i]=(mod-mod/i)*f[mod%i]%mod;
		inv[i]=inv[i-1]*f[i]%mod;
	}
}

inline ll C(ll a,ll b)
{
	return fac[a]*inv[b]*inv[a-b]%mod;
}

int main()
{
	freopen("jiayou.txt","r",stdin);
	int opt,x,y,z;
	n=read();m=read();
	for(int i=1;i<=n;i++) a[i]=read(),sum[i]=sum[i-1]+a[i];
	build(1,1,n);init();
	while(m--)
	{
		opt=read(),x=read(),y=read();
		if(x>y) swap(x,y);
		if(opt==1) z=read(),change(1,x,y,z);
		if(opt==2) change1(1,x,y);
		if(opt==3)
		{
			z=read();ll k=y-x+1;
			if(z==1) printf("%lld\n",(sum[y]-sum[x-1]+mod)%mod);
			else if(k<=z) printf("%lld\n",query(1,x,y)%mod);
			else
			{
				ll val=C(k-1,z-1);
				val%=mod;printf("%lld\n",(val*(query(1,x,y)+mod)%mod)%mod);
			}
		} 
	}
	return 0;
}
