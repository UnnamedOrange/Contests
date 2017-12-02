#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int INF=1000000007;
struct Node
{
	int w;int m;int pf;int zf;
}tree[404040];
int a[110000];
int tmp1;
void maketree(int root,int left,int right)
{
	int mid=(left+right)/2;
	tree[root].zf=1;
	if(left==right)
	{
		tree[root].w=a[left];
		tree[root].pf=a[left]*a[left]%INF;
		return;	
	}
	maketree(root*2,left,mid);
	maketree(root*2+1,mid+1,right);
	tree[root].w=(tree[root*2].w+tree[root*2+1].w)%INF;
	tree[root].pf=(tree[root*2].w+tree[root*2+1].w)%INF;
}
void update(int root,int left,int right,int l,int r,int w,int ca)
{
	int mid=(left+right)/2,x1;
	if(l<=left&&r>=right)
	{
		if(ca==1)
		{
			tree[root].m=(tree[root].m+w*tree[root].zf)%INF;
		}
		else
			tree[root].zf=tree[root].zf*(-1);
		return;
	}
	tree[root].w=(tree[root].w+(long long)tree[root].m*(right-left+1))%INF;
	tree[2*root].m=(tree[root*2].m+tree[root].m)%INF;
	tree[2*root+1].m=(tree[root*2+1].m+tree[root].m)%INF;
	tree[root].m=0;
	tree[2*root].zf=tree[root].zf*tree[2*root].m;
	tree[2*root+1].zf=tree[root].zf*tree[2*root+1].m;
	tree[root].zf=1;
	if(mid>=l)
		update(root*2,left,mid,l,r,w,ca);
	if(mid<r)
		update(root*2+1,mid+1,right,l,r,w,ca);
	tree[root].w=(tree[2*root].w+tree[root*2+1].w)%INF;
	x1=(long long)tree[2*root].m*tree[2*root].zf*(mid-left+1)%INF;
	tree[root].w=(tree[root].w+x1)%INF;
	x1=(long long)tree[2*root+1].m*tree[2*root+1].zf*(right-mid)%INF;
	tree[root].w=(tree[root].w+x1)%INF;
	
	tree[root].pf=(tree[2*root].pf+tree[2*root+1].pf);
	x1=(long long)tree[root*2].m*tree[root*2].m%INF;
	x1=(long long)tree[root*2].m*(mid-left+1)%INF;
	tree[root].pf=(tree[root].pf+x1)%INF;
	x1=(long long)tree[root*2+1].m*tree[root*2+1].m%INF;
	x1=(long long)tree[root*2+1].m*(right-mid)%INF;
	tree[root].pf=(tree[root].pf+x1)%INF;
	
	x1=((long long)tree[2*root].w*tree[2*root].m)%INF*2%INF;
	tree[root].pf=(tree[root].pf+x1)%INF;
	x1=((long long)tree[2*root+1].w*tree[2*root+1].m)%INF*2%INF;
	tree[root].pf=(tree[root].pf+x1)%INF;
}
int query(int root,int left,int right,int l,int r,int k)
{
	int mid=(left+right)/2,ans=0;
	//printf("%d %d\n",left,right);
	if(l<=left&&r>=right)
	{
		if(k==1)
			return tree[root].zf*(tree[root].w+tree[root].m)%INF;
		else
		{
			tmp1=tree[root].pf;
			tmp1=(tmp1+(long long)tree[root].m*tree[root].m%INF*(right-left+1)%INF)%INF;
			return (long long)tree[root].zf*(tree[root].w+tree[root].m)%INF;
		}
	}
	if(mid>=l)
		ans=query(root*2,left,mid,l,r,k);
	if(mid<r)
		ans=(ans+query(root*2+1,mid+1,right,l,r,k))%INF;
	//printf("%d %d %d\n",left,right,ans);
	return ans;
}
int main()
{
	//%%%sjk
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	int n,m,i,ca,x,y,k,w,ans;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)
		scanf("%d",&a[i]);
	maketree(1,1,n);
	//printf("%d\n",tree[1].w);
	for(i=1;i<=m;i++)
	{
		scanf("%d",&ca);
		if(ca==1)
		{
			scanf("%d%d%d",&x,&y,&w);
			update(1,1,n,x,y,w,ca);
			//printf("%d\n",tree[2].w+tree[2].m*5);
		}
		if(ca==2)
		{
			scanf("%d%d",&x,&y);
			update(1,1,n,x,y,0,ca);
		}
		if(ca==3)
		{
			scanf("%d%d%d",&x,&y,&k);
			tmp1=0;
			ans=query(1,1,n,x,y,k);
			if(k==2)
			{
				ans=(long long)ans*ans%INF;//500000004
				ans=(ans-tmp1)%INF;
				ans=(long long)ans*500000004%INF;
			}
			ans=(ans+INF)%INF;
			printf("%d\n",ans);
		}
	}
	return 0;
}
