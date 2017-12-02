#include<bits/stdc++.h>
using namespace std;
int n,k,m,a[40005],b[70],ans;
inline int read()
{
	int x=0;char c;
	c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9')
		{x=x*10+c-'0';c=getchar();}
	return x;
}
int main()
{
	freopen("starlit.in","r",stdin);
	freopen("starlit.out","w",stdout);
	n=read();k=read();m=read();	
	for(int i=1;i<=k;i++)
		a[read()]=1;
	for(int i=1;i<=m;i++)
		b[i]=read();
	int i=1;
	while(i<=n)
	{
		while(a[i]==1)
			{i++;ans++;}	
		i++;
	}
	printf("%d",ans);
	return 0;
}
