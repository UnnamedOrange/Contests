#include<iostream>
#include<cstdio>
using namespace std;
int l,r,k;
long long ans;
int po(int a,int n,int m){
	if(n==0) return 1;
	long long p=po(a,n/2,m);
	return p*p%m*(n%2?a:1)%m;
}
int main(){
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	scanf("%d %d %d",&l,&r,&k);
	for(int i=l;i<=r;i++){
		ans+=po(i,k,998244353);
	}
	printf("%lld",ans%998244353);
	return 0;
}
