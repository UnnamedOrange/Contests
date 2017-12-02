#include<cstdio>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<cstring>
#include<iostream>
using namespace std;
const int MAXN=1e5+10;
int a[MAXN],b[MAXN];
int main()
{
	int k,l,m,n,tot;
	double x1,x2,y1,y2,ans;
	freopen("geometry.in","r",stdin);
	freopen("geometry.out","w",stdout);
	
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	for (int i=1;i<=n;i++) scanf("%d",&b[i]);
	sort(a+1,a+1+n);sort(b+1,b+1+n);
	
	scanf("%d",&m);
	for (int i=1;i<=m;i++)
	{
		scanf("%lf%lf",&x2,&y2);
		tot=0;
		for (int j=1;j<=n;j++)
		{
			x1=a[j];y1=b[j];
			ans=(x1*x2*y1)/(y1*x2+y2*x1);
			if (ans<x2) tot++;
		}
		printf("%d\n",tot);
	}	
	
	
	fclose(stdin);
	fclose(stdout);
	
	return 0;
}
