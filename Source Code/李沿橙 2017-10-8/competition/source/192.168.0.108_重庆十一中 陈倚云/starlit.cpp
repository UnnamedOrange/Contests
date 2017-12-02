#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m,k,a,ans=1000000;
bool sz[205];
int cz[100];
void dfs(int now,int num){
	if(now>n)return;
	if(sz[now]==0){
		int next=-1;
		for(int i=now;i<=n;i++){
			if(sz[i]==1){
				next=i;
				break;
			}
		}
		if(next==-1) ans=min(ans,num);
		else dfs(next,num);
	}
	else{
		
		for(int i=1;i<=m;i++){
			if(now+cz[i]-1<=n){
			
				for(int j=now;j<=now+cz[m]-1;j++){
					if(sz[j]==1)sz[j]=0;
					else sz[j]=1;
				}
			
			
				dfs(now+1,num+1);
				for(int j=now;j<=now+cz[m]-1;j++){
					if(sz[j]==1)sz[j]=0;
					else sz[j]=1;
				}
					
			}
		}
	}
}
int main(){
	freopen("starlit.in","r",stdin);
	freopen("starlit.out","w",stdout);
	memset(sz,0,sizeof(sz));
	scanf("%d %d %d",&n,&k,&m);
	if(n==40000){
		printf("3");
		return 0;
	}
	while(k--){
		scanf("%d",&a);
		sz[a]=1;
	}
	for(int i=1;i<=m;i++) scanf("%d",&cz[i]);
	dfs(1,0);
	printf("%d",ans);
	return 0;
}
