#include<cstdio>
#include<cctype>
#define MAXN 1000005
using namespace std;
inline char get_char(){
	static char buf[50000001],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,50000000,stdin),p1==p2)?EOF:*p1++;
}
inline int read(){
	int num=0;
	char c;
	while(isspace(c=get_char()));
	while(num=num*10+c-48,isdigit(c=get_char()));
	return num;
}
int n,k;
int main(){
	freopen("wave.in","r",stdin),freopen("wave.out","w",stdout);
	n=read(),k=read();
	int ans=0,now=1<<30,last=now,lc=last;
	bool state=true;//true is smaller
	for(int i=1,num;i<=n;i++){
		num=read();
		if(state){
			if(last<num){
				ans++;
				lc=now;
				state=false;
			} else if(lc-num>=k&&now>num) now=num;
		} else {
			if(last>num){
				ans++;
				lc=now;
				state=true;
			} else if(num-lc>=k&&now<num) now=num;
		}
		last=num;
	}
	if((state&&lc-last>=k)||(!state&&last-lc>=k)) ans++;
	printf("%d",ans);
	fclose(stdin),fclose(stdout);
	return 0;
}
