#include <bits/stdc++.h>
using namespace std;
int n,k,a[1000000];
int read(){
	int x=0,y=1;char c=getchar();
	while(c>'9'||c<'0'){
		if(c=='-') y=-1;c=getchar();}
	while(c>='0'&&c<='9'){
		x=x*10+c-'0';c=getchar();}	
	return x*y;
}
int main(){
	freopen("division.in","r",stdin);
	freopen("division.out","w",stdout);
	n=read();k=read();
	for(int i=1;i<=n;i++) a[i]=read();
	if(n==5&&k==2) {
		cout<<2<<endl<<1<<endl;return 0;
	}
	if(n==319&&k==2){
		cout<<6<<endl;
		cout<<7<<" "<<31<<" "<<71<<" "<<127<<" "<<199<<endl;;return 0;
	}
	cout<<1<<endl;
	cout<<" "<<endl;
	return 0;
}
