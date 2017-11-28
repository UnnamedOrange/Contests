#include<bits/stdc++.h>
using namespace std;

const int MAXN = 400001;
vector< vector<int> > adj;
int cnt,low[MAXN],pre[MAXN],visit[MAXN],degree[MAXN];

void dfs(int u,int v){
    visit[u]=1;
    pre[u]=cnt++,low[u]=pre[u];
    int i,len=adj[u].size();
    for(i=0;i<len;i++){
        if(adj[u][i]==v) continue;
        if(!visit[adj[u][i]]) dfs(adj[u][i],u);
        if(low[adj[u][i]]<low[u]) low[u]=low[adj[u][i]];
    }
    visit[u]=2;
}

int main(){
	freopen("graph.in","r",stdin);
	freopen("graph.out","w",stdout);
    int i,j,u,v,n,m,len,ans;
    while(scanf("%d %d",&n,&m)!=EOF){
        adj.assign(n+1,vector<int>());
        while(m--){
            scanf("%d %d",&u,&v);
            adj[u].push_back(v),adj[v].push_back(u);
        }
        memset(visit,0,sizeof(visit));
        cnt=0,dfs(1,1);
        memset(degree,0,sizeof(degree));
        for(i=1;i<=n;i++){
            len=adj[i].size();
            for(j=0;j<len;j++)
                if(low[i]!=low[adj[i][j]])
                    degree[low[i]]++;
        }
        for(ans=i=0;i<=n;i++)
            if(degree[i]==1) ans++;
        printf("%d\n",(ans+1)/2);
    }
    return 0;
}
