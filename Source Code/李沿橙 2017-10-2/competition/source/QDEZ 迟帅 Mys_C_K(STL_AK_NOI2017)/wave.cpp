#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<climits>
#define INF INT_MAX
#define N 2000010
#define lint long long
#define inf INT_MIN
using namespace std;
struct segment{
	int v[2],l,r;
	segment *ch[2];
}*rt;
int build(segment* &rt,int l,int r)
{
	rt=new segment;
	rt->v[0]=inf,
	rt->v[1]=0;
	rt->l=l,rt->r=r;
	if(l==r) return 0;
	int mid=(l+r)>>1;
	build(rt->ch[0],l,mid);
	build(rt->ch[1],mid+1,r);
	return 0;
}
int update(segment* &rt,int pos,int v,int p)
{
	int l=rt->l,r=rt->r;
	if(l==r) return rt->v[p]=v;
	int mid=(l+r)>>1;
	if(pos<=mid) update(rt->ch[0],pos,v,p);
	else update(rt->ch[1],pos,v,p);
	return rt->v[0]=max(rt->ch[0]->v[0],rt->ch[1]->v[0]),
		   rt->v[1]=max(rt->ch[0]->v[1],rt->ch[1]->v[1]);
}
int query(segment* &rt,int s,int t,int p)
{
	int l=rt->l,r=rt->r;
	if(s<=l&&r<=t) return rt->v[p];
	int mid=(l+r)>>1,ans=inf;
	if(s<=mid) ans=max(ans,query(rt->ch[0],s,t,p));
	if(mid<t) ans=max(ans,query(rt->ch[1],s,t,p));
	return ans;
}
int a[N],u[N],d[N];lint lintu[N];
vector<lint> v;
inline int getid(lint x)
{
	return lower_bound(v.begin(),v.end(),x)-v.begin()+1;
}
int main()
{
	freopen("wave.in","r",stdin);
	freopen("wave.out","w",stdout);
	int n,k;scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		v.push_back(a[i]);
		v.push_back(lintu[i]=a[i]+k);
		v.push_back(d[i]=a[i]-k);
	}
	sort(v.begin(),v.end());
	v.erase(unique(v.begin(),v.end()),v.end());
	for(int i=1;i<=n;i++)
		a[i]=getid(a[i]),
		u[i]=getid(lintu[i]),
		d[i]=getid(d[i]);
	int m,ans=1;
	build(rt,1,m=v.size());
	for(int i=1;i<=n;i++)
	{
		int f0=query(rt,u[i],m,1)+1,
			f1=query(rt,1,d[i],0)+1;
		ans=max(ans,max(f0,f1));
		update(rt,a[i],f0,0);
		update(rt,a[i],f1,1);
	}
	printf("%d\n",ans);return 0;
}
