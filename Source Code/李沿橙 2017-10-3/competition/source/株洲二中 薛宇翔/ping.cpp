#include <bits/stdc++.h>
using namespace std;
int read()
{
	int x=0,y=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')y=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*y;
}
int n,m,k=0;
int num1[100005],num[100005];
struct a{int a,b,hand,next;}e[100005];
void add(int x,int y)
{	k++;
	e[k].a=x;e[k].b=y;e[k].next=e[x].hand;
	e[x].hand=k;
}
int main ()
{	freopen("ping.in","r",stdin);
	freopen("ping.out","w".stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int s1=read(),s2=read();
		add(s1,s2);add(s2,s1);
	}
	int kx;
	for(int i=1;i<=n;i++)
	{
		if(!e[i].next)kx=i;
	}
	num1[1]=kx;
	for(int i=2;i<=n;i++)
	{	int xyx=e[num1[i-1]].hand;
		if(e[xyx].b!=num1[i-2])num1[i]=e[xyx].b;
		else num1[i]=e[e[xyx].next].b;
	}
	int k;
	k=read();
	for(int i=1;i<=n;i++)num[num1[i]]=i;
	int anss[100005];
	memset(anss,0,sizeof(anss));
	for(int i=1;i<=k;i++)
	{
		int aa=num[read()],bb=num[read()];
		anss[min(aa,bb)]=1;anss[max(aa,bb)+1]=-1;
	}
	for(int i=1;i<=n;i++)anss[i]=anss[i-1]+anss[i];
	int ans=0,ad[10000],ji=0;
	for(int i=1;i<n;i++)if(anss[i]>anss[i+1])ans++,ad[++ji]=i;
	cout<<ans;
	for(int i=1;i<=ji;i++)printf("%d ",num[ad[i]]);
	return 0;
}
