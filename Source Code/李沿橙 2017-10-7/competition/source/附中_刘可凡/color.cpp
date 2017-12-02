#include<cstdio>
#include<cctype>
#include<algorithm>
#define MAXN 50005
#define MAXM 300005
#define MAXC 1005
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
inline void Swap(int &a,int &b){
    int t=a;
    a=b;
    b=t;
}

int sum[MAXN][MAXC],nav[MAXM][25];
int num[MAXM],c;

int main(){
	freopen("color.in","r",stdin),freopen("color.out","w",stdout);
    int n=read(),m=read();
    for(int i=1;i<=n;i++){
        num[i]=read();
        upmax(c,num[i]);
    }
    if(c<20){
        for(int i=1;i<=n;i++)
            for(int j=1;j<=c;j++)
                nav[i][j]=nav[i-1][j]+(bool)(num[i]==j);
        for(int i=1;i<=m;i++){
            int con=read();
            if(con==1){
                int l=read(),r=read(),c=read();
                printf("%d\n",nav[r][c]-nav[l-1][c]);
            } else {
                int x=read();
                nav[x][num[x]]--,nav[x][num[x+1]]++;
                Swap(num[x],num[x+1]);
            }
        }
    } else{ 
        for(int i=1;i<=n;i++)
            for(int j=1;j<=c;j++)
                sum[i][j]=sum[i-1][j]+(bool)(num[i]==j);
        for(int i=1;i<=m;i++){
            int con=read();
            if(con==1){
                int l=read(),r=read(),c=read();
                printf("%d\n",sum[r][c]-sum[l-1][c]);
            } else {
                int x=read();
                sum[x][num[x]]--,sum[x][num[x+1]]++;
                Swap(num[x],num[x+1]);
            }
        }
    }
    fclose(stdin),fclose(stdout);
    return 0;
}
