#include<cstdio>
#include<cctype>
#include<cstring>
#define MAXN 50005
#define INF 214748364
#define MODS 1000000007
using namespace std;
inline char get_char(){
    static char buf[100001],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
inline int read(){
    int num=0;
    char c,sf=1;
    while(isspace(c=getchar()));
    if(c=='-') sf=-1,c=getchar();
    while(num=num*10+c-48,isdigit(c=getchar()));
    return num*sf;
}
long long balls[MAXN],ans;
bool vis[MAXN];
int xa,xb,xk;
void dfs(int pos,int depth,long long mul){
    if(depth==xk+1){
        ans=(ans+mul)%MODS;
        return ;
    }
    for(int i=pos+1;i<=xb;i++){
        if(vis[i]) continue;
        vis[i]=true;
        dfs(i,depth+1,mul*balls[i]%MODS);
        vis[i]=false;
    }
}
int main(){
    freopen("game.in","r",stdin),freopen("game.out","w",stdout);
    int n=read(),m=read();
    for(int i=1;i<=n;i++) balls[i]=read();
    for(int i=1;i<=m;i++){
        int con=read();
        if(con==1){
            int a=read(),b=read(),c=read();
            for(int i=a;i<=b;i++) balls[i]+=c;
        }
        if(con==2){
            int a=read(),b=read();
            for(int i=a;i<=b;i++) balls[i]=(~balls[i])+1;
        }
        if(con==3){
            xa=read(),xb=read(),xk=read(),ans=0;
            if(xk==1) for(int i=xa;i<=xb;i++) ans=(ans+balls[i])%MODS;
            else dfs(xa-1,1,1);
            printf("%lld\n",ans<0?ans+MODS:ans);
        }
    }
    fclose(stdin),fclose(stdout);
    return 0;
}
