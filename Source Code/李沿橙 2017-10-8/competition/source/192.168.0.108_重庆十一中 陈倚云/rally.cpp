#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=80;
int n,m,k;
int a[maxn][maxn];
int sum[maxn][maxn][maxn][maxn],sum1[maxn][maxn];
bool bl;
int main(){
	freopen("rally.in","r",stdin);
	freopen("rally.out","w",stdout);
	memset(sum,0,sizeof(sum));
	scanf("%d %d %d",&n,&m,&k);
	int tmp;
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++){
		scanf("%d",&a[i][j]);
		if(a[i][j]!=a[1][1]) bl=1;
	} 
	long long ans=0;
	if(bl==0){
		if(a[1][1]%k==0){
			for(int i=1;i<=n;i++){
				for(int j=1;j<=m;j++) ans+=(i*j);
			}
			printf("%lld\n",ans);
			return 0;
		}
		else if(k%a[1][1]==0){
			int t=k/a[1][1];
			for(int i=n;i>=1;i--){
				for(int j=m;j>=1;j--){
					if(i*j>=k) ans+=(i*j);
				}
			}
			printf("%lld\n",ans);
			return 0;
		}
		else{
			printf("0");
			return 0;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			sum1[i][j]=sum1[i][j-1]+a[i][j];
		
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			for(int x=i;x<=n;x++){
				for(int y=j;y<=m;y++){
					if(i==x && y==j) sum[i][j][x][y]=a[i][j];
					else if(i==x) sum[i][j][x][y]=sum1[i][y]-sum1[i][j-1];
					else sum[i][j][x][y]=sum[i][j][x-1][y]+sum1[x][y]-sum1[x][j-1];
				
					if(sum[i][j][x][y]%k==0){
					
						ans++;
					} 
				}
			}
		}
	}

	printf("%lld",ans);
	return 0;
}
