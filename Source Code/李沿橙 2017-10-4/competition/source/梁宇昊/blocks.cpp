#include<cmath>
#include<cstdio>
#include<iostream>
#define ll long long
using namespace std;

int n,m,a[1000007],Min=123456789,Max=-1*Min;

inline int pdzq(int x[],int q)
{
	int tot=0;
	for(register int i=1;i<=n;i++)
		if(x[i]>=q)	tot++;
	return tot;
}

inline int pd(int x)
{
	if(x>Max)	return 0;
	if(x<=Min)	return n;
	int b[1000007];
	for(register int i=1;i<=n;i++)
		b[i]=a[i];
	b[0]=123456789;
	b[n+1]=123456789;
	int rp=0,len=0;
	while("The tast is the craziest!")
	{
		rp++;
		for(int i=1;i<=n;i++)
			if(b[i]>x)
			{
				int id=-1;
				b[i]-=1;
				if(b[i+1]>b[i-1])	b[i-1]+=1,id=i-1;
				else b[i+1]+=1,id=i+1;
				if(rp==1)	len=pdzq(b,x);
				else
				{
					int len2=pdzq(b,x);
					if(len2<len)	b[i]+=1,b[id]-=1;
					else len=len2;
				}
			}
		if(rp>=1000000)	return len;
	}
}

int main()
{
	freopen("blocks.in","r",stdin);
	freopen("blocks.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(register int i=1;i<=n;i++)
		scanf("%d",a+i),Max=max(Max,a[i]),Min=min(Min,a[i]);
	for(register int abc=1;abc<=m;++abc)
	{
		int b;
		scanf("%d",&b);
		int len=pd(b);
		printf("%d ",len);
	}
	return 0;
}
