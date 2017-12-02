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
typedef long long ll;
using namespace std;
int f[201][6][10001],a[201][6],s[201][6],score[201][6];
vector<int> d[201];
int main()
{  	freopen("snakevsblock.in","r",stdin);
	freopen("snakevsblock.out","w",stdout);
	int n,x,y; scanf("%d",&n);
	for(rint i=1;i<=n;++i)
	for(rint j=1;j<=5;++j)
	{	scanf("%d",&a[i][j]);
		s[i][j]=s[i][j-1]+a[i][j];
		score[i][j]=score[i][j-1]-((a[i][j]<0)?a[i][j]:0);
	}
	int maxw=n*50,m; scanf("%d",&m);
	for(rint i=1;i<=n;i++) d[i].push_back(0);
	for(rint i=1;i<=m;i++) scanf("%d%d",&x,&y),d[x].push_back(y);
	for(rint i=1;i<=n;i++) sort(d[i].begin(),d[i].end()),d[i].push_back(5);
	for(rint i=0;i<=n;++i)
	for(rint j=1;j<=5;++j)
	for(rint k=0;k<=maxw;++k) f[i][j][k]=-1;
	int ll,rr;
	for(rint i=0;i<d[1].size();i++) if(d[1][i]<3) ll=d[1][i]; ll++;
	for(rint i=d[1].size()-1;i>=0;i--) if(d[1][i]>=3) rr=d[1][i];
	f[0][3][4]=0;
	for(rint k=ll;k<=rr;k++)
	for(rint u=1;u<=maxw;++u)
	{	for(rint l=5;l>=k;l--)
		if(u-s[1][l]+s[1][3-1]>=0&&f[0][3][u-s[1][l]+s[1][3-1]]!=-1&&u-s[1][l]+s[1][3-1]<=maxw) f[1][k][u]=max(f[1][k][u],f[0][3][u-s[1][l]+s[1][3-1]]+score[1][l]-score[1][3-1]),debug(k),debug(u),debug(l);
		for(rint r=1;r<=3;++r)
		if(u-(s[1][k]-s[1][r-1])>=0&&f[0][3][u-(s[1][k]-s[1][r-1])]!=-1&&u-(s[1][k]-s[1][r-1])<=maxw) f[1][k][u]=max(f[1][k][u],f[0][3][u-(s[1][k]-s[1][r-1])]+score[1][k]-score[1][r-1]);
	}
	for(rint i=2;i<=n;++i)
	{	int p=0,sz=d[i].size();
		for(rint j=1;j<=5;++j) //la
		{	if(p<sz&&d[i][p]==j-1) p++;
			for(rint k=d[i][p-1]+1;k<=d[i][p];++k) //now
			for(rint u=0;u<=maxw;++u)
			{	for(rint l=5;l>=k;l--)
				if(u-s[i][l]+s[i][j-1]>=0&&f[i-1][j][u-s[i][l]+s[i][j-1]]!=-1&&u-s[i][l]+s[i][j-1]<=maxw)
				f[i][k][u]=max(f[i][k][u],f[i-1][j][u-s[i][l]+s[i][j-1]]+score[i][l]-score[i][j-1]);
				for(rint r=1;r<=j;++r)
				if(u-(s[i][k]-s[i][r-1])>=0&&f[i-1][j][u-(s[i][k]-s[i][r-1])]!=-1&&u-(s[i][k]-s[i][r-1])<=maxw) f[i][k][u]=max(f[i][k][u],f[i-1][j][u-(s[i][k]-s[i][r-1])]+score[i][k]-score[i][r-1]);	
			}
		}
	}
	int maxn=0;
	for(rint i=1;i<=5;i++)
	for(rint j=0;j<=maxw;j++) maxn=max(maxn,f[n][i][j]);
	printf("%d\n",maxn);
	return 0;
}



