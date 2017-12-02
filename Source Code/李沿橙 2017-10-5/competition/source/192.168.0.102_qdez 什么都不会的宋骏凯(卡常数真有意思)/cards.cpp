#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<ctime>
#include<map>
#include<queue>
#include<string>
#include<vector>
#define rint register int
#define debug(x) cerr<<#x<<"="<<x<<endl
#define fgx cerr<<"-------------"<<endl
typedef long long ll;
using namespace std;
int a[500],num[1010],b[500],g[1010][500];
double f[500][1010];
bool vis[500];
int gcd(int x,int y){return y?gcd(y,x%y):x;}
int main()
{	freopen("cards.in","r",stdin);
	freopen("cards.out","w",stdout);
	int n,k,ans=0,c=0,maxn=0; scanf("%d",&n);
	for(rint i=1;i<=n;i++)scanf("%d",&a[i]),b[i]=a[i],maxn=max(maxn,a[i]);
	for(rint i=1;i<=1000;i++)
	for(rint j=1;j<=n;j++)
	if(a[j]%i==0) num[i]++;
	for(rint i=1;i<=n;i++)
	{	int nn=0;
		for(rint j=1;j<=i;j++)
		if(i!=j&&gcd(i,j)!=1) nn++;
		if(nn&1) ans=1;
	}
	for(rint i=1;i<=1000;i++)
	for(rint j=1;j<=n;j++) g[i][j]=gcd(i,a[j]);
	for(rint i=1;i<=n;i++) f[1][a[i]]=1.0/n;
	for(rint i=1;i<n;i++)
	for(rint j=2;j<=maxn;j++)
	if(num[j])
	{	if(num[j]-i-1>=0)f[i+1][j]+=f[i][j]*1.0*(num[j]-i)/(n-i);
		for(rint u=1;u<=n;u++)
		if(a[u]%j!=0) f[i+1][g[j][u]]+=f[i][j]*1.0/(n-i);
	}
	double res=0;
	for(rint i=2;i<=n;i+=2) res+=f[i][1];
	printf("%.9lf %d.000000000",res,ans);
	return 0;
}
