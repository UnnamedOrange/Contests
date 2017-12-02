#include<cstdio>
#include<iostream>

using namespace std;

int time,a[52],b[52],work[52];
int ans=0;
bool checkg()
{
	for(int i=0;i<=7;++i)
	{
		if(a[i]!=0)	return false;
	}
	return true;
}

void greed()
{
	for(int i=8;i<24;++i)
	{
		for(int j=i;j>=i-8;--j)
		{
			a[i]-=work[j];
			if(a[i]<0)	{a[i]=0;break;}
		}
		for(int j=i;j>=i-8;--j)
		{
			if(b[j]<=a[i])	{a[i]-=b[j],work[j]+=b[j],b[j]=0;}
			if(b[j]>a[i])	{b[j]-=a[i],work[j]+=a[i],a[i]=0;}
			if(a[i]==0)	break;
		}
	}
	for(int i=0;i<24;++i)
		ans+=work[i];
	printf("%d\n",ans);
	--time;
	return ;
}

int main()
{
	freopen("cashier.in","r",stdin);
	freopen("cashier.out","w",stdout);
	scanf("%d",&time);
	while(time)
	{
		ans=0;
		for(int i=0;i<24;++i)
			scanf("%d",&a[i]);
		for(int i=0;i<24;++i)
			scanf("%d",&b[i]);
		if(checkg())	{greed();continue;}
		
		
		printf("-1\n");
		
		--time;
	}
	return 0;
}
