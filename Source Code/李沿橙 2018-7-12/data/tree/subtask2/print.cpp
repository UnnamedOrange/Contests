#include <bits/stdc++.h>
#define ysf (998244353)
#define inf (1LL<<60)
#define N (1000005)
#define ll long long

using namespace std;

int st[N],top,ans;

inline int gi(){
    int x=0,q=1; char ch=getchar();
    while (ch<'0' || ch>'9') q=ch=='-'?-1:1,ch=getchar();
    while (ch>='0' && ch<='9') x=x*10+ch-'0',ch=getchar();
    return q*x;
}

int main(){
    srand((unsigned long long)new char);
    freopen("f.out","r",stdin); ll x;
	while (scanf("%lld",&x)!=EOF) st[++top]=(x%ysf+ysf)%ysf;
	fclose(stdin);
	freopen("f.in","r",stdin);
	freopen("10.in","w",stdout);
	int n=gi(),m=gi(),k=gi(),T=gi(),O=gi(); T=1;
	printf("%d %d %d %d %d\n",n,m,k,T,O),top=0;
	for (int i=1,u,v;i<=n;++i)
		u=gi(),v=gi(),printf("%d %d\n",u,v);
	for (int i=1,u,v;i<n;++i)
		u=gi(),v=gi(),printf("%d %d\n",u,v);
	while (m--){
		int op=gi(); printf("%d ",op);
		if (op<=2){
			int x=gi()^ans,v=gi()^ans;
			printf("%d %d\n",x,v);
		} else{
			printf("%d\n",gi()^ans);
			if (T) ans=st[++top];
		}
	}
    return 0;
}
