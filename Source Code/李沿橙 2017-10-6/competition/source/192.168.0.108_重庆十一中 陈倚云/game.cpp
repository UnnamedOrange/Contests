#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
#define lson
using namespace std;
const int p=1e9+7;
int n,m;
int sz[101];
long long quick_mod(long long a,long long b) {
	long long ans=1;
	a%=p;
	while(b) {
		if(b&1) {
			ans=ans*a%p;
			b--;
		}
		b>>=1;
		a=a*a%p;
	}
	return ans;
}
long long C(long long n,long long m) {
	if(m>n) return 0;
	long long ans=1;
	for(int i=1; i<=m; i++) {
		long long a=(n+i-m)%p;
		long long b=i%p;
		ans=ans*(a*quick_mod(b,p-2)%p)%p;
	}
}
long long lucas(long long n,long long m) {
	if(m==0) return 1;
	return C(n%p,m%p)*lucas(n/p,m/p)%p;
}
int main() {
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	scanf("%d %d",&n,&m);
	for(int i=1; i<=n; i++) scanf("%d",&sz[i]);
	while(m--) {
		int t,a,b,c,k;
		scanf("%d",&t);
		if(t==1) {
			
			cin >>a >> b >> c; 
			 
			for(int i=a; i<=b; i++) sz[i]=sz[i]+c;
			
		} else if(t==2) {
		
			scanf("%d %d",&a,&b);
			for(int i=a; i<=b; i++) sz[i]=(-1)*sz[i];
			
		} else if(t==3) {
			scanf("%d %d %d",&a,&b,&k);
			long long sum;
			if(k==1){
				sum=0;
				for(int i=a;i<=b;i++) sum+=sz[i];
			}
			else{
				sum=1;
				for(int i=a;i<=b;i++) sum=sum*sz[i];
			}
			if(sum<0) sum+=p;
			printf("%d\n",sum);
			
		}
		
	}

	return 0;
}
