#include<bits/stdc++.h>
#define lol long long
using namespace std;
lol read()
{
	lol x=0,y=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')y=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*y;
}
int n,m,k;
int num[405][405];
lol a[405][405],ans=0;
int main()
{	
	freopen("rally.in","r",stdin);
	freopen("rally.out","w",stdout);
	n=read();m=read();k=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)num[i][j]=read();
	//输入 
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		a[i][j]=a[i-1][j]+a[i][j-1]-a[i-1][j-1]+num[i][j]; 
	//右上角前缀和 
	for(int i=0;i<n;i++)
		for(int j=i+1;j<=n;j++){
			lol nm[405];
			for(int l=1;l<=m;l++)
			{
				lol nu=a[j][l]-a[i][l]-a[j][l-1]+a[i][l-1];
				nm[l]=nu%k;
			}
			lol lek=0,letop=0,les=0;
			for(int i=1;i<=m;i++){
				if(nm[i]){lek+=nm[i],letop=0;
					if(lek%k==0)les++,ans+=les,lek%=k;}
				else letop++,les++,ans+=letop;
			}
			
		}
		printf("%lld\n",ans);
	return 0;
}
