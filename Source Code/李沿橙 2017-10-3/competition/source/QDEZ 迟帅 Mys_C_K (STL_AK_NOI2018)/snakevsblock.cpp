#include<iostream>
#include<cstdio>
#include<cstring>
#define Max(x,y) x=(((x)>(y))?(x):(y))
#define N 210
#define inf -1
#define LEN 10010
#define debug(x) cerr<<#x<<"="<<x
#define sp <<" "
#define ln <<endl
using namespace std;
int dp[N][LEN][6],g[10];
int a[N][6],f[10],L[10];
bool is_wall[N][6];
int main()
{
	freopen("snakevsblock.in","r",stdin);
	freopen("snakevsblock.out","w",stdout);
	int n,m=5;scanf("%d",&n);
	int MaxLen=4;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			scanf("%d",&a[i][j]);
			if(a[i][j]>0) MaxLen+=a[i][j];
		}
	int K;scanf("%d",&K);
	while(K--)
	{
		int x,y;scanf("%d%d",&x,&y);
		is_wall[x][y]=true;
	}
//	debug(MaxLen)ln;
	for(int i=0;i<=MaxLen;i++)
		for(int j=1;j<=m;j++)
			dp[0][i][j]=inf;
	dp[0][4][3]=0;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<=MaxLen;j++)
			for(int k=1;k<=5;k++)
				dp[i+1][j][k]=inf;
		for(int j=0;j<=MaxLen;j++)
		{
			for(int k=1;k<=m;k++)
			{
				int x,y,nl=j;f[k-1]=dp[i][j][k];
				if(dp[i][j][k]<0) continue;
				int mx=k-1;
				for(int r=k;r<=m;r++)
				{
					x=a[i+1][r];f[r]=f[r-1];L[r]=(nl+=x);
					if(r>k&&is_wall[i+1][r-1]) break;
					if(x>0&&nl>MaxLen) break;
					if(x<0)
						if(nl>=0) f[r]=f[r-1]-x;
						else break;
					mx=r;
//					if(!i) debug(r)sp,debug(x)sp,debug(L[r])sp,debug(f[r])ln;
				}
				for(int r=k;r<=mx;r++)
				{
					nl=L[r];
					if(r>k&&is_wall[i+1][r-1]) break;
					for(int l=r;l;l--)
					{
						if(l>=k) Max(dp[i+1][L[r]][l],f[r]),g[l]=f[r];
						else{
							x=a[i+1][l];nl+=x;g[l]=g[l+1];
							if(is_wall[i+1][l]) break;
							if(x>0&&nl>MaxLen) break;
							if(x<0)
								if(nl>=0) g[l]=g[l+1]-x;
								else break;
							Max(dp[i+1][nl][l],g[l]);
						}
//						if(!i) debug(r)sp,debug(l)sp,debug(nl)sp,debug(g[l])ln;
						for(int p=l;p<=r;p++)
							Max(dp[i+1][nl][p],g[l]);
					}
				}
				f[k+1]=dp[i][j][k];nl=j;mx=k+1;
				for(int l=k;l;l--)
				{
					x=a[i+1][l],f[l]=f[l+1];L[l]=(nl+=x);
					if(l<k&&is_wall[i+1][l]) break;
					if(x>0&&nl>MaxLen) break;
					if(x<0)
						if(nl>=0) f[l]=f[l+1]-x;
						else break;
					mx=l;
				}
				for(int l=k;l>=mx;l--)
				{
					int nl=L[l];
					if(l<k&&is_wall[i+1][l]) break;
					for(int r=l;r<=m;r++)
					{
						if(r<=k) Max(dp[i+1][L[l]][r],f[l]),g[r]=f[l];
						else{
							x=a[i+1][r];nl+=x;g[r]=g[r-1];
							if(is_wall[i+1][r-1]) break;
							if(x>0&&nl>MaxLen) break;
							if(x<0)
								if(nl>=0) g[r]=g[r-1]-x;
								else break;
							Max(dp[i+1][nl][r],g[r]);
						}
						for(int p=r;p>=l;p--)
							Max(dp[i+1][nl][p],g[r]);
					}
				}
			}
			int k=3;
			if(dp[i][j][k]<0||a[i+1][3]) continue;
			if(a[i+1][1]<0&&a[i+1][2]>0&&a[i+1][4]<0&&a[i+1][5]>0)
			{
				int nl=j+a[i+1][2],nf=dp[i][j][k];
				if(nl<-a[i+1][4]||nl>MaxLen) continue;
				nf-=a[i+1][4];nl+=a[i+1][4]+a[i+1][5];
				if(nl<-a[i+1][1]||nl>MaxLen) continue;
				nf-=a[i+1][1],nl+=a[i+1][1];
				for(int p=1;p<=m;p++)
					Max(dp[i+1][nl][p],nf);
			}
			if(a[i+1][1]>0&&a[i+1][2]<0&&a[i+1][4]>0&&a[i+1][5]<0)
			{
				int nl=j+a[i+1][4],nf=dp[i][j][k];
				if(nl<-a[i+1][2]||nl>MaxLen) continue;
				nf-=a[i+1][2];nl+=a[i+1][2]+a[i+1][1];
				if(nl<-a[i+1][5]||nl>MaxLen) continue;
				nf-=a[i+1][5],nl+=a[i+1][5];
				for(int p=1;p<=m;p++)
					Max(dp[i+1][nl][p],nf);
			}
		}
	}
//	for(int i=1;i<=n;i++,cout ln)
//		for(int j=1;j<=m;j++)
//		{
//			int ans=0;
//			for(int k=0;k<=MaxLen;k++)
//				Max(ans,dp[i][k][j]);
//			cout<<ans sp;
//		}
//	for(int i=1;i<=n;i++)
//		for(int j=1;j<=5;j++)
//			for(int k=0;k<=MaxLen;k++)
//				debug(i)sp,debug(j)sp,debug(k)sp,debug(dp[i][k][j])ln;
	int ans=0;
	for(int i=1;i<=n;i++)
		for(int j=0;j<=MaxLen;j++)
			for(int k=1;k<=m;k++)
				Max(ans,dp[n][j][k]);
	printf("%d\n",ans);return 0;
}
