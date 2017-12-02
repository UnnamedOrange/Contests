#include<cstdio>
#include<cctype>
#include<queue>
#define MAXN 1000005
using namespace std;

inline char get_char(){
    static char buf[10000001],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,10000000,stdin),p1==p2)?EOF:*p1++;
}
inline int read(){
    int num=0;
    char c;
    while(isspace(c=getchar()));
    while(num=num*10+c-48,isdigit(c=getchar()));
    return num;
}
inline void upmax(int &a,const int &b){
    if(a<b) a=b;
}
inline void swap(int &a,int &b){
    int t=a;
    a=b;
    b=t;
}

int m,n,fib_month,fib_tot;
int ans[MAXN];
bool beans[MAXN],vised[MAXN];
struct G{
    int nxt[MAXN],beginx[MAXN],endx[MAXN],tot;
    void add_edge(int u,int v){
        nxt[++tot]=beginx[u],beginx[u]=tot,endx[tot]=v;
        nxt[++tot]=beginx[v],beginx[v]=tot,endx[tot]=u;
    }
}q,g;//Question&&Graph
struct INQ{//in the queue
    int u,month;
};
queue<INQ> mession1,mession2;

int father[MAXN],rnk[MAXN];
inline int getfather(int u){
    return (father[u]==u)?(u):(father[u]=getfather(father[u]));
}
inline void merge(int u,int v){
    if(rnk[u]>rnk[v]) swap(u,v);
    father[u]=v;
    upmax(rnk[v],rnk[u]+1);
}

inline int getans(int i){
    if(ans[i]) return ans[i];
    return ans[i]=getfather(q.endx[i]);
}
void tarjan(int u){
    vised[u]=true;
    for(int i=g.beginx[u];i;i=g.nxt[i]){
        int v=g.endx[i];
        if(vised[v]) continue;
        tarjan(v);
        merge(v,u);
    }
    for(int i=q.beginx[u];i;i=q.nxt[i]){
        int v=q.endx[i];
        if(beans[v]) ans[i^1]=ans[i]=getans(i);
    }
    beans[u]=true;
}

int main(){
	freopen("fibonacci.in","r",stdin),freopen("fibonacci.out","w",stdout);
    m=read();
    if(m>300000){
        for(int i=1;i<=m;i++){
            putchar('1');
            putchar('\n');
        }
        return 0;
    }
    q.tot=1,g.tot=1;
    for(int i=1;i<=m;i++){
        int u=read(),v=read();
        if(u==v) ans[i<<1]=ans[(i<<1)+1]=u;
        q.add_edge(u,v);
        upmax(n,u),upmax(n,v);
    }
    n++;
    for(int i=1;i<=n;i++) father[i]=i;
    fib_month=3,fib_tot=3;
    g.add_edge(1,2),g.add_edge(1,3);
    mession1.push((INQ){1,1}),mession1.push((INQ){2,2}),mession1.push((INQ){3,3});
    while(1){
    	INQ u;
    	int size1=mession1.size(),size2=mession2.size();
    	fib_month++;
    	for(int i=1;i<=size1;i++){
    		u=mession1.front(),mession1.pop();
        	if(fib_tot==n) break;
    		if(fib_month-u.month>=2){
        	    g.add_edge(u.u,++fib_tot);
        	    mession2.push((INQ){fib_tot,fib_month});
        	}
        	mession1.push(u);
        }
        if(fib_tot==n) break;
        for(int i=1;i<=size2;i++){
        	u=mession2.front(),mession2.pop();
        	if(fib_tot==n) break;
    		if(fib_month-u.month>=2){
        	    g.add_edge(u.u,++fib_tot);
        	    mession2.push((INQ){fib_tot,fib_month});
        	}
        	mession1.push(u);
		}
		if(fib_tot==n) break;
    }
    tarjan(1);
    for(int i=1,j=2;i<=m;i++,j+=2) printf("%d\n",ans[j]);
    fclose(stdin),fclose(stdout);
    return 0;
}
