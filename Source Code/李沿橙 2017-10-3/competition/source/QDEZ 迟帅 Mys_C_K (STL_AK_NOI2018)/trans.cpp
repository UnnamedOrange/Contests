#include<iostream>
#include<cstring>
#include<cstdio>
#define N 1000010
using namespace std;
int a[N];
int main()
{
	freopen("trans.in","r",stdin);
	freopen("trans.out","w",stdout);
	int n,k;
	while(scanf("%d%d",&n,&k)!=EOF&&(n||k))
	{
		for(int i=1;i<=n;i++)
			scanf("%1d",&a[i]);
		a[n+1]=-1;
		for(int i=1;i<=n;i++)
			if(!k) break;
			else if(a[i]==2&&a[i+1]==3)
				if(i&1) a[i+1]=2,k--;
				else a[i]=3,k--;
		for(int i=1;i<=n;i++)
			printf("%d",a[i]);
		printf("\n");
	}
	return 0;
}
