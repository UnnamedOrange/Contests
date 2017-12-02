#include<cstdio>
#include<cctype>
#include<cstring>
#define MAXN 1000005
using namespace std;
char buf[20000001],*p1=buf;
inline char get_char(){
	return (*p1!=-1)?(*p1++):EOF;
}
inline int read(){
	int num=0;
	char c;
	while(isspace(c=get_char()));
	if(c==EOF) return -1;
	while(num=num*10+c-48,isdigit(c=get_char()));
	return num;
}
inline char get_ch(){
	char c;
	while(!isdigit(c=get_char()));
	return c;
}
char s[MAXN];
int main(){
	freopen("trans.in","r",stdin),freopen("trans.out","w",stdout);
	int n,k;
	memset(buf,-1,sizeof(buf));
	fread(buf,1,20000000,stdin);
	while((n=read())!=-1){
		k=read();
		for(register int i=1;i<=n;i++) s[i]=get_ch();
		for(int i=1;k&&i<=n;i++){
			if(s[i]=='2'&&s[i+1]=='3'){
				if(i&1){
					if(k) s[i+1]='2';
					break;
				} else s[i]='3',k--;
			}
		}
		for(int j=1;j<=n;j++) putchar(s[j]);
		putchar('\n');
	}
	fclose(stdin),fclose(stdout);
	return 0;
}
