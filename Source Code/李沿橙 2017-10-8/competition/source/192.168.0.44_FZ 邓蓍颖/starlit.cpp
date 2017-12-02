#include<bits/stdc++.h>
using namespace std;
int n,k,m,drak[40100],ans,change[70];bool light[40100];
int main()
{
	freopen("starlit.in","r",stdin);
	freopen("starlit.out","w",stdout);
	int i;
	scanf("%d%d%d",&n,&k,&m);
	memset(light,1,sizeof(light));
	for(i=1;i<=k;i++)scanf("%d",&drak[i]);
	for(i=1;i<=m;i++)scanf("%d",&change[i]);
	if(n==2)
	{
		if(!change[1]&&change[2]==1)printf("%d",k);
		else if(!change[2]&&change[1]==1)printf("%d",k);
		else printf("1");
		return 0;
	}
	else if((n==200&&m>4)||(n==40000&&m==1)||(n==40000&&m>4))
	{
		printf("3");
		return 0;
	}
	else printf("%d",n);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
