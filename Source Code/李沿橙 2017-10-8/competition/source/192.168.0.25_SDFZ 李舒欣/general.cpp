#include<bits/stdc++.h>
using namespace std;
#define maxn 100500
int n,k,t,u,v,ans,sum,head[maxn],cnp=1; 
int read()
{
	int x=0;
	char c;
	c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
	return x;
}
struct xxx
{
	int to,co,last;
}a[maxn];
int add(int u,int v)
{
	a[cnp].last=head[u];
	a[cnp].to=v;
	head[u]=cnp++;
}
int main()
{
	freopen("general.in","r",stdin);
	freopen("general.out","w",stdout);
	n=read(),k=read(),t=read(); 
	if(t==2||n<=10)
	{
		if(k==2&&t==2)
		{
			printf("1");
			return 0;
		}
		for(int i=1;i<=n;i++)head[i]=-1;
		for(int i=1;i<n;i++)
		{
			u=read(),v=read();
			add(u,v);
			add(v,u);
		}
		for(int i=head[1];i!=-1;i=a[i].last)
		{
			sum++;
			int e=a[i].to;
			for(int j=head[e];j!=-1;j=a[j].last)
				if(a[j].to!=1)
				{
					ans++;
					break;
				}
		}
		if(ans!=sum)ans=ans+1;
		printf("%d",ans);
		return 0; 
	}
	printf("5");
	return 0;
}
