#include<cstdio>
#include<algorithm>
#define maxn 10010
using namespace std;
int n,sum,tot,x;
int a[maxn],b[maxn];
double ans;
int gcd(int x,int y)
{
	if(y==0)
	return x;
	return gcd(y,x%y);
}
int main()
{
	freopen("cards.in","r",stdin);
	freopen("cards.out","w",stdout);
	scanf("%d",&n);
	sum=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]),b[i]=i;
		sum=gcd(sum,a[i]);
	}
	if(sum!=1)
	{
		if(n&1)
		puts("1.00000000 1.00000000");
		else
		puts("0.00000000 0.00000000");
		return 0;
	}
	sum=0;
	do
	{
		x=0;
		sum++;	
		for(int i=1;i<=n;i++)
		{
			x=gcd(x,a[b[i]]);
			if(x==1)
			{
				if((i&1)==0)
				tot++;
				break;
			}
		}
		
	}
	while(next_permutation(b+1,b+n+1));
	ans=(double)tot/sum;
	printf("%0.8lf 1.00000000\n",ans);
	return 0;
}
