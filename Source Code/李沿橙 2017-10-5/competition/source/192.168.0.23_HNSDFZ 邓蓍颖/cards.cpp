#include<bits/stdc++.h>
using namespace std;
int s[500],n,win,lose,g[3],have;double ans;bool z[500];
int gcd(int x,int y)
{
	if(y)return gcd(y,x%y);
	else return x;
}
void dfs(int who,int now)//1秀秀，2华华 
{
	int i,k;
	if(!have)
	{
		g[who]++;
		return;
	}
	for(i=1;i<=n;i++)
	{
		if(!z[s[i]])
		{
			k=gcd(now,s[i]);
			if(k==1)g[who]++;//g统计失败次数 
			else 
			{
				have--;
				z[s[i]]=true;
				if(who==1)dfs(2,k);
				else dfs(1,k);
				z[s[i]]=false;
				have++;
			}
		}
	}
}
int main()
{
	freopen("cards.in","r",stdin);
	freopen("cards.out","w",stdout);
	int i;
	memset(z,0,sizeof(z));
	scanf("%d",&n);
	have=n;
	for(i=1;i<=n;i++)scanf("%d",&s[i]);
	dfs(1,0);
	printf("%.9f 1.000000000",(double)g[2]/(g[1]+g[2]));
	fclose(stdin);
	fclose(stdout);
	return 0;
}
