#include<cstdio>
#include<cctype>
#include<algorithm>
#define MAXN 100005
using namespace std;
const double eps=-(1e-6);
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
int n,m;
int x[MAXN],y[MAXN];
double k[MAXN];
int search(int px,int py){
    int l=0,r=n,mid;
    double cy;
    while(l<r){
        mid=(l+r)>>1;
        cy=(double)(k[mid]*(double)px+y[mid]);
        if((double)(py-cy)>eps) l=mid+1;
        else r=mid-1;
    }
    if(r==1){
    	cy=(double)(k[1]*(double)px+y[1]);
    	return (double)(py-cy)>=eps;
	}
    return r;
}
int main(){
	freopen("geometry.in","r",stdin),freopen("geometry.out","w",stdout);
    n=read();
    for(int i=1;i<=n;i++) x[i]=read();
    sort(x+1,x+n+1);
    for(int i=1;i<=n;i++) y[i]=read();
    sort(y+1,y+n+1);
    for(int i=1;i<=n;i++) k[i]=(double)(-(double)y[i]/x[i]);
    m=read();
    for(int i=1;i<=m;i++){
        int px=read(),py=read();
        printf("%d\n",search(px,py));
    }
    fclose(stdin),fclose(stdout);
    return 0;
}
