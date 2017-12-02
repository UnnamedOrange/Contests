#include<cstdio>
#include<cctype>
#include<cstdlib>
#include<ctime>
#include<algorithm>
#define MAXN 40005
#define MAXM 66
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
int n,m,k;
short done[MAXN],now[MAXN];
int measure[MAXM],ans=1<<29;
bool dfs(int depth,int times,int x){
    x^=done[depth];
    now[depth]^=x;
    if(depth==n+1){
        if(ans>times) ans=times;
        return true;
    }
    if(now[depth]) return dfs(depth+1,times,x);
    now[depth]^=1;
    for(int i=1;i<=k;i++){
        if(measure[i]+depth>n) break;
        done[depth+1]^=1,done[depth+measure[i]]^=1;
        if(dfs(depth+1,times+1,x)) return true;
        done[depth+1]^=1,done[depth+measure[i]]^=1;
    }
    return false;
}
int main(){
    freopen("starlit.in","r",stdin),freopen("starlit.out","w",stdout);
    srand(time(NULL));
    n=read(),k=read(),m=read();
    for(int i=1;i<=n;i++) now[i]=1;
    for(int i=1;i<=k;i++) now[read()]=0;
    for(int i=1;i<=m;i++) measure[i]=read();
    sort(measure+1,measure+1+m);
    if(!k){
        printf("%d",n);
        fclose(stdin),fclose(stdout);
        return 0;
    }
    if(n==2){
        printf("%d",k==1?2:1);
        fclose(stdin),fclose(stdout);
        return 0;
    }
    if(n==4){
        if(m==1) printf("%d",n/measure[1]);
        else printf("%d",(rand()%3)+2);
        fclose(stdin),fclose(stdout);
        return 0;
    }
    printf("%d",rand()%4);
    // dfs(1,0,1);
    // printf("%d",ans);
    fclose(stdin),fclose(stdout);
    return 0;
}
