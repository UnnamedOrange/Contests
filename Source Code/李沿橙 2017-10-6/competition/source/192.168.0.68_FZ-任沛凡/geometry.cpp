#include<cstdio>
#define eps 1e-10
using namespace std;
struct data
{
	int x,b;
	double k;
}a[100010];
int x,y,n,m;
bool check(int k)
{
	if((double)(y-x*a[k].k-a[k].b)<-eps)
	return 0;
	return 1;
}
int main()
{
	freopen("geometry.in","r",stdin);
	freopen("geometry.out","w",stdout);
	int l,r,mid,ans;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	scanf("%d",&a[i].x);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i].b);
		a[i].k=(double)-a[i].b/a[i].x;
	}
	scanf("%d",&m);
	while(m--)
	{
		scanf("%d%d",&x,&y);
		if(!check(1))
		{
			puts("0");
			continue;
		}
		l=1;
		r=n;
		while(l<=r)
		{
			mid=(l+r)>>1;
			if(check(mid))
			{
				ans=mid;
				l=mid+1;
			}
			else
			r=mid-1;
		}
		printf("%d\n",ans);
	}
	return 0;
}
