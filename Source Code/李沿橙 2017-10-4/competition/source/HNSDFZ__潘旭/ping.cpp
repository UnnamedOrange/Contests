#include<iostream>
#include<cstdio>
#include<cstdlib>

using namespace std;
int n,m,x,y,a,b,k;
int o[20];

int main()
{
	freopen("ping.in","r",stdin);
	freopen("ping.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	o[i]=i;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&x,&y);
		
	}
	scanf("%d",&k);
	for(int i=1;i<=k;i++)
	scanf("%d%d",&a,&b);
	int t=1,z=n/k;
	printf("%d%d",t,z);
	fclose(stdin);
	fclose(stdout);
}
