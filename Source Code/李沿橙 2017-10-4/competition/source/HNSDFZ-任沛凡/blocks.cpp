#include<cstdio>
#define ll long long
#define maxn 1000010
using namespace std;
int a[maxn];
ll s[maxn];
int n,m,k;
bool check(int x)
{
	ll sum=(ll)x*k;
	for(int i=1;i<=n-x+1;i++)
	if((ll)(s[i+x-1]-s[i-1])>=sum)
	return 1;
	return 0;
}
int main()
{
	freopen("blocks.in","r",stdin);
	freopen("blocks.out","w",stdout);
	int l,r,mid,ans;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
	s[i]=s[i-1]+a[i];
	while(m--)
	{
		scanf("%d",&k);
		l=0,r=n;
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
		printf("%d ",ans);
	}
	printf("\n");
	return 0;
}
		
