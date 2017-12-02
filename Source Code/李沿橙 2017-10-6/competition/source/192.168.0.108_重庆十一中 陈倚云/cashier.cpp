#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
using namespace std;
int T,a[24],b[24],t[24],ans;

int main(){
	freopen("cashier.in","r",stdin);
	freopen("cashier.out","w",stdout);
	scanf("%d",&T);
	while(T--){
		memset(t,0,sizeof(t));
		for(int i=0;i<24;i++) scanf("%d",&a[i]);
		for(int i=0;i<24;i++) scanf("%d",&b[i]);
		ans=-1;
		for(int i=0;i<24;i++){
			if(a[i]>t[i]){
				int j=i;
				while(a[i]>t[i] ){
					if(j+7<i) break;
					if(b[j]+t[i]>=a[i]){
						int add=a[i]-t[i];
						b[j]=b[j]-add;
						for(int z=j;z<=min(23,j+7);z++) t[z]+=add;
						ans+=add; 
						break;
					}
					if(j==0){break;}
					else{
						int add=b[j];
						b[j]=0;
						for(int z=j;z<=min(23,j+7);z++) t[z]+=add;
						ans+=add; 
						j--;
					}
				}
			}
		}
		if(ans==-1) printf("%d\n",ans);
		else 	printf("%d\n",ans+1);
	}
	return 0;
}
