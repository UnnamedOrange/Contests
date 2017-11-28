#include <bits/stdc++.h>
using namespace std;

inline int read(int &r){
	int f=1,c=getchar();r=0;
	while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();};
	while(c>='0'&&c<='9')r=r*10+c-'0',c=getchar();
	return r*f;
}

const int maxn = 100005;
vector<int> g[maxn];
int d[maxn][2]; // 0 ??
bool vis[maxn];

void dp(int u,int fa) {
    if(vis[u]) return;
    vis[u] = 1;

    d[u][0] = d[u][1] = 0;
    int sum = 0;
    for(int i=0; i < (int)g[u].size(); i++) {
        int v = g[u][i];
        if(v==fa) continue;
        dp(v,u);
        d[u][1] += max(d[v][0],d[v][1]);
        sum+=d[v][0];
    }

    for(int i=0; i < (int)g[u].size(); i++) {
        int v = g[u][i];
        if(v==fa) continue;
        d[u][0] = max(d[u][0],sum-d[v][0]+d[v][1]+1);
    }

}

int T;
int N,K;

int main(){
	
    read(T);
    while(T--) {
        read(N);
        read(K);

        for(int i=0; i <= N; i++)
            g[i].clear();
        memset(vis,0,sizeof(vis));

        int u;
        for(int i=1; i < N; i++) {
            read(u);
            g[u].push_back(i+1);
            g[i+1].push_back(u);
        }

        dp(1,-1);

        int ans = max(d[1][1],d[1][0]);
        if(ans*2>=K)
            printf("%d\n",(K+1)/2);
        else
            printf("%d\n",ans+K-(ans*2));
    }
    return 0;
}
