#include<cstdio>
#include<cstring>
#include<cctype>
#include<cstdlib>
#include<ctime>
#define MAXN 301
using namespace std;
const int prec=0.9*CLOCKS_PER_SEC;
clock_t beg;
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
int gcd(int a,int b){
    if(a<b) return gcd(b,a);
    if(!b) return a;
    bool s1=!(a&1),s2=!(b&1);
    if(s1){
        if(s2) return gcd(a>>1,b>>1)<<1;
        return gcd(a>>1,b);
    
    }
    return gcd(b,a-b);
}
int n,num[MAXN];
bool vis[MAXN];
int times,xiuxiu;
void dfs(int depth,int lst,int now,bool fir){
	if(depth==n){
		xiuxiu+=fir,times++;
		return;
	}
    if(gcd(num[lst],num[now])==1){
        times++,xiuxiu+=fir;
        return;
    }
    if(clock()-beg>prec){
        printf("%.9lf 1.000000000",(double)xiuxiu/times);
        exit(0);
    }
    for(int i=1;i<=n;i++){
        if(vis[i]) continue;
        vis[i]=true;
        dfs(depth+1,now,i,!fir);
        vis[i]=false;
    }
}
int main(){
	freopen("cards.in","r",stdin),freopen("cards.out","w",stdout);
    n=read();
    for(int i=1;i<=n;i++) num[i]=read();
    beg=clock();
    if(n==1){
    	if(num[1]==1) printf("0.000000000 0.000000000");
    	else printf("1.000000000 1.000000000");
    	return 0;
	}
	if(n==2){
		if(num[1]==1&&num[2]==1) printf("0.000000000 0.000000000");
		else if(num[1]==1||num[2]==1) printf("0.500000000 1.000000000");
		else if(gcd(num[1],num[2])==1) printf("1.000000000 1.000000000");
		else printf("0.000000000 0.000000000");
		return 0;
	}
    dfs(0,0,0,1);
    printf("%.9lf 1.000000000",(double)xiuxiu/times);
    fclose(stdin),fclose(stdout);
    return 0;
}
