#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
long long xx[1010],yy[1010],f[1010];
int cnt,dpy,dpx;
void find_dep(long long x)
{
	int i=60;
	while(x>1)
	{
		while(f[i]>=x)
			i--;
		//printf("%d %d\n",x,f[i]);
		yy[++cnt]=x-f[i];
		dpy++;
		x=x-f[i];
	}
}
int main()
{
	int i,j,m;
	freopen("fibonacci.in","r",stdin);
	freopen("fibonacci.out","w",stdout);
	long long n=1000000000000,x,y;
	f[1]=1;
	f[2]=1;
	i=2;
	while(f[i]<=n)
	{
		i++;
		f[i]=f[i-1]+f[i-2];
	}
	scanf("%d",&m);
	for(j=1;j<=m;j++)
	{
		scanf("%lld%lld",&x,&y);
		cnt=0;
		dpy=0;
		xx[0]=x;
		find_dep(x);
		dpx=dpy;
		for(i=1;i<=cnt;i++)
			xx[i]=yy[i];
		cnt=0;
		dpy=0;
		yy[0]=y;
		find_dep(y);
		//printf("%d %d\n",dpx,dpy);
		if(dpy<dpx)
		{
			for(i=0;i<=dpy;i++)
			{
				if(xx[dpx-dpy+i]==yy[i])
				{
					printf("%d\n",yy[i]);
					break;
				}
			}
		}
		else
		{
			for(i=0;i<=dpx;i++)
			{
				if(yy[dpy-dpx+i]==xx[i])
				{
					printf("%d\n",xx[i]);
					break;
				}
			}
		}
	} 
	return 0;
}
