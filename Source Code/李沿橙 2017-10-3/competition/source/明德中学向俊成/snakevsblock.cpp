#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
int a[210][210];
int x,y;
int main()
{
	freopen("snakevsblock.in","r",stdin);freopen("snakevsblock.out","w",stdout);
	int i,j,k,m,n;
	long long s=4,t=0;
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			scanf("%d",&a[i][j]);
			if(a[i][j]>0)
			s=s+a[i][j];
			else if(a[i][j]<0&&(s+a[i][j])>0)
			{
				s=s+a[i][j];
				t=t-a[i][j];
			}
		}
	}
	scanf("%d",&m);
	for(i=1;i<=m;i++)
	{
		scanf("%d%d",&x,&y);
	}
	printf("%lld",t);
	return 0;
}
