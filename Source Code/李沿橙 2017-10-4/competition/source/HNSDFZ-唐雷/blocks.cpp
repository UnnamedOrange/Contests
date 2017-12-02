#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define N 1000005
using namespace std;
typedef long long ll;
int n,m,cnt,ans;
int a[N],que[N];
long long s[N];
int Max(int x,int y){return x>y?x:y;}
void work(int le,ll up,int x)
{
	if(s[que[cnt]]-s[que[cnt-1]]>up)return;
	int l=1,r=cnt;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(s[que[cnt]]-s[que[mid-1]]<=up)
		{ans=Max(ans,x-que[mid-1]);r=mid-1;}
		else l=mid+1;
	}
}
int main()
{
	freopen("blocks.in","r",stdin);
	freopen("blocks.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)scanf("%d",&a[i]);
	int t;
	for(int i=1;i<=m;++i)
	{
		ll sum=0;scanf("%d",&t);
		ans=0;cnt=0;
		memset(s,0,sizeof(s));
		memset(que,0,sizeof(que));
		int l=0;
		for(int j=1;j<=n;++j)
		{
			if(a[j]-t<0)
			{
				if(l)//front
				work(l,sum,j-1);
				if(a[j]-t<-sum)//can't go
				{
					s[j]=s[que[cnt]]-(a[j]-t+sum);
					que[++cnt]=j;
					l=cnt;
					sum=0;
				}
				else//can go
				{
					sum+=a[j]-t;
					ans=Max(ans,j-que[l]);
				}
			}
			else
			{
				sum+=a[j]-t;
				ans=Max(ans,j-que[l]);
			}
		}
		if(l)
		work(l,sum,n);
		printf("%d ",ans);
	}
	return 0;
}
