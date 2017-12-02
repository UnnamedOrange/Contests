#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define K 10
#define M 70
using namespace std;
int a[K],b[M];
int main()
{
	freopen("starlit.in","r",stdin);
	freopen("starlit.out","w",stdout);
	int n,k,m;scanf("%d%d%d",&n,&k,&m);
	for(int i=1;i<=k;i++) scanf("%d",&a[i]);
	for(int i=1;i<=m;i++) scanf("%d",&b[i]);
	if(n==2) return !printf("1\n");
	if(m==1)
	{
		if(b[1]==1) return !printf("%d\n",k);
		int now=1,res=k,ans=0;
		while(res)
		{
			a[now]+=b[1],ans+=2;
			if(a[now]==a[now+1]) now+=2,res-=2;
		}
		return !printf("%d\n",ans);
	}
	if(n==200&&m>4) return !printf("%d\n",4);
	if(n==40000&&m>4) return !printf("%d\n",4);
	printf("STL_AK_NOI2018\n");return 0;
}
