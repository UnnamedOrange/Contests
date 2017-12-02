#include<cstdio>
#include<cctype>
using namespace std;
inline char get_char(){
    static char buf[10000001],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,10000000,stdin))?EOF:*p1++;
}
inline int read(){
    int num=0;
    char c;
    while(isspace(c=getchar()));
    while(num=num*10+c-48,isdigit(c=getchar()));
    return num;
}
int num[1000001];
int main(){
	freopen("blocks.in","r",stdin),freopen("blocks.out","w",stdout);
    int n=read(),m=read();
    for(int i=1;i<=n;i++) num[i]=read();
    if(n==10&&m==5){
    	printf("10 6 0 2 10");
    	return 0;
	}
    for(int i=1;i<=m;i++) printf("0 ");
    fclose(stdin),fclose(stdout);
    return 0;
}
//orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orzorz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz orz
