#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=31;
int m,n;

int mul_mod(int a,int b,int mod){
    a%=mod;
    int x=1;
    while(b){
        if(b&1) x= 1ll*a*x%mod;
        a = 1ll*a*a%mod;
        b >>= 1;
    }
    return x;
}

int main(){
	freopen("math.in","r",stdin);
	freopen("math.out","w",stdout);
	 
	int T;
	cin>>T; 
    int a;
    while(cin>>a>>n){
        int maxn=(1<<n);
        if(a&1) puts("1"); 
        else{
            int ans=0;
            for(int i=2;i<=n;i+=2){
                if(mul_mod(a,i,maxn) == mul_mod(i,a,maxn))
                    ans++;
            }
            int c=(n+a-1)/a; 
            int x=(1<<n) >> c;
            int t=n>>c;
            ans+=x;
            ans-=t;
            printf("%d\n",ans);
        }
    }
    return 0;
}
