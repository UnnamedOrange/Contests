#include<bits/stdc++.h>
using namespace std;
#define maxn 100000
int ans=4,a[maxn],c[maxn],tem,n,m,k;
int read()
{
	int x=0;
	char c;
	c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
	return x;
}
int search(int mo,int last)
{
	int b[1000];
	if(mo>=ans)return 0;
	int sum=0;
	for(int i=1;i<=n;i++)if(a[i]==0)sum++;
	if(sum==n)
	{
		ans=min(ans,mo);
		return 0;
	}
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n-c[i]+1;j++)
		{
			for(int q=1;q<=n;q++)b[q]=a[q];
			for(int p=j;p<j+c[i];p++)a[p]^=1;
			search(mo+1,i);
			for(int q=1;q<=n;q++)a[q]=b[q];
		}
}
int main()
{
	freopen("starlit.in","r",stdin);
	freopen("starlit.out","w",stdout);
	n=read(),k=read(),m=read();
	if(n<=16)ans=10;
	for(int i=1;i<=k;i++)
	{
		tem=read();
		a[tem]=1; 
	}
	for(int i=1;i<=m;i++)c[i]=read();
	search(0,0);
	printf("%d",ans);
	return 0;
}
