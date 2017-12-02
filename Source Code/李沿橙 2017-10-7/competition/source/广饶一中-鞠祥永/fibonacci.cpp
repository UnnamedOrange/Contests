#include<cstdio>
const int maxm=3e5+30;
int m;
long long f[59]={1,1};
int main(){
	freopen("fibonacci.in","r",stdin);
	freopen("fibonacci.out","w",stdout);
	for(int i=2;i<=58;i++) f[i]=f[i-1]+f[i-2];
	scanf("%d",&m);
	long long a,b;
	while(m--){
		scanf("%lld%lld",&a,&b);
		for(int i=58;a!=b;i--){
			if(a>f[i]) a-=f[i];
			if(b>f[i]) b-=f[i];
		}
		printf("%lld\n",a);
	}
	return 0;
} 
