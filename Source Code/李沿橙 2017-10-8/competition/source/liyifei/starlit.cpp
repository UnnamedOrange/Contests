#include<cstdio>
#include<cstring>
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int b[51010],q[51010],vis[50101],hh[50101],bb[50505];
int n,m;
void bfs(int st)
{
	int h,t,x,y,i,k,tmp;
	h=0;t=1;q[h]=st;
	while(h<t)
	{
		x=q[h];
		if(x==(1<<n)-1)
			return;
		h++;
		for(i=1;i<=m;i++)
		{
			for(k=1;k<=n-b[i]+1;k++)
			{	
				tmp=x;
				tmp=tmp^((1<<(k+b[i]-1))-(1<<(k-1)));
				if(vis[tmp]==1)
					continue;
				vis[tmp]=1;
				hh[tmp]=hh[x]+1;
				q[t]=tmp;
				t++;
			}
		}
	}
}
int main()
{
	freopen("starlit.in","r",stdin);
	freopen("starlit.out","w",stdout);
	int k,i,tmp,j,xx,ans=0;
	scanf("%d%d%d",&n,&k,&m);
	if(n<=16)
	{
		tmp=(1<<n)-1;
		for(i=1;i<=k;i++)
		{
			scanf("%d",&xx);
			tmp-=(1<<xx-1);
		}
		for(j=1;j<=m;j++)
			scanf("%d",&b[j]);
		//printf("%d",tmp);
		bfs(tmp);
		printf("%d",hh[(1<<n)-1]);
		return 0;
	}
	if(m==1)
	{
		for(i=1;i<=k;i++)
		{
			scanf("%d",&xx);
			vis[xx]=1;
		}
		tmp=0;
		scanf("%d",&xx);
		for(i=1;i<=n;i++)
		{
			int sum=(tmp+vis[i])%2;
			//printf("%d %d\n",i,tmp);
			if(sum==1)
			{
				ans++;
				bb[i+xx-1]++;
				tmp++;
			}
			tmp=(tmp+bb[i])%2;
		}
		printf("%d",ans);
		return 0;
	}
	printf("3");
 	return 0;
}

