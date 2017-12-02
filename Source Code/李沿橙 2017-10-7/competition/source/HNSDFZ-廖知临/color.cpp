#include<cstdio>
using namespace std;
int n,m,a[300005],l,r,c;
inline int read()
{
	int x=0;char c;
	c=getchar();
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
    n=read();m=read();
    for(int i=1;i<=n;i++)
    	a[i]=read();
	for(int i=1;i<=m;i++)
	{
		if(read()==1)
		{
			int ans=0;
			l=read();r=read();c=read();
			for(int i=l;i<=r;i++)
				if(a[i]==c)	ans++;
			printf("%d\n",ans);
		}
		else
		{
			c=read();
			c=a[c];a[c]=a[c+1];a[c+1]=c;
		}
	}
    return 0;
}
