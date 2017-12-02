#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 30
#define INF 10000000
using namespace std;
int a[N],b[N],c[N],d[1010],e[N],top,ans[N];
const int n=24;
int main()
{
	freopen("cashier.in","r",stdin);
	freopen("cashier.out","w",stdout);
	int T;scanf("%d",&T);
	int PT=T;
while(T--)
{
	int ss=0,s,pans;top=0;
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]),ss+=a[i];
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&b[i]);
		for(int j=1;j<=b[i];j++)
			d[++top]=i;
	}
	int TT=4000000/PT/top,minans=INF;
	while(TT--)
	{
		s=ss;pans=0;
		memcpy(c,a,sizeof(c));
		random_shuffle(d+1,d+top+1);
		for(int i=1;i<=top&&s;i++,pans++)
			for(int x=d[i];x<d[i]+8;x++)
				c[(x>n)?(x-n):x]?(c[x]--,s--):0;
		minans=min(minans,pans);
	}
	if(minans==INF)
	{
		printf("%d\n",-1);
		continue;
	}
	printf("%d\n",minans);
}
	return 0;
}
