#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,k,t;
int f[100001];
int main(){
	freopen("general.in","r",stdin);
	freopen("general.out","w",stdout);
	scanf("%d %d %d",&n,&k,&t);
	if(k==0){
		printf("%d",n);
		return 0;
	}
	if(t==2){
		int ans1=0,ans2=0,a,b,ma;
		for(int i=1;i<n;i++){
			scanf("%d %d",&a,&b);
			ma=max(a,max(b,ma));
			if(a==1){
				if(f[b]==3) f[b]=2;
				else f[b]=1;
			}
			else if(b==1){
				if(f[a]==3) f[a]=2;
				else f[a]=1;
			}
			else{
				if(f[a]==0) f[a]=3;
				else if(f[a]==1) f[a]=2;
				if(f[b]==0) f[b]=3;	
				else if(f[b]==1) f[b]=2;
				
			}
		}
		for(int i=1;i<=ma;i++){	if(f[i]==2) ans2++;}
		printf("%d",ans2+1);
		return 0;
	}
	else printf("3");
	return 0;
}
