#include<cstdio>
#include<cctype>
#include<cstring>
#define MAXN 1005
#define INF 214748364
using namespace std;
inline char get_char(){
    static char buf[100001],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
inline int read(){
    int num=0;
    char c;
    while(isspace(c=getchar()));
    while(num=num*10+c-48,isdigit(c=getchar()));
    return num;
}
inline int max(int a,int b){
    int c=(a-b)>>31;
    return (a&~c)|(b&c);
}
inline int min(int a,int b){
    int c=(a-b)>>31;
    return (a&c)|(b&~c);
}
// int dp[25][MAXN],g[25][MAXN];
int need[25],man[25],n,m,ans;
void dfs(int depth,int peo){
    if(need[depth-1]>0||peo>ans) return ;
    if(depth==25){
        if(peo<ans) ans=peo;
        return ;
    }
    dfs(depth+1,peo);
    for(int i=1;i<=man[depth];i++){
        bool flag=false;
        for(int j=min(depth+7,24);j>=depth;j--){
            if(need[j]>0) flag=true;
            need[j]-=i;
        }
        if(flag) dfs(depth+1,peo+i);
        for(int j=min(depth+7,24);j>=depth;j--) need[j]+=i;
    }
    // for(int i=pos+1;i<=24;i++){
        // for(int j=1;j<=man[i];j++){
            // for(int k=pos;k<=)
        // }
    // }
}
int main(){
	freopen("cashier.in","r",stdin),freopen("cashier.out","w",stdout);
    int T=read();
    while(T--){
        for(int i=1;i<=24;i++) need[i]=read();
        for(int i=1;i<=24;i++) man[i]=read();
        ans=INF;
        dfs(1,0);
        printf("%d\n",ans==INF?-1:ans);
    }
    fclose(stdin),fclose(stdout);
    return 0;
}
/*int main(){
    int T=read();
    while(T--){
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=24;i++) need[i]=read();
        for(int i=1;i<=24;i++) g[i][0]=man[i]=read();
        for(int i=1;i<n;i++){
            for(int j=0;j<=need[i];j++){
                for(int k=max(1,i-8);k<=i;k++){
                    for(int r=0;r<=j;r++){

                    }
                }
            }
        }
    }
}*/
