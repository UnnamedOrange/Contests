#include<cstdio>
#define inf 1e9
#define min(x,y) (x)<(y)?(x):(y)
#define max(x,y) (x)>(y)?(x):(y)
using namespace std;
int a[100],b[100],c[100];
int d[100],tmp[100];
int t,sum,ans;
bool flag;
int inc(int x,int y)
{
	if(x+y>24)
	return x+y-24;
	return x+y;
}
int main()
{
	freopen("cashier.in","r",stdin);
	freopen("cashier.out","w",stdout);
	int x;
	scanf("%d",&t);
	while(t--)
	{
		for(int i=1;i<=24;i++)
		scanf("%d",&a[i]);
		for(int i=1;i<=24;i++)
		scanf("%d",&b[i]);
		ans=inf;
		for(int i=1;i<=24;i++)
		{
			for(int j=1;j<=24;j++)
			c[j]=a[j],d[j]=b[j];
			flag=0;
			sum=0;
			for(int j=i,p=1;p<=24;p++,j=inc(j,1))
			{
				if(c[j]==0)
				continue;
				for(int k=j,q=1;q<=8;q++,k=inc(k,23))
				{
					if(d[k]==0)
					continue;
					x=min(d[k],c[j]);
					d[k]-=x;
					for(int l=k,o=1;o<=8;o++,l=inc(l,1))
					c[l]=max(0,c[l]-x);
					if(c[j]==0)
					break;
				}
				if(c[j]>0)
				{
					flag=1;
					break;
				}
			}
			if(flag)
			continue;
			for(int j=1;j<=24;j++)
			sum+=b[j]-d[j]; 
			if(sum<ans)
			ans=sum;
		}
		if(ans==inf)
		{
			puts("-1");
			continue;
		}
		printf("%d\n",ans);
	}
	return 0;
}
		
