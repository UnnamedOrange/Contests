#include<iostream>
#include<cstring>
#include<cstdio>
#define N 300010
#define M 300010
#define debug(x) cerr<<#x<<"="<<x
#define sp <<" "
#define ln <<endl
using namespace std;
struct segment{
	int v;segment *ch[2];
}*T[N+M*2],*Tmp;
int build(segment* &rt,int l,int r)
{
	rt=new segment;rt->v=-1;
	if(l==r) return rt->v=0;
	int mid=(l+r)>>1;
	build(rt->ch[0],l,mid);
	build(rt->ch[1],mid+1,r);
	return 0;
}
int L,R,mid,ans;
int update(segment* &pre,segment* &rt,int p,int v)
{
	rt=new segment;
	rt->v=pre->v;
	if(L==R) return rt->v+=v;
	mid=(L+R)>>1;
	if(p<=mid)
	{
		R=mid,rt->ch[1]=pre->ch[1];
		update(pre->ch[0],rt->ch[0],p,v);
	}
	else{
		L=mid+1,rt->ch[0]=pre->ch[0];
		update(pre->ch[1],rt->ch[1],p,v);
	}
	return 0;
}
int query(segment* &rt,int p)
{
	if(L==R) return rt->v;
	mid=(L+R)>>1;
	if(p<=mid) R=mid,ans=query(rt->ch[0],p);
	else L=mid+1,ans=query(rt->ch[1],p);
	return ans;
}
int col[N];
struct queries{
	int opt,l,r,x;
}q[M];
int main()
{
	freopen("color.in","r",stdin);
	freopen("color.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	int MaxColor=0;
	for(int i=1;i<=n;i++)
		scanf("%d",&col[i]),
		MaxColor=max(MaxColor,col[i]);
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&q[i].opt);
		if(q[i].opt==1)
			scanf("%d%d%d",&q[i].l,&q[i].r,&q[i].x),
			MaxColor=max(MaxColor,q[i].x);
		else scanf("%d",&q[i].x);
	}
	build(T[0],1,MaxColor);
	for(int i=1;i<=n;i++)
		L=1,R=MaxColor,
		update(T[i-1],T[i],col[i],1);
	n=MaxColor;int s,t,c,x,y;
	for(int i=1;i<=m;i++)
		if(q[i].opt==1)
		{
			s=q[i].l,t=q[i].r,c=q[i].x;
			L=1,R=n,x=query(T[t],c),
			L=1,R=n,y=query(T[s-1],c);
			printf("%d\n",x-y);
		}
		else{
			x=q[i].x,y=x+1;
			L=1,R=n;update(T[x],Tmp,col[x],-1);
			L=1,R=n;update(Tmp,T[x],col[y],1);
			swap(col[x],col[y]);
		}
	return 0;
}
