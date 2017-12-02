#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lint long long
#define N 100010
using namespace std;
int x0[N],y0[N];
inline int check(int x1,int y1,int x0,int y0)
{
	return (lint)x1*y0+(lint)x0*y1>=(lint)x0*y0;
}
inline int solve(int x,int y,int L,int R)
{
	int mid=(L+R)>>1;
	while(L<=R)
	{
		if(check(x,y,x0[mid],y0[mid])) L=mid+1;
		else R=mid-1;mid=(L+R)>>1;
	}
	return R;
}
int main()
{
	freopen("geometry.in","r",stdin);
	freopen("geometry.out","w",stdout);
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&x0[i]);
	for(int i=1;i<=n;i++)
		scanf("%d",&y0[i]);
	sort(x0+1,x0+n+1);
	sort(y0+1,y0+n+1);
	int m;scanf("%d",&m);
	while(m--)
	{
		int x,y;scanf("%d%d",&x,&y);
		printf("%d\n",solve(x,y,1,n));
	}
	return 0;
}
