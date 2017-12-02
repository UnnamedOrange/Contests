#include <bits/stdc++.h>
#define inf 1000000000+7
typedef long long lol;
using namespace std;
lol n,m,a[50010],ans;
int read(){
	int x=0,y=1;char c=getchar();
	while(c>'9'||c<'0'){
		if(c=='-') y=-1;c=getchar();}
	while(c>='0'&&c<='9'){
		x=x*10+c-'0';c=getchar();}
		return x*y;	
}
void work(int t,int w,int s){
	int id=0;
	if(s==1) {id=1;
	for(int i=t;i<=w;i++) ans=(a[i]+ans)%1000000007; }
	if(s==w-t+1){ id=1;ans=1;for(int i=t;i<=w;i++)
	ans=ans*a[i]%1000000007;}
	if(id==0&&s==2) {
		for(int i=t;i<w;i++)
			for(int j=i+1;j<=w;j++)
		ans=(ans+(a[i]*a[j]))%1000000007;	
	}
	if(id==0&&s!=2) ans=0;
	if(ans<0) ans=ans+inf;
	cout<<ans<<endl;
}
int main(){
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=m;i++){
		int id;id=read();
		if(id==1) {int t,c,w;t=read();w=read();c=read();
		for(int i=t;i<=w;i++) a[i]+=c;}
		if(id==2) {
			int t,w;t=read();w=read();
			for(int i=t;i<=w;i++) a[i]=-a[i];}
		if(id==3) {ans=0;
			int t,w,s;t=read();w=read();s=read();work(t,w,s);
		}	
	}
	return 0;
}
