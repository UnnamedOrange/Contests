#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;
struct node
{
	int sum;
	int son[2];
}d[17200005];
int n,m,siz;
int a[300005];
void add(int pos,int l,int r,int end,int num)
{
	if(l==r){d[pos].sum+=num;return;}
	d[pos].sum+=num;
	int mid=(l+r)>>1;
	bool f=end>mid;
	if(!d[pos].son[f])
		siz++,d[pos].son[f]=siz;
	if(!f)
	add(d[pos].son[f],l,mid,end,num);
	else
	add(d[pos].son[f],mid+1,r,end,num);
}
int get(int pos,int l,int r,int le,int ri)
{
	if(le<=l&&r<=ri){return d[pos].sum;}
	int mid=(l+r)>>1;
	if(ri<=mid)
	{
		if(!d[pos].son[0])return 0;
		return get(d[pos].son[0],l,mid,le,ri);
	}
	else if(le>mid)
	{
		if(!d[pos].son[1])return 0;
		return get(d[pos].son[1],mid+1,r,le,ri);
	}
	else
	{
		int l1=0,l2=0;
		if(d[pos].son[0])l1=get(d[pos].son[0],l,mid,le,ri);
		if(d[pos].son[1])l2=get(d[pos].son[1],mid+1,r,le,ri);
		return l1+l2;
	}
}
int main()
{
	freopen("color.in","r",stdin);
	freopen("color.out","w",stdout);
	siz=300000;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
	{
		scanf("%d",&a[i]);
		add(a[i],1,n,i,1);
	}
	int typ,l,r,col;
	int ans=0;
	for(int i=1;i<=m;++i)
	{
		scanf("%d",&typ);
		if(typ==1)
		{
			scanf("%d%d%d",&l,&r,&col);
			printf("%d\n",get(col,1,n,l,r));
		}
		if(typ==2)
		{
			scanf("%d",&l);
			add(a[l],1,n,l,-1);
			add(a[l],1,n,l+1,1);
			add(a[l+1],1,n,l+1,-1);
			add(a[l+1],1,n,l,1);
			swap(a[l],a[l+1]);
		}
	}
	return 0;
}
