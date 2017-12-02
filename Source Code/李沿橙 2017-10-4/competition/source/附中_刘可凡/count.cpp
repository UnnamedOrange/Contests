#include<cstdio>
#define MODS 998244353
using namespace std;
long long l,r,k;
inline long long qpow(long long tar){
    long long x=k,ret=1;
    while(x){
        if(x&1) ret=(ret*tar)%MODS;
        tar=(tar*tar)%MODS;
        x>>=1;
    }
    return ret;
}
int main(){
	freopen("count.in","r",stdin),freopen("count.out","w",stdout);
    scanf("%d%d%d",&l,&r,&k);
    long long ans=0;
    if(l==1) l++,ans+=qpow(2);
    for(long long i=l;i<=r;++i)
		ans=(ans+qpow(i))%MODS;
    printf("%d",ans);
    fclose(stdin),fclose(stdout);
    return 0;
}
