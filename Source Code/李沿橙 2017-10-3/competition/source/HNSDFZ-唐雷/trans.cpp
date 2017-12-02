#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
using namespace std;
int n,k;
char s[1000005];
int a[1000005];
bool vis[1000005];
int main()
{
	freopen("trans.in","r",stdin);
	freopen("trans.out","w",stdout);
	while(scanf("%d%d",&n,&k)!=EOF)
	{
		memeset(vis,0,sizeof(vis));
		scanf("%s",s+1);for(int i=1;i<=n;++i)a[i]=s[i]-'0';
		int tot=0;bool f=0;
		for(int i=1;i<n;++i)
		{
			if(a[i]==2&&a[i+1]==3)
			{
				tot++;
				if(i&1)
				{
					a[i+1]=2;vis[i+1]=1;
				}
				else
				{
					a[i]=3;
					if(vis[i])
					{
						if((k-tot)&1)a[i]=2,f=1;
						else f=1;
					}
					vis[i]=1;
					i-=2;
				}
				if(tot==k)f=1;
				if(f)break;
			}
		}
		for(int i=1;i<=n;++i)
		printf("%d",a[i]);printf("\n");
	}
	return 0;
}
