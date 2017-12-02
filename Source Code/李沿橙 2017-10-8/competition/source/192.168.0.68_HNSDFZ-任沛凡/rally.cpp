#include<cstdio>
#define ll long long
using namespace std;
int n,m,k;
ll sum,ans;
ll a[410][410];
int main()
{
	freopen("rally.in","r",stdin);
	freopen("rally.out","w",stdout);
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	{
		scanf("%lld",&a[i][j]);
		a[i][j]+=a[i-1][j];
		a[i][j]+=a[i][j-1];
		a[i][j]-=a[i-1][j-1];
	}
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	for(int l=1;l<=i;l++)
	for(int r=1;r<=j;r++)
	{
		sum=a[i][j]-a[i][r-1]-a[l-1][j]+a[l-1][r-1];
		if(sum%k==0)
		ans++;
	}
	printf("%lld\n",ans);
	return 0;
}
		
		
