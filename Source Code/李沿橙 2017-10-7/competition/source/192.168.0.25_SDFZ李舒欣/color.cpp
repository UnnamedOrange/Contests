#include<bits/stdc++.h>
using namespace std;
#define maxn 10000
int n,m,a[maxn],step,l,ans,r,s;
int read()
{
	int x=0;
	char c;
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9')
	{
		x=x*10+c-'0';
		c=getchar();
	}
	return x;
}
int main()
{
	freopen("color.in","r",stdin);
	freopen("color.out","w",stdout);
	n=read(),m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=m;i++)
	{
		step=read();
		if(step==1)
		{
			ans=0;
			l=read(),r=read(),s=read();
			for(int j=l;j<=r;j++)if(a[j]==s)ans++;
			printf("%d\n",ans);
		}
		else 
		{
			s=read();
			swap(a[s],a[s+1]);
		}
	}
	return 0;
}
