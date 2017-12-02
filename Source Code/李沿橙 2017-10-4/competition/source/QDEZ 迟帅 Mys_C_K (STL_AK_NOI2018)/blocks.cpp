#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1000010
#define lint long long
using namespace std;
int b[N];lint a[N];
int main()
{
	freopen("blocks.in","r",stdin);
	freopen("blocks.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&b[i]);
	for(int i=1;i<=n;i++)
		a[i]=a[i-1]+b[i];
	while(m--)
	{
		int k,ans=0;scanf("%d",&k);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=i;j++)
				if(a[i]-a[j-1]>=(i-j+1)*(lint)k)
					ans=max(ans,i-j+1);
		printf("%d ",ans);
	}
	printf("\n");return 0;
}
