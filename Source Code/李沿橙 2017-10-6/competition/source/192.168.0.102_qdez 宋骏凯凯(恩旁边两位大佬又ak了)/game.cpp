#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<string>
#include<cmath>
#include<ctime>
#include<queue>
#include<map>
#include<vector>
#define rint register int
#define debug(x) cerr<<#x<<"="<<x<<endl
#define fgx cerr<<"-------------"<<endl
typedef long long ll;
using namespace std;
const int mod=1e9+7;
int b[100000];
struct node
{	int l,r,sum,ans,tag1,tag2;
}a[200000];
void down(int o)
{	int len=a[o].r-a[o].l+1;
	if(a[o].tag2!=0) a[o].sum=(-a[o].sum+mod)%mod;
	a[o].ans=a[o].ans+(ll)a[o].tag1*(len-1)%mod*(ll)a[o].sum%mod+(ll)len*(len-1)%mod*500000004LL%mod*((ll)a[o].tag1*a[o].tag1%mod);
	if(a[o].tag1!=0) a[o].sum=(a[o].sum+(ll)len*a[o].tag1%mod)%mod;
	if(a[o].tag2!=0)
	{	if(a[o+o].tag2) a[o+o].tag2=0;
		else 
		{	a[o+o].tag2=1;
			if(a[o+o].tag1) a[o+o].tag1=(mod-a[o+o].tag1)%mod;
		}
		if(a[o+o+1].tag2) a[o+o+1].tag2=0;
		else 
		{	a[o+o+1].tag2=1;
			if(a[o+o+1].tag1) a[o+o+1].tag1=(mod-a[o+o+1].tag1)%mod;
		}
	}
	//debug(o);debug(a[o].tag1);debug(a[o].tag2);fgx;debug(a[o].sum);
	a[o+o].tag1+=a[o].tag1; a[o+o+1].tag1+=a[o].tag1; a[o].tag1=a[o].tag2=0;
}
void update(int o)
{	if(a[o+o].tag1||a[o+o].tag2) down(o+o); if(a[o+o+1].tag1||a[o+o+1].tag2) down(o+o+1);
	a[o].sum=(a[o+o].sum+a[o+o+1].sum)%mod;
	a[o].ans=((a[o+o].ans+a[o+o+1].ans)%mod+(ll)a[o+o].sum*a[o+o+1].sum%mod)%mod;
}

void build(int ll,int rr,int o)
{	a[o].l=ll; a[o].r=rr;
	if(ll==rr)
	{	a[o].sum=b[ll];a[o].ans=0;	
		return;
	}
	int mid=(ll+rr)>>1;
	build(ll,mid,o+o); build(mid+1,rr,o+o+1);
	update(o);
}
void modify(int ll,int rr,int k,int o)
{	if(a[o].tag1||a[o].tag2) down(o);
	if(a[o].l==ll&&a[o].r==rr){a[o].tag1=(a[o].tag1+(k+mod)%mod)%mod;down(o);return;}
	int mid=(a[o].l+a[o].r)>>1;
	if(rr<=mid) modify(ll,rr,k,o+o);
	else if(ll>mid) modify(ll,rr,k,o+o+1);
	else modify(ll,mid,k,o+o),modify(mid+1,rr,k,o+o+1);
	update(o);
}
void modify2(int ll,int rr,int o)
{	if(a[o].tag1||a[o].tag2) down(o);
	if(a[o].l==ll&&a[o].r==rr)
	{	if(a[o].tag2!=0) a[o].tag2=0;
		else 
		{	a[o].tag2=1;
			if(a[o].tag1) a[o].tag1=(mod-a[o].tag1)%mod;
		}
		down(o);
		return;
	}
	int mid=(a[o].l+a[o].r)>>1;
	if(rr<=mid) modify2(ll,rr,o+o);
	else if(ll>mid) modify2(ll,rr,o+o+1);
	else modify2(ll,mid,o+o),modify2(mid+1,rr,o+o+1);
	update(o);
}
int querysum(int ll,int rr,int o)
{	if(a[o].tag1||a[o].tag2) down(o);
	if(a[o].l==ll&&a[o].r==rr) return a[o].sum;
	int mid=(a[o].l+a[o].r)>>1;
	if(rr<=mid) return querysum(ll,rr,o+o);
	else if(ll>mid) return querysum(ll,rr,o+o+1);
	else return (querysum(ll,mid,o+o)+querysum(mid+1,rr,o+o+1))%mod;
}
int query(int ll,int rr,int o)
{	if(a[o].tag1||a[o].tag2) down(o);
	if(a[o].l==ll&&a[o].r==rr) return a[o].ans;
	int mid=(a[o].l+a[o].r)>>1;
	if(rr<=mid) return query(ll,rr,o+o);
	else if(ll>mid) return query(ll,rr,o+o+1);
	else return ((query(ll,mid,o+o)+query(mid+1,rr,o+o+1))%mod+(long long)(querysum(ll,mid,o+o)*querysum(mid+1,rr,o+o+1))%mod)%mod;
}
int main()
{   freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	int n,m; scanf("%d%d",&n,&m);
	for(rint i=1;i<=n;i++) scanf("%d",&b[i]);
	build(1,n,1);
	for(rint i=1;i<=m;i++)
	{	int opt,l,r,k; scanf("%d",&opt);
		if(opt==1)
		{	scanf("%d%d%d",&l,&r,&k);
			modify(l,r,k,1);
		}
		if(opt==2)
		{	scanf("%d%d",&l,&r);
			modify2(l,r,1);
		}
		if(opt==3)
		{	scanf("%d%d%d",&l,&r,&k);
			if(k>2) printf("heiheihei\n");
			else if(k==2) printf("%d\n",query(l,r,1));
			else printf("%d\n",querysum(l,r,1));
		}
	}
	return 0;
}


