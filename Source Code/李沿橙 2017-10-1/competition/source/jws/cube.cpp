#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#define MAXP 30005
int p;
int h[MAXP];
int num[MAXP],d[MAXP];
using namespace std;
int main()
{
	freopen("cube.in","r",stdin);
	freopen("cube.out","w",stdout);
	scanf("%d",&p);
	for(int i=1;i<=30000;i++)
	{
		h[i]=i;
		num[i]=1;
	}
	for(int i=1;i<=p;i++)
	{
		char x=' ';
		while(x!='M' && x!='C') scanf("%c",&x);
		if(x=='M')
		{
			int a,b;
			scanf("%d%d",&a,&b);
			while(h[a]!=a) a=h[a];
			while(h[b]!=b) b=h[b];
			d[a]=num[b];
			num[b]+=num[a];
			h[a]=b;
		}
		else if(x=='C')
		{
			int a;
			scanf("%d",&a);
			int ans=0;
			while(h[a]!=a)
			{
				ans+=d[a];
				a=h[a];
			}
			printf("%d\n",ans);
		}
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
