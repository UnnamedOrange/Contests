#include<cstdio>
#include<cctype>
#define MAXN 405
#define MAXK 1000005
using namespace std;

inline char get_char(){
    static char buf[1000001],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
}
inline int read(){
    int num=0;
    char c;
    while(isspace(c=get_char()));
    while(num=num*10+c-48,isdigit(c=get_char()));
    return num;
}

int sum[MAXN][MAXN],num[MAXN][MAXN],cnt1[MAXK],cnt2[MAXK];

int main(){
    freopen("rally.in","r",stdin),freopen("rally.out","w",stdout);
    int n=read(),m=read(),k=read();
    long long ans=0;
    if(k==1){
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                ans+=i*j;
    } else {
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                sum[i][j]=(sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+(num[i][j]=read()%k))%k;
                cnt1[sum[i][j]]++,cnt2[sum[i][j]-num[i][j]]++;
            }
        }
        for(int i=0;i<k;i++) ans+=cnt1[i]*cnt2[k-i];
    }
    printf("%lld",ans);
    fclose(stdin),fclose(stdout);
    return 0;
}