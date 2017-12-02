#include<bits/stdc++.h>
using namespace std;
int n,need[30],timepeople[30],p[1500],all,tot,minn,have[30],ans=99999999;
bool may()
{
	int i;
	for(i=0;i<=23;i++)
		if(have[i]<need[i])return false;
	return true;
}
void dfs(int last)
{
	int j,i;
	if(minn>=ans)return;
	if(may())
	{
		ans=minn;
		return ;
	}
	for(i=last+1;i<=tot;i++)
	{
		for(j=0;j<=7;j++)
		{
			if(p[i]+j<=23)have[p[i]+j]++;
			else have[p[i]+j-24]++;
		}
		minn++;
		dfs(i+1);
		for(j=0;j<=7;j++)
		{
			if(p[i]+j<=23)have[p[i]+j]--;
			else have[p[i]+j-24]--;
		}
		minn--;
		dfs(i+1);
	} 
}
int main()
{
	int i,j; 
	freopen("cashier.in","r",stdin);
	freopen("cashier.out","w",stdout);
	scanf("%d",&all);
	while(all)
	{
		for(i=0;i<=23;i++)scanf("%d",&need[i]);
		for(i=0;i<=23;i++)
		{
			scanf("%d",&timepeople[i]);	
			while(timepeople[i])
			{
				tot++;
				p[tot]=i;
				timepeople[i]--;
			}
		}
		ans=99999999;
		minn=0;
		dfs(1);
		printf("%d\n",ans);
		all--;
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
