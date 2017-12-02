#include<cstdio>
#include<iostream>
#include<cmath>
#include<cstdlib>
#include<algorithm>

using namespace std;

int n,x[100004],y[100004];
int m,xp,yp;
long long ans;

void sortx(int l,int r)
{
	if(l==r)	return;
	int mid=(l+r)/2;
	sortx(l,mid);
	sortx(mid+1,r);
	int temp[100004];
	for(int i=l;i<=r;++i)
		temp[i]=x[i];
	int i=l,k=l,j=mid+1;
	while(i<=mid)
	{
		if(temp[i]<=temp[j]||j>r)
			x[k++]=temp[i++];
		else
			x[k++]=temp[j++];
	}
	if(j<=r)
		while(j<=r)
			x[k++]=temp[j++];
	return ;
}

void sorty(int l,int r)
{
	if(l==r)	return;
	int mid=(l+r)/2;
	sorty(l,mid);
	sorty(mid+1,r);
	int temp[100004];
	for(int i=l;i<=r;++i)
		temp[i]=y[i];
	int i=l,k=l,j=mid+1;
	while(i<=mid)
	{
		if(temp[i]<=temp[j]||j>r)
			y[k++]=temp[i++];
		else
			y[k++]=temp[j++];
	}
	if(j<=r)
		while(j<=r)
			y[k++]=temp[j++];
	return ;
}

int found(int t)
{
	int s;
	double a;
	a=(double)yp/xp+(double)y[t]/x[t];
	s=ceil((double)y[t]/a);
	return s;
}

int main()
{
	freopen("geometry.in","r",stdin);
	freopen("geometry.out","w",stdout);
	
	scanf("%d",&n);
	for(int i=1;i<=n;++i)	scanf("%d",&x[i]);
	for(int i=1;i<=n;++i)	scanf("%d",&y[i]);
	sortx(1,n);sorty(1,n);
	//have been checked

	scanf("%d",&m);
	for(int i=1;i<=m;++i)
	{
		ans=0;
		scanf("%d%d",&xp,&yp);
		int length=floor(sqrt((double)xp)*sqrt((double)yp));
		
		for(int j=1;j<=n;++j)
		{
			if((int)length>=x[j]&&(int)length>=y[j])	continue;
			int a=found(j);
			if(a>xp)
			{
				ans=j-1;
				break;
			}
			if(j==n)	ans=n;
		}
		printf("%d\n",ans);
	}
	return 0;
} 
