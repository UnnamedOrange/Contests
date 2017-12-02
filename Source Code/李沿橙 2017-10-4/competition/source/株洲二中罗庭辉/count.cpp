#include <bits/stdc++.h>
#define inf 998244353
typedef long long lol;
using namespace std;
inline int read(){
	int x=0,y=1;char c=getchar();
	while(c>'9'||c<'0'){
		if(c=='-') y=1;c=getchar();}
		while(c>='0'&&c<='9'){
			x=x*10+c-'0';c=getchar();}
			return x*y;
}
lol ans;
lol fastm(lol a,lol b,lol c){
	lol anss=1;a=a%c;
	while(b){if(b&1) anss=anss*a%c;a=a*a%c;b=b/2;}
	anss%=c;
	return anss;
}
lol l,r,k;
int main(){
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	l=read();r=read();k=read();
	for(int i=l;i<=r;i++)
	{ans=(ans+fastm(i,k,inf))%inf;}
	cout<<ans<<endl;
	return 0;
}
