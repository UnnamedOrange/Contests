#include<cstdio>
using namespace std;
long long p,t,a,b,c,a1,b1,c1,l,n;
int main()
{
	freopen("carry.in","r",stdin);
	freopen("carry.out","w",stdout);
	scanf("%lld",&p);
	l=1e8;
	while (p)
	{
		scanf("%lld%lld%lld",&a,&b,&c);
		t=0,n=l/p,p--;
		if (a==b && b==c)
		{
			printf("-1\n");
			continue;
		}
		while (t<=n)
		{
			if (a&1 || b&1 || c&1) break;
			a1=a>>1,b1=b>>1,c1=c>>1;
			a=b1+c1,b=a1+c1,c=a1+b1;
			t++,l--;
		}
		if (t>n) t=-1;
		printf("%lld\n",t);
	}
	return 0;
}
