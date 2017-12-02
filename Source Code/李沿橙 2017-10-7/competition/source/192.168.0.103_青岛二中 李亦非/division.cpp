#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
using namespace std;
vector<int>vis[303030];
int fa[303030],a[303030],f[303030],re[303030];
int find_set(int x)
{
	int y=x,z=y,tmp=0,t;
	while(fa[x]!=x)
		tmp+=re[x],x=fa[x];
	while(fa[y]!=x)
	{
		t=tmp;
		tmp-=re[y];
		re[y]=t;
		y=fa[y];
		fa[z]=x;
		z=y;
	}
	return x;	
}
int main()
{
	int n,ca,cnt=0,i,j,k,lst,c,xx,yy;
	freopen("division.in","r",stdin);
	freopen("division.out","w",stdout);
	scanf("%d%d",&n,&ca);
	for(i=1;i<=n;i++)
		fa[i]=i;
	for(i=1;i<=n;i++)
	scanf("%d",&a[i]);
	lst=n;
	for(i=n;i>=1;i--)
	{
		//printf("%d\n",i);
		for(j=1;j<=513;j++)
		{
			if(j*j-a[i]<=0)
				continue;
			c=vis[j*j-a[i]].size();
			if(c>0)
			{
				if(ca==1)
				{
					f[++cnt]=i;
					for(k=lst;k>i;k--)
						vis[a[k]].clear();
					lst=i;
					break;
				}
				else
				{
					for(k=0;k<c;k++)
					{
						xx=find_set(i);
						yy=find_set(vis[j*j-a[i]][k]);
						if(xx==yy)
						{
							if(re[i]!=0&&(re[i]+re[vis[j*j-a[i]][k]])%2==0)
							{
								f[++cnt]=i;
								for(k=lst;k>=i;k--)
								{
									vis[a[k]].clear();
									fa[k]=k;
									re[k]=0;
								}
								lst=i;
								break;
							}	
						}
						else
						{
							fa[xx]=yy;
							if(fa[vis[j*j-a[i]][k]]!=vis[j*j-a[i]][k])
							re[xx]=re[vis[j*j-a[i]][k]]+1;
							else
							re[xx]=1;
						}
					}
				}
			}
		}
		vis[a[i]].push_back(i);
	}
	printf("%d\n",cnt+1);
	for(i=cnt;i>=1;i--)
		printf("%d ",f[i]);
	return 0;
}
