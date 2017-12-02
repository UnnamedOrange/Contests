#include<cstdio>
const int maxn=210;
int n,ans;
int map[maxn][5];
bool v[maxn][5];
int main(){
	freopen("snakevsblock.in","r",stdout);
	freopen("snakevsblock.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		for(int j=0;j<5;j++){
			scanf("%d",&map[i][j]);
			if(map[i][j]<0){
				map[i][j]*=-1;
				ans+=map[i][j];
				v[i][j]=1;
			}
			
		}
	}
	
	
	
	
	printf("%d\n",ans);
	return 0;
}
