#include <bits/stdc++.h>
using namespace std;
int read()
{
	int x=0,y=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')y=-1;c=getchar();}
	while(c<='9'&&c>='0'){x=x*10+c-'0';c=getchar();}
	return x*y;
}
int n;int ans=0;int ax[1005][1005];
void a()
{
	for(int i=1;i<=1000;i++)
		for(int j=1;j<=i/2;j++)
		{
			if(j==1)ax[i][j]=i,ax[i][j]%=7;
			else ax[i][j]=ax[i][j-1]*(i-j+1),ax[i][j]%=7;
		}
	return;
}
int doit(int x)
{
	int y=x/2;int anss=0;
	for(int i=1;i<=y;i++)
	{
		anss+=ax[x][i];
		anss%=7;
	}
	return anss;
}
int main()
{	freopen("stack.in","r",stdin);
	freopen("stack.out","w",stdout);
	a();
	n=read();
	/*for(int i=1;i<=10;i++)
		{
			for(int j=1;j<=i/2;j++)cout<<ax[i][j]<<" ";cout<<endl; 
		}*/
	for(int i=1;i<=n;i++)
	{
		ans+=doit(i);
		ans%=7;
	}
	cout<<ans;
	return 0;
}
