#include<bits/stdc++.h>
using namespace std;
long long ans[2000][2000],fina;
bool en;
int n,m,p,all,use[450][450],k=1;
int dfs(int x,int num,long long sum,int hang)
{
	if (all+1==x) 
		{en=1;return 0;}	
	for (int i=num;i<=all;i++) 
	{
		if(en==1)	return 0;
		ans[hang][k++]=sum+use[hang][i];
		dfs(x+1,i+1,sum+use[hang][i],hang);
	}	
}
int dfsfin(int x,int num,long long sum,int lie)
{
	if (all+1==x) 
		{en=1;return 0;}	
	for (int i=num;i<=all;i++) 
	{
		if(en==1)	return 0;
		if((sum+ans[i][lie])%p==0)	fina++;
		dfsfin(x+1,i+1,sum+ans[i][lie],lie);
	}	
}
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
	freopen("rally.in","r",stdin);
	freopen("rally.out","w",stdout);
	n=read();m=read();p=read();
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
			use[i][j]=read();
	}
	all=m;
	for(int j=1;j<=n;j++)
	{
		k=1;	
		for(int i=1;i<=m;i++)
			{en=0;dfs(i,i,0,j);}	
	}
	all=n;
	for(int i=1;i<=k-1;i++)
	{
		for(int j=1;j<=n;j++)
			{en=0;dfsfin(j,j,0,i);}
	}
	printf("%lld",fina);
	return 0;
}
