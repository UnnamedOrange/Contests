#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int xx[202020],yy[202020];
int erf(int l,int r,int x,int y)
{
	while(l<=r)
	{
		int mid=(l+r)/2;
		if(y-(double)yy[mid]*(xx[mid]-x)/xx[mid]>=-0.0000001)
			l=mid+1;
		else
			r=mid-1;
	}
	return r;
}
int main()
{
	int i,n,m,ans,x,y;
	//%%%sjk
	freopen("geometry.in","r",stdin);
	freopen("geometry.out","w",stdout);
	scanf("%d",&n);
	for(i=1;i<=n;i++)
		scanf("%d",&xx[i]);
	sort(xx+1,xx+n+1);
	for(i=1;i<=n;i++)
		scanf("%d",&yy[i]);
	sort(yy+1,yy+n+1);
	scanf("%d",&m);
	for(i=1;i<=m;i++)
	{
		scanf("%d%d",&x,&y);
		ans=erf(1,n,x,y);
		printf("%d\n",ans);
	}
	return 0;
}

