#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

#define LL long long
const int N=200010;
int n,m,a[N],b[N];
LL k;

int cmp(const void *p1,const void *p2)
{
	return (*(int *)p1)-(*(int *)p2);
}

LL cal(LL ans)
{
	int i;
	LL s=0,top=m,gtmp;
	for (i=1;i<=n;i++)
	{
		gtmp=ans/a[i];
		while (top&&b[top]>gtmp)top--;
		s+=top;
	}
	return s;
}

int main()
{
	freopen("number.in","r",stdin);
	freopen("number.out","w",stdout);
	cin>>n>>m>>k;
	int i;
	for (i=1;i<=n;i++)scanf("%d",a+i);
	for (i=1;i<=m;i++)scanf("%d",b+i);
	qsort(a+1,n,sizeof(a[0]),cmp);
	qsort(b+1,m,sizeof(b[0]),cmp);
	LL ll=a[1]*(LL)b[1],rr=a[n]*(LL)b[m],mid;
	while (ll<rr)
	{
		mid=(ll+rr)/2;
		if (cal(mid)>=k)rr=mid;
		else ll=mid+1;
	}
	cout<<ll<<endl;
	return 0;
}
 
