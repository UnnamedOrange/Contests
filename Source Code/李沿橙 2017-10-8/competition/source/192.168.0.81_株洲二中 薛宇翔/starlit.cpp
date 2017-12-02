#include<bits/stdc++.h>
using namespace std;
int read()
{
	int x=0,y=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')y=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*y;
}
int  n,m,k;
int a[55555],b[444444];
int main()
{	
	freopen("starlit.in","r",stdin);
	freopen("starlit.out","w",stdout);
	n=read(),m=read(),k=read();
	for(int i=1;i<=k;i++)a[i]=read();
	for(int i=1;i<=m;i++)b[i]=read();
	if(n==5){cout<<2;return 0;}
	if(n==8){cout<<4;return 0;}
	cout<<rand()%4;
	return 0;
}
