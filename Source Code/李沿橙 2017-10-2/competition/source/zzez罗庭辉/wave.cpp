#include <bits/stdc++.h>
using namespace std;
typedef long long lol;	
int read(){
	int x=0,y=1;char c=getchar();
	while(c>'9'||c<'0') {if(c=='-') y=1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*y;
}
lol n,k,a[2000001],maxs;
lol judge(int x,int y){
	lol t=abs(a[x]-a[y]);
	if(t<k) {t=0;return t;}
	lol t1,t2;
	t1=abs(a[x]-a[y-1]);t2=abs(a[x]-a[y+1]);
	if(t<t1||t<t2) {t=0;return t;}
	return t;}
int main(){
	freopen("wave.in","r",stdin);
	freopen("wave.out","w",stdout);
	n=read();k=read();
	for(int i=1;i<=n;i++)
	a[i]=read();
	for(int i=1;i<=n-2;i++)
		for(int j=i+2;j<=n;j++)
	maxs=max(maxs,judge(i,j));
	cout<<maxs<<endl;	
	return 0;
}
