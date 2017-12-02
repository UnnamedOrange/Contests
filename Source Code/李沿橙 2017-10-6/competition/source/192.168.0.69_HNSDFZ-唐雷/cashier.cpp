#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define N 100005
using namespace std;
int a[25],b[25];
int c[25];
int t;
int p(int x,int y)
{
	return x+y<=0?x+y+24:(x+y>24?x+y-24:x+y);
}
int main()
{
	freopen("cashier.in","r",stdin);
	freopen("cashier.out","w",stdout);
	scanf("%d",&t);
	while(t--)
	{
		int ans=0;
		for(int i=1;i<=24;++i)scanf("%d",&a[i]);
		for(int i=1;i<=24;++i)scanf("%d",&b[i]);
		for(int i=1;i<=24;++i)
		if(a[i]>0)
		{
			int s=p(i,-8);
			for(int j=i;j!=s;j=p(j,-1))
			{
				if(b[j]!=0)
				{
					int v=min(a[i],b[j]);ans+=v;
//					c[j]+=v;
					b[j]-=v;int to=p(j,8);
					for(int l=j;l!=to;l=p(l,1))a[l]-=v;
				}
				if(!a[i])break;
			}
			if(a[i]>0){ans=-1;break;}
		}
//		for(int i=1;i<=24;++i)printf("%d ",c[i]);cout<<endl;
		printf("%d\n",ans);
	}
	return 0;
}
