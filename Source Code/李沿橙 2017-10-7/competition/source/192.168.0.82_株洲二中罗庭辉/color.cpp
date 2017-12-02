#include <bits/stdc++.h>
using namespace std;
typedef long long lol;
lol ans,n,m,a[1000000];
int read(){
	int x=0,y=1;char c=getchar();
	while(c>'9'||c<'0'){
		if(c=='-') y=-1;c=getchar();}
	while(c>='0'&&c<='9'){
		x=x*10+c-'0';c=getchar();}	
	return x*y;
}
inline void  chang(lol t,lol w){
	a[0]=a[t];a[t]=a[w];a[w]=a[0];}
inline void work(lol t,lol w,lol c){
	for(int i=t;i<=w;i++)
	if(a[i]==c) ans++;
	cout<<ans<<endl;
}	
int main(){
	freopen("color.in","r",stdin);
	freopen("color.out","w",stdout);
	n=read();m=read();	
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=m;i++){
		lol t;t=read();ans=0;
	if(t==1) {int t1,w1,c1;t1=read();w1=read();c1=read();work(t1,w1,c1);}
	else {lol t1,w1;t1=read();w1=t1+1;chang(t1,w1);}}
	return 0;
}
