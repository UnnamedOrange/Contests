#include<cstdio>
const int maxn=4e2+10;

int n,m,k,ans;
int a[maxn][maxn];
int s[maxn][maxn];

int main(){
	freopen("rally.in","r",stdin);
	freopen("rally.out","w",stdout);
	
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++){
		scanf("%d",&a[i][j]);
		s[i][j]=(s[i][j-1]+a[i][j])%k;
	}
	
	int now;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			for(int ii=i;ii<=n;ii++){
				for(int jj=j;jj<=m;jj++){
					now=0;
					for(int iii=i;iii<=ii;iii++){
						now+=s[iii][jj]-s[iii][j-1];
						now=(now+k)%k;
					}
					if(!now) ans++;
				}
			}
		}
	}
	
	printf("%d\n",ans);
	
	
	
	
	
	
	return 0;
}
