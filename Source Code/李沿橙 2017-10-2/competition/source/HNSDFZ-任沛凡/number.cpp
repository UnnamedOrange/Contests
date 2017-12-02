#include<cstdio>
#define maxn 2000
using namespace std;
int n,v[maxn];
long long ans;
int main()
{
	freopen("number.in","r",stdin);
	freopen("number.out","w",stdout);
	int a,b,x;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		a=i;
		x=0;
		while(a)
		{
			b=a%10;
			x|=1<<b;
			a=a/10;
		}
		ans+=v[x];
		v[x]++;
	}
	printf("%lld\n",ans);
	return 0;
}
