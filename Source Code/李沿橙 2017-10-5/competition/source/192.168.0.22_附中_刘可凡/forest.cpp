#include<cstdio>
#include<cctype>
#include<cstring>
#define MAXN 10005
#define MODS 1000000007
using namespace std;
inline char get_char(){
    static char buf[1000001],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
}
inline int read(){
    int num=0;
    char c;
    while(isspace(c=getchar()));
    while(num=num*10+c-48,isdigit(c=getchar()));
    return num;
}
int n,tot=1,maxa;
int nxt[MAXN],beginx[MAXN],endx[MAXN],q[MAXN];
bool forbit[MAXN],vis[MAXN];
inline int max(int a,int b){
    int c=(a-b)>>31;
    return (a&~c)|(b&c);
}
int dfs(int u,int lst){
    int max1=0,max2=0,tem1;
    vis[u]=true;
    for(int i=beginx[u];i;i=nxt[i]){
        if(forbit[i]) continue;
        int v=endx[i];
        if(v==lst) continue;
        if(max1<(tem1=dfs(v,u))) max2=max1,max1=tem1;
        else if(max2<tem1) max2=tem1;
    }
    maxa=max(maxa,max1+max2+q[u]);
    return q[u]+max1;
}
int main(){
	freopen("forest.in","r",stdin),freopen("forest.out","w",stdout);
    n=read();
    for(int i=1;i<=n;i++) q[i]=read();
    for(int i=1;i<n;i++){
        int u=read(),v=read();
        nxt[++tot]=beginx[u],beginx[u]=tot,endx[tot]=v;
        nxt[++tot]=beginx[v],beginx[v]=tot,endx[tot]=u;
    }
    dfs(1,0);
    printf("%d\n",maxa%MODS);
    for(int i=1;i<n;i++){
        long long ans=1;
        maxa=0;
        int x=(read())<<1;
        forbit[x]=forbit[x^1]=true;
        memset(vis,false,sizeof(vis));
        for(int i=1;i<=n;i++)
            if(!vis[i])
                dfs(i,0),ans=(ans*maxa)%MODS;
        printf("%lld\n",ans);
    }
    fclose(stdin),fclose(stdout);
    return 0;
}
