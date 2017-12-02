#include<bits/stdc++.h>
using namespace std;
#define maxn 405
long long n,m,k,a[maxn][maxn],sum[maxn][maxn],ans;
int read()
{
	int x=0;
	char c;
	c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
	return x;
}
int main()
{
	freopen("rally.in","r",stdin);
	freopen("rally.out","w",stdout);
	n=read(),m=read(),k=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			a[i][j]=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			sum[i][j]=(sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+a[i][j])%k;
	if(n>110)
	{
		for(int w=1;w<=n;w++)
			for(int l=1;l<=m;l++)
				if(sum[w][l]%k==0)ans+=(n-w+1)*(m-l+1);
		printf("%d",ans);
		return 0;
	}
	for(int w=1;w<=n;w++)
		for(int l=1;l<=m;l++)
			for(int i=w;i<=n;i++)
				for(int j=l;j<=m;j++)
					if(!((sum[i][j]-sum[i-w][j]-sum[i][j-l]+sum[i-w][j-l])%k))ans++;
	printf("%d",ans);
}
