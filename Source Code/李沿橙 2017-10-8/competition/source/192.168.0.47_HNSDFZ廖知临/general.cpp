#include<bits/stdc++.h>
using namespace std;
int n,k,t,b[10000],num=1,ans=1;
inline int read()
{
	int x=0;char c;
	c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9')
		{x=x*10+c-'0';c=getchar();}
	return x;
}
struct pack{
	int dian;
	int bian;
}a[1000];
bool cmp(const pack &a,const pack &b)
{
    if(a.bian<b.bian)return 1;
    else return 0;
}
int main()
{
	freopen("general.in","r",stdin);
	freopen("general.out","w",stdout);
	n=read();k=read();t=read();
	int x,y;
	if(k==0)	{printf("%d",n);return 0;}
	for(int i=1;i<=n-1;i++)
	{
		x=read();y=read();
		a[x].bian++;a[y].bian++;
		if(x==1)	b[num++]=y;
		if(y==1)	b[num++]=x;
	}
	for(int i=1;i<=num-1;i++)
		ans+=(a[b[i]].bian-1);
	if(t==2)	{printf("%d",ans);return 0;}
	return 0;
}
