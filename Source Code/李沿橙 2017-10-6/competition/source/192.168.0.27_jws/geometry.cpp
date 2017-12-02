#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#define MAXN 100005
#define eps 0.000000001
int n,m;
int x[MAXN],y[MAXN];
using namespace std;

int ck(int num,int xp,int yp)
{
	double k;
	k=-((double)y[num]/(double)x[num]);
	if(k*xp+y[num]-yp>=eps) return 0;
	else return 1;
}

int main()
{
	freopen("geometry.in","r",stdin);
	freopen("geometry.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&x[i]);
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&y[i]);
	}
	sort(x+1,x+n+1);
	sort(y+1,y+n+1);
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		int xp,yp;
		scanf("%d%d",&xp,&yp);
		int l=0,r=n;
		while(l<r)
		{
			int mid=(l+r)/2+1,f=ck(mid,xp,yp);
			if(f==1) l=mid;
			else r=mid-1;
		}
		printf("%d\n",l);
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
