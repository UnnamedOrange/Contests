#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
using namespace std;
int n,k;
int a[150005],b[150005],cnt;
bool check(int x,int y)
{
	int e=x+y;
	int p=sqrt(e);
	if(p*p!=e)return 0;
	return 1;
}
int main()
{
	freopen("division.in","r",stdin);
	freopen("division.out","w",stdout);
	scanf("%d%d",&n,&k);
	int mx=0,cnt=0;
	for(int i=1;i<=n;++i){scanf("%d",&a[i]);mx=max(mx,a[i]);if(a[i]==2)b[++cnt]=i;}
	if(n==2)
	{
		if(check(a[1],a[2]))printf("%d\n%d",2,1);
		else printf("%d\n",1);
		return 0;
	}
	if(mx<=2)
	{
		if(cnt<=1)printf("%d\n",1);
		else if(k==1)
		{
			printf("%d\n",cnt);
			for(int i=2;i<=cnt;++i)
			{
				printf("%d ",b[i]-1);
			}
			printf("\n");return 0;
		}
		else if(k==2)
		{
			printf("%d\n",cnt%2?cnt/2+1:cnt/2);
			if(cnt%2)
			for(int i=1;i<cnt;i+=2)
			{
				printf("%d ",b[i]+1);
			}
			else
			for(int i=2;i<cnt;i+=2)
			{
				printf("%d ",b[i]+1);
			}
			printf("\n");return 0;
		}
		return 0;
	}
	return 0;
}
