#include<cstdio>
#define MODS 1000000007
using namespace std;
int pow(int times,long long base){
    int ret=1;
    while(times){
        if(times&1) ret=(ret*base)%MODS;
        base=(base*base)%MODS;
        times>>=1;
    }
    return ret;
}
int main(){
	freopen("photo.in","r",stdin),freopen("photo.out","w",stdout);
    int n,m,k;
    scanf("%d%d%d",&n,&m,&k);
    printf("%d",(1LL*n*m*k)%MODS);
    fclose(stdin),fclose(stdout);
    return 0;
}
