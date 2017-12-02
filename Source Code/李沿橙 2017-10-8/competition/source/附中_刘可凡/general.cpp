#include<cstdio>
#include<cctype>
#define MAXN 100005
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
inline int min(int a,int b){
    int c=(a-b)>>31;
    return (a&c)|(b&~c);
}

int n,k,t,dp[MAXN][4];//O2防炸
int nxt[MAXN],beginx[MAXN],endx[MAXN];

int dfs(int a,int b,int father){
    if(dp[a][b]>=0) return dp[a][b];
    dp[a][b]=0;
    if(b==2){
        for(int i=beginx[a],u=endx[i];i;i=nxt[i],u=endx[i])
            if((u=endx[i])!=father)
                dp[a][2]+=dfs(u,0,a);
        return dp[a][2];
    }
    if(b==1){
        for(int i=beginx[a],u=endx[i];i;i=nxt[i],u=endx[i])
            if((u=endx[i])!=father)
                dp[a][1]+=min(min(dfs(u,0,a),dfs(u,1,a)),dfs(u,2,a));
        return ++dp[a][1];
    }
    dp[a][0]=MAXN;
    int sum=0;
    for(int i=beginx[a],u=endx[i];i;i=nxt[i])
        if((u=endx[i])!=father)
            sum+=min(dfs(u,0,a),dfs(u,1,a));
    for(int i=beginx[a],u=endx[i];i;i=nxt[i])
        if((u=endx[i])!=father)
            dp[a][0]=min(dp[a][0],dfs(u,1,a)+sum-min(dfs(u,0,a),dfs(u,1,a)));
    return dp[a][0]; 
}

int main(){
    freopen("general.in","r",stdin),freopen("general.out","w",stdout);
    n=read(),k=read(),t=read();
    if(!k){
        printf("%d",n);
        return 0;
    }//k==1 is ok
    for(int i=1;i<n;i++){
        int u=read(),v=read();
        dp[i][0]=dp[i][1]=dp[i][2]=-1;
        nxt[i]=beginx[u],beginx[u]=i,endx[i]=v;
        nxt[i+n]=beginx[v],beginx[v]=i+n,endx[i+n]=u;
    }
    dp[n][0]=dp[n][1]=dp[n][2]=-1;
    printf("%d",min(min(dfs(1,0,0),dfs(1,1,0)),dfs(1,2,0)+1));
    fclose(stdin),fclose(stdout);
    return 0;
}