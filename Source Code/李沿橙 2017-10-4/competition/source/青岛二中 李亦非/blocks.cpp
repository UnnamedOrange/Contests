#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int sum[1010101],q[1010101];
int erf(int l,int r,int j,int k)
{
	int mid,p=r;
	while(l<=r)
	{	
		mid=(l+r)/2;
		//printf("%d %d %d %d %d %d %d_",j,q[mid],sum[j],sum[q[mid]],k,l,r);
		if(sum[j]-sum[q[mid]]<k*(j-q[mid]))
			l=mid+1;
		else
			r=mid-1;
		//printf("%d %d\n",l,r);
	}
	if(l<=p)
	return j-q[l];
	else
	return 0;
}
int main()
{
	freopen("blocks.in","r",stdin);
	freopen("blocks.out","w",stdout);
	int n,m,i,k,j,h,x,ans=0;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)
	{
		scanf("%d",&x);
		sum[i]=sum[i-1]+x;
	}
	for(i=1;i<=m;i++)
	{
		scanf("%d",&k);
		h=0;
		ans=0;
		memset(q,0,sizeof(q));
		for(j=1;j<=n;j++)
		{
			//printf("%d %d ",h,q[h]);
			ans=max(erf(0,h,j,k),ans);
			if(sum[q[h]]-q[h]*k>sum[j]-j*k)
				q[++h]=j;
			//printf("%d ",h);
			//printf("%d\n",ans);
		}
		//for(j=1;j<=h;j++)
		//	printf("%d ",q[j]);
		//printf("\n");
		printf("%d ",ans);
	}
	return 0;
}
