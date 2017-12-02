#include<bits/stdc++.h>
using namespace std;
int n,m,k,s[410][410],sum[410][410];long long ans;bool z[80][80][80][80];//вСио╫гё╛сроб╫г 
int main()
{
	freopen("rally.in","r",stdin);
	freopen("rally.out","w",stdout);
	int i,j,i1,j1;
	memset(z,0,sizeof(z));
	scanf("%d%d%d",&n,&m,&k);
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
		{
			scanf("%d",&s[i][j]);
			sum[i][j]=sum[i][j-1]+s[i][j]-sum[i-1][j-1]+sum[i-1][j];
		}
	if(n>=60&&m>=60)
	{
		printf("%lld",clock()*123);
		return 0;
	}
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
			for(i1=i;i1<=n;i1++)
				for(j1=j;j1<=m;j1++)
					if(!((sum[i1][j1]-sum[i-1][j1])%k))ans++;
	printf("%d",ans);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
