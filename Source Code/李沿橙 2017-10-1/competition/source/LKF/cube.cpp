#include<cstdio>
#include<cctype>
#define MAXN 30010
int father[MAXN],son[MAXN],depth[MAXN],bot[MAXN],top[MAXN];
inline char get_char(){
	static char buf[500001],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,500000,stdin),p1==p2)?EOF:*p1++;
}
inline int read(){
	int num=0;
	char c;
	while(isspace(c=get_char()));
	while(num=num*10+c-48,isdigit(c=get_char()));
	return num;
}
inline char get_ch(){
	char c;
	while(!isalpha(c=get_char()));
	return c;
}
int main(){
	freopen("cube.in","r",stdin);
	freopen("cube.out","w",stdout);
	int p=read();
	for(int i=1;i<=MAXN;i++){
		son[i]=i;
		bot[i]=i;
		top[i]=i;
		father[i]=i;
		depth[i]=1;
	}
	for(int k=1;k<=p;k++){
		char c=get_ch();
		if(c=='M'){
			int x=read(),y=read();
			if(top[x]==top[y]) continue;
			son[bot[y]]=top[x];
			for(int i=top[x];;i=son[i]){
				top[i]=top[y];
				depth[i]+=depth[bot[y]];
				if(i==bot[x]) break;
			}
			father[top[x]]=bot[y];
			for(int i=top[y];;i=son[i]){
				bot[i]=bot[x];
				if(i==bot[y]) break;
			}
		} else printf("%d\n",depth[read()]-1);
	}
	fclose(stdin),fclose(stdout);
	return 0;
}
