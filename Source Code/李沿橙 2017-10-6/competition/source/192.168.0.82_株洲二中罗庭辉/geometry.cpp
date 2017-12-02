#include <bits/stdc++.h>
#define inf 100010
typedef long long lol;
using namespace std;
lol n,m,x[inf],y[inf],ans;
struct cmp{int x;int y;}e[inf];
int read(){
	int x=0,y=1;char c=getchar();
	while(c>'9'||c<'0'){
		if(c=='-') y=-1;c=getchar();}
	while(c>='0'&&c<='9'){
		x=x*10+c-'0';c=getchar();}
		return x*y;	
}
void jugdes(int x,int y){
	int s=1;
	while(s<=n){
	int  x1=e[s].x,y1=e[s].y;s++;
	if(-x*(-y1/x1)-y1+y>=0) ans++; 	
	else break;}
}
int main(){
	freopen("geometry.in","r",stdin);
	freopen("geometry.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++) x[i]=read();
	for(int i=1;i<=n;i++) y[i]=read();
	sort(x+1,x+1+n);sort(y+1,y+1+n);
	for(int i=1;i<=n;i++)
	{e[i].x=x[i];e[i].y=y[i];}
	m=read();
	for(int i=1;i<=m;i++) {
	int x1,y1;ans=0;
	x1=read();y1=read();
	jugdes(x1,y1);
	cout<<ans<<endl;}
	return 0;
}
