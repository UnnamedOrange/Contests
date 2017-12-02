#include<cstdio>
#include<cstring>
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int a[405][406],sum[405][405],vis[1110110];
int main()
{
	freopen("rally.in","r",stdin);
	freopen("rally.out","w",stdout);
	int n,m,p,j,i,k,ans,x;
	scanf("%d%d%d",&n,&m,&p);
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
		{
			scanf("%d",&a[i][j]);
			sum[i][j]=(sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+a[i][j])%p;
		}
	ans=0;
	for(i=1;i<=n;i++)
	{
		for(j=i;j<=n;j++)
		{
			for(k=0;k<=m;k++)
			{
				x=sum[j][k]-sum[i-1][k];
				x=(x+p)%p;
				//if(vis[p-x]!=0)
				//	printf("%d %d %d %d\n",i,j,k,x);
				ans=ans+vis[(p-x)%p];
				vis[x]++;
			}
			for(k=1;k<=m;k++)
				vis[(sum[j][k]-sum[i-1][k]+p)%p]=0;
		}
	}
	printf("%d",ans);
 	return 0;
}

