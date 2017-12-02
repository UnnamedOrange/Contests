#include<iostream>
#include<cstdio>
#include<cstring>

#define N 404

using namespace std;
int n,m,k,ans;
int a[N][N],s[N][N];

inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f; 
}

int main()
{
	freopen("rally.in","r",stdin);freopen("rally.out","w",stdout);
	n=read();m=read();k=read();
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++)
	{
		a[i][j]=read();
		s[i][j]=a[i][j]+s[i-1][j]+s[i][j-1]-s[i-1][j-1];
	}
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++)
	{
		for(int x=i;x<=n;x++) 
		  for(int y=j;y<=m;y++)
		  {
			  int tmp=(s[x][y]-s[i-1][y]-s[x][j-1]+s[i-1][j-1])%k;
		  	  if(tmp==0) ans++;
		  }
	}
	printf("%d\n",ans);
	fclose(stdin);fclose(stdout);
	return 0;
	
}
