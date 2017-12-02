#include<bits/stdc++.h>
using namespace std;
#define maxn 300000
int x[maxn],y[maxn],l,r,yes,m,px,py,n;
int read()
{
	int x=0;
	char c;
	c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9')
	{
		x=x*10+c-'0';
		c=getchar();
	}
	return x;
}
int check(int now)
{
	if(y[now]==0)return 1;
	float len=((float)x[now]/(float)y[now])*(float)py;
	if(px+len<x[now]+0.0)return 0;
	if(x[now]==0&&px!=0)return 0;
	return 1;
}
int main()
{
	freopen("geometry.in","r",stdin);
	freopen("geometry.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)x[i]=read();
	for(int i=1;i<=n;i++)y[i]=read();
	sort(x+1,x+1+n);
	sort(y+1,y+1+n);
	m=read();
	for(int i=1;i<=m;i++)
	{
		px=read(),py=read();
		l=0,r=n,yes=0;
		while(l<r)
		{
			int mid=(l+r)/2;
			int can=check(mid);
			if(yes)
			{
				l++;
				can=check(l);
				if(!can)l--,r--;
			}
			else if(can)
			{
				l=mid;
				if(l==mid)yes++;
			}
			else r=mid-1;
		}
		printf("%d\n",l);
	}
	return 0;
}
