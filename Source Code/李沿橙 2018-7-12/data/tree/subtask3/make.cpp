#include <bits/stdc++.h>
#define ysf (998244353)
#define inf (1LL<<60)
#define N (1000005)
#define ll long long

using namespace std;

int tong[N],bel[N],n,m,k,T,O;

inline int gi(){
    int x=0,q=1; char ch=getchar();
    while (ch<'0' || ch>'9') q=ch=='-'?-1:1,ch=getchar();
    while (ch>='0' && ch<='9') x=x*10+ch-'0',ch=getchar();
    return q*x;
}

inline int Rand(){
    int res=rand()%1000000001;
    return rand()&1 ? res : -res;
}

int main(){
    srand((unsigned long long)new char);
    freopen("f.in","w",stdout);
    n=99900+rand()%101;
    m=99900+rand()%101;
    k=rand()%n+1;
    T=0,O=3;
    printf("%d %d %d %d %d\n",n,m,k,T,O);
    for (int i=1;i<=n;++i) bel[i]=rand()%k+1,printf("%d %d\n",Rand(),bel[i]),++tong[bel[i]];
    for (int i=2;i<=n;++i) printf("%d %d\n",1,i);
	//printf("%d %d\n",i,rand()%(i-1)+1);
    while (m--){
	int op=rand()%2+1;
	if (op==1){
	    int x=rand()%n+1;
	    printf("1 %d %d\n",x,Rand());
	} else{
	    int o=rand()%k+1;
	    while (!tong[o]) o=rand()%k+1;
	    printf("3 %d\n",o);
	}
    }
    return 0;
}
