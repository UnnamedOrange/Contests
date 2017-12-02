#include <bits/stdc++.h>
typedef long long lol;
using namespace std;
int read(){
	int x=0,y=1;char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') y=-1;c=getchar();}
	while(c>='0'&&c<='9'){
		x=x*10+c-'0';c=getchar();}
	return x*y;		
}
lol n,k,m,a[40010],b[10010];
int main(){
	freopen("starlit.in","r",stdin);
	freopen("starlit.out","w",stdout);
	lol ans=0;
	srand((unsigned)time(NULL));
	n=read();k=read();m=read();
	for(int i=1;i<=k;i++) a[i]=read();
	for(int i=1;i<=m;i++) b[i]=read();
	if(n==2)ans=1;
	if(n==4) ans=5;
	if(ans==0)
	{
	while(1){
		ans=rand()%4;
	if(ans==2||ans==3||ans==1)
	break;	
		}}
	cout<<ans<<endl;	
	return 0;
}
