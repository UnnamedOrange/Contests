#include<cstdio>
#define min(x,y) (x)<(y)?(x):(y)
using namespace std;
int f[1010],g[1010];
int n,t;
int inc(int x,int y)
{
	if(x+y>=7)
	return x+y-7;
	return x+y;
}
int main()
{
	freopen("stack.in","r",stdin);
	freopen("stack.out","w",stdout);
	scanf("%d",&n);
	f[0]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<=i;j++)
		g[j]=f[j];
		for(int j=1;j<=i;j++)
		{
			t=min(i-1,j);
			f[j]=inc(f[j-1],g[t]);
		}
	}
	printf("%d\n",inc(f[n],7-f[n-1]));
	return 0;
}
