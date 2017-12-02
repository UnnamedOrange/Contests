#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
int a[30001]={0};
int main()
{
	freopen("Cube.in","r",stdin);freopen("Cube.out","w",stdout);
	int i,j,k,m,n,p,x[30000],y[30000],lc,t,s=0;
	char c[10];
	scanf("%d",&p);
	t=1;
	for(i=1;i<=p;i++)
	{
		gets(c);
		lc=strlen(c);
		if(c[0]=='M')
		{
			int bj=0;
			for(j=2;j<lc;j++)
			{
				if(c[j]<='9'&&c[j]>='0'&&bj==0)
				{
					x[t]=x[t]*10+c[j]-'0';
				}
				if(c[j]==' ')
				{
					bj=1;
				}
				if(c[j]<='9'&&c[j]>='0'&&bj==1)
				{
					y[t]=y[t]*10+c[j]-'0';
				}
			}
			t++;
		}
		else if(c[0]=='C')
		{	
			s=0;
			int count=0;
			for(j=2;j<lc;j++)
			{
				if(c[j]<='9'&&c[j]>='0')
				s=s*10+c[j]-'0';
			}
			for(j=1;j<=t;j++)
			{
				if(x[j]==s)
				count++;
			}
			printf("%d\n",count);
		}
	}
	return 0;
}
