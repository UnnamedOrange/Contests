#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int n,m,a[100000];
int main(){
	freopen("color","r",stdin);
	freopen("color","w",stdout);
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	while(m--){
		int t;
		scanf("%d",&t);
		if(t==1){
			int l,r,c;
			long long ans=0;
			scanf("%d %d %d",&l,&r,&c);
			for(int i=l;i<=r;i++){
				if(a[i]==c) ans++;
			}
			printf("%lld\n",ans);
		}
		else{
			int x;
			scanf("%d",&x);
			int c=a[x];
			a[x]=a[x+1];
			a[x+1]=c;
		}
	}
	return 0;
}
