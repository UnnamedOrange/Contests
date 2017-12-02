#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
int a[300010];
int main()
{
	freopen("color.in","r",stdin);freopen("color.out","w",stdout);
	int i,j,k,m,n;
	int x,x1,y1,t,s=0,x2;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	for(i=1;i<=m;i++)
	{
		s=0;
		scanf("%d",&x);
		if(x==1)
		{
			t=0;
			scanf("%d%d%d",&x1,&y1,&t);
			for(j=x1;j<=y1;j++)
			{
				if(a[j]==t)
				{
					s++;
				}
			}
			printf("%d\n",s);
		}
		else if(x==2)
		{
			scanf("%d",&x2);
			t=a[x2];
			a[x2]=a[x2+1];
			a[x2+1]=t;
		}
	}
	return 0;
}
