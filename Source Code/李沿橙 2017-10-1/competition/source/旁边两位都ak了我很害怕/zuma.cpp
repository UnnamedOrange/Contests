#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<string>
#include<cmath>
#include<ctime>
#include<queue>
#include<map>
#include<vector>
#define rint register int
#define debug(x) cerr<<#x<<"="<<x<<endl
#define fgx cerr<<"-------------"<<endl
#define min(x,y) (x>y?y:x)
typedef long long ll;
using namespace std;
int f[201][201][2][3];
const int inf=1e9;
char c[2001];
int main()
{   freopen("zuma.in","r",stdin);
	freopen("zuma.out","w",stdout);
	scanf("%s",c+1);
	int n=strlen(c+1);
	for(rint i=1;i<=n;i++)
	for(rint j=1;j<=n;j++)
	for(rint k=0;k<=1;k++)
	for(rint u=0;u<=2;u++) f[i][j][k][u]=inf;
	for(rint i=1;i<=n;i++) f[i][i][c[i]-'0'][1]=0;
	for(rint j=2;j<=n;j++)
	for(rint i=1;i+j-1<=n;i++)
	{	int k=i+j-1;
		for(rint u=i;u<k;u++)
		{	for(rint d=0;d<=2;d++)
			for(rint i1=0;i1<=2;i1++)
			for(rint i2=0;i2<=2;i2++)
			if(i1+i2+d>=3)
			{	f[i][k][0][0]=min(f[i][k][0][0],f[i][u][0][i1]+f[u+1][k][0][i2]+d),
				f[i][k][1][0]=min(f[i][k][1][0],f[i][u][1][i1]+f[u+1][k][1][i2]+d);
				if(i2+d==3) 
				f[i][k][0][i1]=min(f[i][k][0][i1],f[i][u][0][i1]+f[u+1][k][1][i2]+d),
				f[i][k][1][i1]=min(f[i][k][1][i1],f[i][u][1][i1]+f[u+1][k][0][i2]+d);
				if(i1+d==3) 
				f[i][k][0][i2]=min(f[i][k][0][i2],f[i][u][1][i1]+f[u+1][k][0][i2]+d),
				f[i][k][1][i2]=min(f[i][k][1][i2],f[i][u][0][i1]+f[u+1][k][1][i2]+d);
			}
			else
			f[i][k][0][i1+i2+d]=min(f[i][k][0][i1+i2+d],f[i][u][0][i1]+f[u+1][k][0][i2]+d),
			f[i][k][1][i1+i2+d]=min(f[i][k][1][i1+i2+d],f[i][u][1][i1]+f[u+1][k][1][i2]+d);
		}
		if(f[i][k][0][0]>f[i][k][1][0]) f[i][k][0][0]=f[i][k][1][0];
		else f[i][k][1][0]=f[i][k][0][0];
	}
	printf("%d\n",f[1][n][0][0]);
 	return 0;
}


